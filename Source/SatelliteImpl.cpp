#include <map>
#include <set>
#include <ctime>
#include <cstdint>
#include <spdlog/spdlog.h>

#include "SatelliteImpl.hpp"

using std::string;

struct ServiceNode
{
    string  IpPort;
    int32_t Weight;

    ServiceNode(const string &IpPort, int32_t Weight):
        IpPort(IpPort), Weight(Weight) { }

    bool operator < (const ServiceNode &x) const
    {
        return IpPort < x.IpPort;
    }
};

class SatelliteInternal
{
public:
    // ServerName -> ServerSet
    std::map<string, std::set<ServiceNode>> Servers;
    uint64_t LastUpdate;

    SatelliteInternal(void):
        LastUpdate(time(nullptr)) { }
};

SatelliteImpl::SatelliteImpl(void)
{
    this->PImpl = new SatelliteInternal;
    
}

SatelliteImpl::~SatelliteImpl(void)
{
    delete this->PImpl;
}

::grpc::Status SatelliteImpl::Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response)
{
    // timestamp check
    auto ts = time(nullptr);
    response->set_code(0);
    int64_t margin;
    if (ts > request->timestamp())
        margin = ts - request->timestamp();
    else
        margin = request->timestamp() - ts;
    if (margin > 20)
    {
        spdlog::warn("heartbeat timestamp margin too much: {}, {}, remote {}, local {}", 
            request->service_info().service_name(),
            request->service_info().server_ip_port(),
            request->timestamp(), ts);
        response->set_code(-1000);
        response->set_message(fmt::format("Server timestamp: {}, your timestamp: {}", ts, request->timestamp()));
        return grpc::Status::OK;
    }
    // logic
    const auto &serviceName = request->service_info().service_name();
    if (PImpl->Servers.find(serviceName) == PImpl->Servers.end())
        PImpl->Servers.insert(std::make_pair(serviceName, std::set<ServiceNode>()));
    auto &serverSet = PImpl->Servers[serviceName];
    ServiceNode tmpNode(request->service_info().server_ip_port(), request->service_info().weight());
    if (serverSet.find(tmpNode) == serverSet.end())
    {
        serverSet.insert(tmpNode);
    }
    else
    {
        auto np = serverSet.find(tmpNode);
        if (np->Weight != tmpNode.Weight)
        {
            serverSet.erase(np);
            serverSet.insert(tmpNode);
            PImpl->LastUpdate = ts;
        }
    }
    return grpc::Status::OK;
}

::grpc::Status SatelliteImpl::GetCurrentVersion(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response)
{
    response->set_timestamp(PImpl->LastUpdate);
    // spdlog::info("GetCurrentVersion: {}", PImpl->LastUpdate);
    return grpc::Status::OK;
}
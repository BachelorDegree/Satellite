#include <map>
#include <set>
#include <ctime>
#include <mutex>
#include <cstdint>
#include <spdlog/spdlog.h>

#include "SatelliteImpl.hpp"

using std::string;

struct ServiceNode
{
    int32_t Weight;
    int64_t LastHeartbeat;
    ServiceNode(int32_t weight, int64_t lastHeartbeat):
        Weight(weight), LastHeartbeat(lastHeartbeat) { }
};

class SatelliteInternal
{
public:
    // ServerName -> ServerSet
    std::map<string, std::map<string, ServiceNode>> Servers;
    uint64_t LastUpdate;
    std::mutex MutexServers, MutexLastUpdate;

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
    const std::lock_guard<std::mutex> sguard(PImpl->MutexServers);
    const auto &serviceName = request->service_info().service_name();
    const auto &ip_port = request->service_info().server_ip_port();
    const auto weight = request->service_info().weight();
    if (PImpl->Servers.find(serviceName) == PImpl->Servers.end())
        PImpl->Servers.insert(std::make_pair(serviceName, std::map<string, ServiceNode>()));
    auto &servers = PImpl->Servers[serviceName];
    if (servers.find(ip_port) == servers.end())
    {
        servers.insert(std::make_pair(ip_port, ServiceNode(weight, ts)));
    }
    else
    {
        auto np = servers.find(ip_port);
        if (np->second.Weight != weight)
        {
            np->second.Weight = weight;
            const std::lock_guard<std::mutex> luguard(PImpl->MutexLastUpdate);
            PImpl->LastUpdate = ts;
        }
        np->second.LastHeartbeat = ts;
    }
    return grpc::Status::OK;
}

::grpc::Status SatelliteImpl::GetCurrentVersion(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response)
{
    response->set_timestamp(PImpl->LastUpdate);
    // spdlog::info("GetCurrentVersion: {}", PImpl->LastUpdate);
    return grpc::Status::OK;
}

::grpc::Status SatelliteImpl::GetServiceNodes(::grpc::ServerContext* context, const ::GetServiceNodesRequest* request, ::GetServiceNodesResponse* response)
{
    const auto ts = time(nullptr);
    response->mutable_status()->set_code(0);
    const std::lock_guard<std::mutex> guard(PImpl->MutexServers);
    auto f = PImpl->Servers.find(request->service_name());
    if (f == PImpl->Servers.end())
    {
        response->mutable_status()->set_code(-1001);
        response->mutable_status()->set_message("Service doesn't exist");
        return grpc::Status::OK;
    }
    for (const auto &i : f->second)
    {
        // no heartbeat over 30s
        if (ts - i.second.LastHeartbeat > 30)
            continue;
        auto p = response->add_nodes();
        p->set_service_name(request->service_name());
        p->set_server_ip_port(i.first);
        p->set_weight(i.second.Weight);
    }
    return grpc::Status::OK;
}

::grpc::Status SatelliteImpl::GetAllServiceNames(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetAllServiceNamesResponse* response)
{
    std::lock_guard<std::mutex> guard(PImpl->MutexServers);
    for (const auto &i : PImpl->Servers)
    {
        response->add_service_names(i.first);
    }
    return grpc::Status::OK;
}
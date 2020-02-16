#pragma once

#include "satellite.pb.h"
#include "satellite.grpc.pb.h"

class SatelliteInternal;
class SatelliteImpl final : public Satellite::Service
{
public:
    SatelliteImpl(void);
    ~SatelliteImpl(void);
    ::grpc::Status Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response) override;
    ::grpc::Status GetCurrentVersion(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response) override;
    ::grpc::Status GetServiceNodes(::grpc::ServerContext* context, const ::GetServiceNodesRequest* request, ::GetServiceNodesResponse* response) override;
    ::grpc::Status GetAllServiceNames(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetAllServiceNamesResponse* response) override;
private:
    SatelliteInternal *PImpl;
};
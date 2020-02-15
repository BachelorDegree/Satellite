#pragma once

#include "../Proto/satellite.pb.h"
#include "../Proto/satellite.grpc.pb.h"

class SatelliteInternal;
class SatelliteImpl final : public Satellite::Service
{
public:
    SatelliteImpl(void);
    ~SatelliteImpl(void);
    ::grpc::Status Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response) override;
    ::grpc::Status GetCurrentVersion(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response) override;
private:
    SatelliteInternal *PImpl;
};
#pragma once

#include "../Proto/satellite.pb.h"
#include "../Proto/satellite.grpc.pb.h"

class SatelliteImpl final : public Satellite::Service
{
public:
    ::grpc::Status Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response) override;
};
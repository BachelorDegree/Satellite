#include "SatelliteImpl.hpp"

::grpc::Status SatelliteImpl::Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response)
{
    return grpc::Status::OK;
}
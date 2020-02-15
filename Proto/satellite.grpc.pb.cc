// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: satellite.proto

#include "satellite.pb.h"
#include "satellite.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char* Satellite_method_names[] = {
  "/Satellite/Heartbeat",
  "/Satellite/GetCurrentVersion",
};

std::unique_ptr< Satellite::Stub> Satellite::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Satellite::Stub> stub(new Satellite::Stub(channel));
  return stub;
}

Satellite::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Heartbeat_(Satellite_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetCurrentVersion_(Satellite_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Satellite::Stub::Heartbeat(::grpc::ClientContext* context, const ::HeartbeatRequest& request, ::GeneralStatus* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Heartbeat_, context, request, response);
}

void Satellite::Stub::experimental_async::Heartbeat(::grpc::ClientContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Heartbeat_, context, request, response, std::move(f));
}

void Satellite::Stub::experimental_async::Heartbeat(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GeneralStatus* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Heartbeat_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::GeneralStatus>* Satellite::Stub::AsyncHeartbeatRaw(::grpc::ClientContext* context, const ::HeartbeatRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GeneralStatus>::Create(channel_.get(), cq, rpcmethod_Heartbeat_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::GeneralStatus>* Satellite::Stub::PrepareAsyncHeartbeatRaw(::grpc::ClientContext* context, const ::HeartbeatRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GeneralStatus>::Create(channel_.get(), cq, rpcmethod_Heartbeat_, context, request, false);
}

::grpc::Status Satellite::Stub::GetCurrentVersion(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::GetCurrentVersionResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetCurrentVersion_, context, request, response);
}

void Satellite::Stub::experimental_async::GetCurrentVersion(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetCurrentVersion_, context, request, response, std::move(f));
}

void Satellite::Stub::experimental_async::GetCurrentVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetCurrentVersionResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetCurrentVersion_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::GetCurrentVersionResponse>* Satellite::Stub::AsyncGetCurrentVersionRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GetCurrentVersionResponse>::Create(channel_.get(), cq, rpcmethod_GetCurrentVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::GetCurrentVersionResponse>* Satellite::Stub::PrepareAsyncGetCurrentVersionRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GetCurrentVersionResponse>::Create(channel_.get(), cq, rpcmethod_GetCurrentVersion_, context, request, false);
}

Satellite::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Satellite_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Satellite::Service, ::HeartbeatRequest, ::GeneralStatus>(
          std::mem_fn(&Satellite::Service::Heartbeat), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Satellite_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Satellite::Service, ::google::protobuf::Empty, ::GetCurrentVersionResponse>(
          std::mem_fn(&Satellite::Service::GetCurrentVersion), this)));
}

Satellite::Service::~Service() {
}

::grpc::Status Satellite::Service::Heartbeat(::grpc::ServerContext* context, const ::HeartbeatRequest* request, ::GeneralStatus* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Satellite::Service::GetCurrentVersion(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::GetCurrentVersionResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}



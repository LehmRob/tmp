// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rpc.proto

#include "rpc.pb.h"
#include "rpc.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace grpctest {

static const char* GrpcTester_method_names[] = {
  "/grpctest.GrpcTester/DoIt",
};

std::unique_ptr< GrpcTester::Stub> GrpcTester::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< GrpcTester::Stub> stub(new GrpcTester::Stub(channel));
  return stub;
}

GrpcTester::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_DoIt_(GrpcTester_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status GrpcTester::Stub::DoIt(::grpc::ClientContext* context, const ::grpctest::TesterRequest& request, ::grpctest::TesterReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_DoIt_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::grpctest::TesterReply>* GrpcTester::Stub::AsyncDoItRaw(::grpc::ClientContext* context, const ::grpctest::TesterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::grpctest::TesterReply>::Create(channel_.get(), cq, rpcmethod_DoIt_, context, request);
}

GrpcTester::Service::Service() {
  AddMethod(new ::grpc::RpcServiceMethod(
      GrpcTester_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< GrpcTester::Service, ::grpctest::TesterRequest, ::grpctest::TesterReply>(
          std::mem_fn(&GrpcTester::Service::DoIt), this)));
}

GrpcTester::Service::~Service() {
}

::grpc::Status GrpcTester::Service::DoIt(::grpc::ServerContext* context, const ::grpctest::TesterRequest* request, ::grpctest::TesterReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace grpctest


#include <thread>
#include <memory>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

#include <spdlog/spdlog.h>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "Source/SatelliteImpl.hpp"
#include "Source/TfcConfigCodec.hpp"

AlohaIO::TfcConfigCodec MainConf;

void DoServer(void);

int main(int argc, char *argv[])
{
    int MainRet = EXIT_FAILURE;
    do
    {
        if (argc == 1)
        {
            fprintf(stderr, "USAGE: %s <conf_file>\n", argv[0]);
            break;
        }
        
        int ret = MainConf.ParseFile(argv[1]);
        if (ret != AlohaIO::TfcConfigCodec::SUCCESS)
        {
            fprintf(stderr, "Parse %s failed, retcode: %d\n", argv[1], ret);
            break;
        }
        MainRet = EXIT_SUCCESS;
        DoServer();
    } while (false);
    return MainRet;
}

void DoServer(void)
{
    auto listenIpPort = MainConf.GetKV("server", "bind_ip").append(":").append(MainConf.GetKV("server", "bind_port"));
    SatelliteImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(listenIpPort, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    spdlog::info("Server listening on {}", listenIpPort);
    server->Wait();
}
protoc --cpp_out=. satellite.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` satellite.proto
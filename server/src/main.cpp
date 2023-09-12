#include <iostream>
#include <grpcpp/grpcpp.h>
#include <myproto/rpc_commands.grpc.pb.h>

class CommandServiceImpl final : public CommandService::Service {
public:
	grpc::Status SayHello(
		grpc::ServerContext* context,
		const HelloRequest* request,
		HelloResponse* response
	) override {
		std::cout << "hello" << std::endl;
		return grpc::Status::OK;
	}

	grpc::Status PrintMessage(
		grpc::ServerContext* context,
		const PrintRequest* request,
		PrintResponse* response
	) override {
		std::cout << request->message().substr(6, std::string::npos) << std::endl;
		return grpc::Status::OK;
	}
};

int main() {
	std::string server_address("0.0.0.0:50051");
	CommandServiceImpl service;

	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();

	return 0;
}

#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include <myproto/rpc_commands.grpc.pb.h>

int main() {
	grpc::ChannelArguments channel_args;
	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	std::unique_ptr<CommandService::Stub> stub = CommandService::NewStub(channel);

	// Send "hello" command
	HelloRequest hello_request;
	HelloResponse hello_response;
	grpc::ClientContext hello_context;
	grpc::Status hello_status = stub->SayHello(&hello_context, hello_request, &hello_response);

	if (hello_status.ok()) {
		std::cout << "Server says: hello" << std::endl;
	} else {
		std::cerr << "RPC failed: " << hello_status.error_message() << std::endl;
	}

	// Send "print [x]" command
	PrintRequest print_request;
	print_request.set_message("print [Some Parameter 1]");
	PrintResponse print_response;
	grpc::ClientContext print_context;
	grpc::Status print_status = stub->PrintMessage(&print_context, print_request, &print_response);

	if (print_status.ok()) {
		std::cout << "Print command sent successfully." << std::endl;
	} else {
		std::cerr << "RPC failed: " << print_status.error_message() << std::endl;
	}

	return 0;
}

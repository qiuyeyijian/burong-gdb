#include <iostream>
#include<thread>
#include "burongnet.h"
static void master_write_callback(burongnet::Handle handle, uint32_t len) {
	std::cout << "[Thread " << std::this_thread::get_id() << " ] "
		<< "Send ok" << std::endl;
}
static void master_read_callback(burongnet::Handle handle, std::shared_ptr<burongnet::Buffer> data, uint32_t len) {}
static void master_accept_callback(burongnet::Handle handle, uint32_t code) {
	if (code == burongnet::CEC_SUCCESS) {
		std::string ip;
		uint16_t port;
		handle->GetAddress(ip, port);
		std::cout << "IP: " << ip << " Port: " << port << std::endl;
	}
	else {
		std::cout << "Something error: " << code << std::endl;
	}
}

static void master_disconnect_callback(burongnet::Handle handle, uint32_t err) {
	std::cout << "Disconnect" << std::endl;

}

static void slave_write_callback(burongnet::Handle handle, uint32_t len) {
	std::cout << "write: " << len << std::endl;
}
static void slave_read_callback(burongnet::Handle handle, std::shared_ptr<burongnet::Buffer> data, uint32_t len) {
	std::cout << "read: " << data << len << std::endl;
}
static void slave_connect_callback(burongnet::Handle handle, uint32_t code) {
	std::cout << "connect: " << code << std::endl;
}
static void slave_disconnect_callback(burongnet::Handle handle, uint32_t err) {
	std::cout << "disconnect: " << err << std::endl;
}


int main(int argc, char const* argv[])
{
	burongnet::BuRongNet net;
	net.Init(4);
	net.SetConnectionCallback(slave_connect_callback);
	net.SetWriteCallback(slave_write_callback);
	net.SetReadCallback(slave_read_callback);
	net.SetDisconnectionCallback(slave_disconnect_callback);
	net.Connection("127.0.0.1", 9821);
	net.Join();


	/* code */
	return 0;
}

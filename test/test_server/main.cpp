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

static void slave_write_callback(burongnet::Handle handle, uint32_t len) {}
static void slave_read_callback(burongnet::Handle handle, std::shared_ptr<burongnet::Buffer> data, uint32_t len) {

}
static void slave_connect_callback(burongnet::Handle handle, uint32_t code) {}
static void slave_disconnect_callback(burongnet::Handle handle, uint32_t err) {
}


int main(int argc, char const* argv[])
{
	burongnet::BuRongNet net;
	net.Init(4);
	net.SetAcceptCallback(master_accept_callback);
	net.SetWriteCallback(master_write_callback);
	net.SetReadCallback(master_read_callback);
	net.SetDisconnectionCallback(master_disconnect_callback);
	net.ListenAndAccept("0.0.0.0", 9821);

	net.Join();
	

	/* code */
	return 0;
}

#pragma once
#include <string_view>
#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996)

class UDPSocks {
public:
	UDPSocks();
	~UDPSocks();

	bool BindListeningSocket();
	void UnbindListeningSocket();

	void SendPacket(char* message);
	std::string_view RecievePacket();

private:
	sockaddr_in server;
	sockaddr_in client;
	SOCKET server_socket;
};

UDPSocks* GetUDP();
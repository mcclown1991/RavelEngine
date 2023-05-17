#include "UDPSock.h"

#include <iostream>

UDPSocks* GetUDP() {
    static UDPSocks s;
    return(&s);
}

UDPSocks::UDPSocks() {
	
}

UDPSocks::~UDPSocks() {
	
}

bool UDPSocks::BindListeningSocket() {
    // initialise winsock
    WSADATA wsa;
    std::cout << "Initialising Winsock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return false;
    }
    printf("Initialised.\n");

    // create a socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    u_long iMode = 1;
    auto iResult = ioctlsocket(server_socket, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
        printf("ioctlsocket failed with error: %ld\n", iResult);

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        return false;
    }
    puts("Bind done.");
}

void UDPSocks::UnbindListeningSocket() {
    closesocket(server_socket);
    WSACleanup();
}

void UDPSocks::SendPacket(char* message) {
    // print details of the client/peer and the data received
    printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    printf("Data: %s\n", message);

    // reply the client with 2the same data
    if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code: %d", WSAGetLastError());
    }
}

std::string_view UDPSocks::RecievePacket() {
    
    // try to receive some data, this is a blocking call
    int message_len;
    int slen = sizeof(sockaddr_in);
    char message[256] = {};
    if (message_len = recvfrom(server_socket, message, 256, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
    {
        auto error = WSAGetLastError();
        if (error == WSAEWOULDBLOCK)
            std::cout << "no data try again later" << std::endl;
			//printf("recvfrom() failed with error code: %d", WSAGetLastError());
        return std::string();
    }
    return message;
}

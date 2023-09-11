#pragma once
#include<WS2tcpip.h>
#include<iostream>
#include<string>
#include<WinSock2.h>
#include"Address_v4.h"
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 512
class Socket
{
	friend class Address_v4;
public:


	void connect(Address_v4* addr);

	void send(char* msg, int msg_len);

	void recv(char* msg, int msg_len);

	Socket();
	~Socket();


private:
	int fd;

	Address_v4* addr;
	void init();

};


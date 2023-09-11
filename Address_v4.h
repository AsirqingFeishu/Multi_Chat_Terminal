#pragma once
#include "Socket.h"
class Address_v4
{
public:
	Address_v4();
	Address_v4(char* ip, int port);
	~Address_v4();

	void GetAddr(char* ip, int& port);
	void SetAddr();

	struct sockaddr_in addr;
	int addr_len;
	char* ip;
};


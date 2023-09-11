#include "Socket.h"

Socket::Socket()
{
	this->init();

	addr = new Address_v4();

	fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		std::cout << "socket create error!" << std::endl;
		exit(1);
	}
}


void Socket::connect(Address_v4* addr)
{
	int res = ::connect(fd, (struct sockaddr*)&addr->addr, addr->addr_len);
	if (res != 0)
	{
		std::cout << "connect failed！" << std::endl;
		exit(1);
	}
	char ip[20];
	inet_ntop(AF_INET, &(addr->addr.sin_addr), ip, sizeof(ip));
	std::cout << "connect [ " << ip << ":" << ntohs(addr->addr.sin_port) << " ] "
		<< "sucessfully!" << std::endl;
}

void Socket::send(char* msg,int msg_len)
{
	int size =::send(this->fd, msg, msg_len,0);
	if (size < 0)
	{
		std::cout << "send message failed. " << WSAGetLastError() << std::endl;
		exit(1);
	}
	else if (size == 0)
	{
		std::cout << "connect already close." << WSAGetLastError() << std::endl;
		exit(0);
	}
	else
		std::cout << "send successfully." << std::endl;
}

void Socket::recv(char* msg, int msg_len)
{
	int ret = ::recv(fd, msg, sizeof(msg_len), 0);
	if (ret < 0)
	{
		std::cout << "recv failed." << std::endl;
		exit(1);
	}
	else if (ret == 0)
	{
		std::cout << "connect already close." << WSAGetLastError() << std::endl;
		exit(0);
	}
	else
	{
		std::cout << ">> " << msg << std::endl;
	}

}

void Socket::init()
{	
	/********  初始化WinSock  **************/
	WORD wVersionRequested = MAKEWORD(2, 2);		// 生成版本号
	WSADATA wsaData;
	if (::WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		std::cout << "加载WinSock.dll 失败" << WSAGetLastError() << std::endl;
		exit(1);
	}
}




Socket::~Socket()
{
	if (fd)
	{
		closesocket(fd);
	}
	if (addr != nullptr)
		delete addr;
	WSACleanup();
}

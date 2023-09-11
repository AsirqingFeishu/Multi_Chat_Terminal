#include "Address_v4.h"

Address_v4::Address_v4()
{
	ip = new char(30);
	addr_len = sizeof(struct sockaddr_in);
	memset(&addr, 0, addr_len);
}

Address_v4::Address_v4(char* ip, int port)
{
	memset(&addr, 0, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &addr.sin_addr);
}

Address_v4::~Address_v4()
{
	
}
void Address_v4::GetAddr(char* ip, int& port)
{
	std::cout << "������IP:";
	std::cin >> ip;
	std::cout << "������˿ں�:";
	std::cin >> port;
}
/*     ����ip��ַ�Ͷ˿ں�      */
void Address_v4::SetAddr()
{

	int port = 0;
	this->GetAddr(ip,port);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &addr.sin_addr);

	return;
}
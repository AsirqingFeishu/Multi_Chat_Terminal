#include "Socket.h"
#include "User.h"
#include <iostream>

using namespace std;
int main()
{
	// 创建套接字
	Socket cliSock;
	// 创建服务器地址
	Address_v4 addr;
	addr.SetAddr();
	// 开始连接
	cliSock.connect(&addr);

	// 创建用户
	User user(cliSock);
	// 用户登陆
	user.Login();
	// 用户聊天
	user.Chat();

	system("pause");


	return 0;
}
#include "Socket.h"
#include "User.h"
#include "Console.h"
#include <iostream>

using namespace std;


int main()
{
	// 终端显示类
	Console ConsoleShow;
	// 登陆终端显示
	ConsoleShow.LoginShow(ConsoleShow.width, ConsoleShow.height);

	// 创建套接字
	Socket cliSock;
	// 创建服务器地址
	Address_v4 addr;
	addr.SetAddr();		// 已更改
	// 开始连接
	cliSock.connect(&addr);

	// 创建用户
	User user(cliSock);
	// 用户登陆
	user.Login();

	// 聊天窗口显示
	ConsoleShow.ChatShow(ConsoleShow.width+40, ConsoleShow.height+15);
	// 用户聊天
	user.Chat(ConsoleShow);

	system("pause");


	return 0;
}
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Socket.h"
#include <string>


class UsrInfor
{
public:
	UsrInfor() {};
	~UsrInfor() {};
	// 转换用户信息为数据进行发送
	void Transfrom(class UsrInfor& user, char** buf);
public:
	std::string code;			// 指令码
	std::string name;			// 用户名
	std::string sec;			// 密码
	std::string msg;			// 用户消息
};
class User
{
	friend class UsrInfo;
	friend class Manager;
public:

	User(Socket& sock);
	~User() {};
	/*		用户登陆	*/
	void Login();
	/*		用户注册	*/
	void Register();
	/*		用户聊天	*/
	void Chat();

	void Input();
public:
	UsrInfor usrInfo;
	char AckBuf[4];			// Ack接收缓存
	char* buf;				// 发送、接收缓存
private:
	bool Is_Resigter(char* rep);
private:

	Socket sock;
	char CL_CMD_REG;
	char CL_CMD_CHAT;
	char CL_CMD_LOGIN;
};





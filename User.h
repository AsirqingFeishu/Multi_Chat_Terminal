#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Socket.h"
#include "Console.h"
#include <string>
#include <thread>
#include <mutex>
#include<conio.h>
/*		
	注册/登陆数据： [r/l, 用户名，密码,]
	聊天数据：		[c,用户名, 聊天信息]
*/
#define Separator ','
class UsrInfor
{
public:
	UsrInfor() {};
	~UsrInfor() {};
	// 转换用户信息为数据进行发送
	/*
		user: 用户信息
		buf：数据缓存
		返回值：数据大小
	*/
	int Transfrom_to_Date(UsrInfor& user, char*& buf, char usrCode);
	/*
		转用户信息为数据
	*/
	int inTransfrom_to_UsrInfor(UsrInfor*& user, char*& buf);
public:
	std::string code;			// 指令码
	std::string name;			// 用户名
	std::string sec;			// 密码
	std::string msg;			// 用户消息
};
class User
{
	friend class UsrInfo;

public:

	User(Socket& sock);
	~User() {};
	/*		用户登陆	*/
	void Login();
	/*		用户注册	*/
	void Register(char code);
	/*		用户聊天	*/
	void Chat(Console& console);
	/*      输入登陆信息   */
	void Input();
	/*     显示聊天信息   */
	void ShowChat(Console& console);
public:
	UsrInfor usrInfo;						// 用户信息
	UsrInfor* usrInfo_Recv=nullptr;			// 收到的用户消息
	char AckBuf[10];					// Ack接收缓存
	char* buf;							// 接收缓存
private:
	bool Is_Resigter(char* rep);
private:

	Socket sock;
	char CL_CMD_REG;
	char CL_CMD_CHAT;
	char CL_CMD_LOGIN;

	// 锁变量
	std::mutex mtx;
};





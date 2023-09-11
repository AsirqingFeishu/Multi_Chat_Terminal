#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Socket.h"
#include <string>


class UsrInfor
{
public:
	UsrInfor() {};
	~UsrInfor() {};
	// ת���û���ϢΪ���ݽ��з���
	void Transfrom(class UsrInfor& user, char** buf);
public:
	std::string code;			// ָ����
	std::string name;			// �û���
	std::string sec;			// ����
	std::string msg;			// �û���Ϣ
};
class User
{
	friend class UsrInfo;
	friend class Manager;
public:

	User(Socket& sock);
	~User() {};
	/*		�û���½	*/
	void Login();
	/*		�û�ע��	*/
	void Register();
	/*		�û�����	*/
	void Chat();

	void Input();
public:
	UsrInfor usrInfo;
	char AckBuf[4];			// Ack���ջ���
	char* buf;				// ���͡����ջ���
private:
	bool Is_Resigter(char* rep);
private:

	Socket sock;
	char CL_CMD_REG;
	char CL_CMD_CHAT;
	char CL_CMD_LOGIN;
};





#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Socket.h"
#include "Console.h"
#include <string>
#include <thread>
#include <mutex>
#include<conio.h>
/*		
	ע��/��½���ݣ� [r/l, �û���������,]
	�������ݣ�		[c,�û���, ������Ϣ]
*/
#define Separator ','
class UsrInfor
{
public:
	UsrInfor() {};
	~UsrInfor() {};
	// ת���û���ϢΪ���ݽ��з���
	/*
		user: �û���Ϣ
		buf�����ݻ���
		����ֵ�����ݴ�С
	*/
	int Transfrom_to_Date(UsrInfor& user, char*& buf, char usrCode);
	/*
		ת�û���ϢΪ����
	*/
	int inTransfrom_to_UsrInfor(UsrInfor*& user, char*& buf);
public:
	std::string code;			// ָ����
	std::string name;			// �û���
	std::string sec;			// ����
	std::string msg;			// �û���Ϣ
};
class User
{
	friend class UsrInfo;

public:

	User(Socket& sock);
	~User() {};
	/*		�û���½	*/
	void Login();
	/*		�û�ע��	*/
	void Register(char code);
	/*		�û�����	*/
	void Chat(Console& console);
	/*      �����½��Ϣ   */
	void Input();
	/*     ��ʾ������Ϣ   */
	void ShowChat(Console& console);
public:
	UsrInfor usrInfo;						// �û���Ϣ
	UsrInfor* usrInfo_Recv=nullptr;			// �յ����û���Ϣ
	char AckBuf[10];					// Ack���ջ���
	char* buf;							// ���ջ���
private:
	bool Is_Resigter(char* rep);
private:

	Socket sock;
	char CL_CMD_REG;
	char CL_CMD_CHAT;
	char CL_CMD_LOGIN;

	// ������
	std::mutex mtx;
};





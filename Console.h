#pragma once
#include <Windows.h>
#include<string>
#include<iostream>

class Console
{
public:

	Console();

	~Console();

	// ��½��Ϣ��ʾ
	void LoginShow(int width, int height);
	// ���������ʾ
	void ChatShow(int width, int height);
	// ���ô��ڴ�С
	void Set_WinSize(int width, int height);
	// ���ù��λ��
	void SetXY(int x, int y);
	// ��ȡ��ǰ���λ��
	void GetCurXY(POINT& pos);
public:
	int width = 0;			//	���
	int height = 0;			//	�߶�
public:
	POINT pos_Info;				// �����Ϣ�Ĺ��λ��
	POINT pos_Usr;				// ���ʹ��ڵĹ��λ��
};


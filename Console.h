#pragma once
#include <Windows.h>
#include<string>
#include<iostream>

class Console
{
public:

	Console();

	~Console();

	// 登陆信息显示
	void LoginShow(int width, int height);
	// 聊天界面显示
	void ChatShow(int width, int height);
	// 设置窗口大小
	void Set_WinSize(int width, int height);
	// 设置光标位置
	void SetXY(int x, int y);
	// 获取当前光标位置
	void GetCurXY(POINT& pos);
public:
	int width = 0;			//	宽度
	int height = 0;			//	高度
public:
	POINT pos_Info;				// 输出消息的光标位置
	POINT pos_Usr;				// 发送窗口的光标位置
};


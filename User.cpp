#include "User.h"

/*      登陆     */
void User::Login()
{
	this->Register(this->CL_CMD_LOGIN);
	std::cout << AckBuf << std::endl;
	// 判断是否已经注册
	if (!Is_Resigter(AckBuf))
	{
		this->Register(this->CL_CMD_REG);
		if (Is_Resigter(AckBuf))
		{
			std::cout << "注册成功" << std::endl;
		}
		else
			std::cout << "注册失败" << std::endl;
			return;
	}
	std::cout << "登陆成功" << std::endl;
	Sleep(2);
	return;
}
/*      注册     */
void User::Register(char code)
{
	this->Input();
	this->usrInfo.code = code;
	int size = usrInfo.Transfrom_to_Date(usrInfo, buf, code);					// 转为发送数据
	int sendByte = this->sock.send(buf, size);
	int recvByte = this->sock.recv(AckBuf, sizeof(AckBuf));

	return;
}

void User::Chat(Console& console)
{

	//std::thread ShowChatInfo;
	//ShowChatInfo = std::thread(&User::ShowChat,this,console);
	this->usrInfo.code = CL_CMD_CHAT;
	while (true)
	{
		/***************************   上锁        *******************/
		this->mtx.lock();
		// 设置光标位置
		console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
		// 获取输入信息
	
		while (true)
		{
			if (_kbhit())
			{
				char ch = _getch();
				if (ch == '\r')			// 按下回车
				{
					break;
				}
				else if (ch == 8)		// 按下退格
				{

				}
				// 设置光标位置
				console.SetXY(console.pos_Usr.x + this->usrInfo.msg.size(), console.pos_Usr.y);
				std::cout << ch;
				this->usrInfo.msg += ch;
			}
		}
		// 清除编辑区
		console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
		std::cout << std::string(this->usrInfo.msg.size(), ' ');
		if (this->usrInfo.msg.size())
		{
			// 消息窗口打印自己发出的信息
			console.SetXY(console.pos_Info.x, console.pos_Info.y);
			console.pos_Info.y += 1;
			std::cout << this->usrInfo.name << ">> " << this->usrInfo.msg << std::endl;
		}
		this->mtx.unlock();
		/****************************** 解锁      ***********************/

		// 转换消息为数据，并发送
		if (usrInfo.msg.size() != 0)
		{
			int size = usrInfo.Transfrom_to_Date(usrInfo, buf, usrInfo.code[0]);					// 转为发送数据
			int sendByte = this->sock.send(buf, size);
			if (sendByte == 0)
			{
				std::cout << "connect already close, send failed...." << std::endl;
				break;
			}
			usrInfo.msg.clear();
		}

	}

}
User::User(Socket& sock) :sock(sock) 
{
	this->CL_CMD_REG = 'r';
	this->CL_CMD_CHAT = 'c';
	this->CL_CMD_LOGIN = 'l';
	memset(AckBuf, 0, sizeof(AckBuf));
	this->buf = nullptr;
	//this->usrInfo = new UsrInfo();

};
/*   读取用户信息   */
void User::Input()
{
	std::cout << "用户名：" << std::endl;
	std::cin >> this->usrInfo.name;
	std::cout << "密码：" << std::endl;
	std::cin >> this->usrInfo.sec;
}

void User::ShowChat(Console& console)
{

	int size;
	char* RecvBuf = new char[BUFSIZE];
	memset(RecvBuf, 0, BUFSIZE);
	while (true)
	{
		
		size = this->sock.recv(RecvBuf, sizeof(RecvBuf));
		if (size > 0)
		{
			// 把数据转为用户信息
			this->usrInfo.inTransfrom_to_UsrInfor(this->usrInfo_Recv, RecvBuf);
			/*************************  上锁 ********************/
			this->mtx.lock();

			// 设置消息光标位置
			console.SetXY(console.pos_Info.x, console.pos_Info.y);
			// 输出信息
			std::cout <<this->usrInfo_Recv->name<<">> "<< this->usrInfo_Recv->msg << std::endl;

			// 修改消息光标位
			POINT pos;
			console.GetCurXY(pos);
			console.pos_Info.y = pos.y;
			// 还原光标位置为输入信息 
			console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
			this->mtx.unlock();
			/*************************  开锁 ********************/
		}
		else if (size == 0)
		{
			std::cout << "connect already close...." << std::endl;
			break;
		}
		
	}
	if (RecvBuf != nullptr)
		delete[]RecvBuf;
	return;
}

bool User::Is_Resigter(char* rep)
{
	// 成功注册、或者成功登陆
	if ((rep[0] == this->CL_CMD_LOGIN && rep[1]=='1') || (rep[0] == this->CL_CMD_REG && rep[1]=='1'))
	{
		return true;
	}
	return false;
}
// 转换用户信息为数据进行发送
/*   如果是发送信息，则没有密码部分     */
int UsrInfor::Transfrom_to_Date(UsrInfor& user, char*& buf, char usrCode)
{
	if (usrCode != 'c')
	{
		int size = user.code.size() + user.name.size() + user.msg.size() + user.sec.size();
		if (buf != nullptr)
			delete[] buf;
		buf = new char[size + 4];
		std::string str = user.code + "," + user.name + "," + user.sec + "," + user.msg;
		strncpy(buf, str.c_str(), str.size());
		buf[str.size()] = '\0';
		return str.size() + 1;
	}
	else
	{
		int size = user.code.size() + user.name.size() + user.msg.size();
		if (buf != nullptr)
			delete[] buf;
		buf = new char[size + 3];
		std::string str = user.code + "," + user.name + "," + user.msg;
		strncpy(buf, str.c_str(), str.size());
		buf[str.size()] = '\0';
		return str.size() + 1;
	}
}
// 转换接受数据为用户信息
int UsrInfor::inTransfrom_to_UsrInfor(UsrInfor*& user, char*& buf)
{
	if (user == nullptr)
	{
		user = new UsrInfor;
	}
	std::string Data = buf;
	int pos_Dos[2];				// 分隔符位置  1,111,
	pos_Dos[0] = Data.find(Separator);
	pos_Dos[1] = Data.find(Separator, pos_Dos[0]+1);
	// 切割字符串
	user->code = Data.substr(0, pos_Dos[0]);
	user->name = Data.substr(pos_Dos[0] + 1, pos_Dos[1] - pos_Dos[0] - 1);
	user->sec = "";
	user->msg = Data.substr(pos_Dos[1] + 1);
	Data.clear();
	return 0;
}

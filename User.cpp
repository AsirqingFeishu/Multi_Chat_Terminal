#include "User.h"

/*      登陆     */
void User::Login()
{
	this->Register(this->CL_CMD_LOGIN);
	//std::cout << AckBuf << std::endl;
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
	int size = usrInfo.Transfrom(usrInfo, buf);					// 转为发送数据
	this->sock.send(buf, size);
	this->sock.recv(AckBuf, sizeof(AckBuf));
}

void User::Chat()
{
	//system("cls");
	std::cout << " --------------------------------------------- " << std::endl;
	while (true)
	{
		std::cout << this->usrInfo.name << ">> ";
		system("pause");
		//std::cin >> this->usrInfo;
		//this->sock.send((char*)message, sizeof(message));
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

bool User::Is_Resigter(char* rep)
{
	// 成功注册、或者成功登陆
	if ((rep[0] == this->CL_CMD_LOGIN && rep[1]=='1') || (rep[0] == this->CL_CMD_REG && rep[1]=='1'))
	{
		return true;
	}
	return false;
}

int UsrInfor::Transfrom(UsrInfor& user, char*& buf)
{
	int size = user.code.size() + user.name.size() + user.msg.size() + user.sec.size();
	if (buf != nullptr)
		delete[] buf;
	buf = new char[size + 4];
	std::string str = user.code + "," + user.name + "," + user.sec + "," + user.msg;
	strncpy(buf, str.c_str(), str.size());
	buf[str.size()] = '\0';
	return str.size()+1;
}

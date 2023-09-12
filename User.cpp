#include "User.h"

/*      ��½     */
void User::Login()
{
	this->Register(this->CL_CMD_LOGIN);
	//std::cout << AckBuf << std::endl;
	// �ж��Ƿ��Ѿ�ע��
	if (!Is_Resigter(AckBuf))
	{
		this->Register(this->CL_CMD_REG);
		if (Is_Resigter(AckBuf))
		{
			std::cout << "ע��ɹ�" << std::endl;
		}
		else
			std::cout << "ע��ʧ��" << std::endl;
			return;
	}
	std::cout << "��½�ɹ�" << std::endl;
	Sleep(2);
	return;
}
/*      ע��     */
void User::Register(char code)
{
	this->Input();
	this->usrInfo.code = code;
	int size = usrInfo.Transfrom(usrInfo, buf);					// תΪ��������
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
/*   ��ȡ�û���Ϣ   */
void User::Input()
{
	std::cout << "�û�����" << std::endl;
	std::cin >> this->usrInfo.name;
	std::cout << "���룺" << std::endl;
	std::cin >> this->usrInfo.sec;
}

bool User::Is_Resigter(char* rep)
{
	// �ɹ�ע�ᡢ���߳ɹ���½
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

#include "User.h"

/*      ��½     */
void User::Login()
{
	this->Register(this->CL_CMD_LOGIN);
	std::cout << AckBuf << std::endl;
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
	int size = usrInfo.Transfrom_to_Date(usrInfo, buf, code);					// תΪ��������
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
		/***************************   ����        *******************/
		this->mtx.lock();
		// ���ù��λ��
		console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
		// ��ȡ������Ϣ
	
		while (true)
		{
			if (_kbhit())
			{
				char ch = _getch();
				if (ch == '\r')			// ���»س�
				{
					break;
				}
				else if (ch == 8)		// �����˸�
				{

				}
				// ���ù��λ��
				console.SetXY(console.pos_Usr.x + this->usrInfo.msg.size(), console.pos_Usr.y);
				std::cout << ch;
				this->usrInfo.msg += ch;
			}
		}
		// ����༭��
		console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
		std::cout << std::string(this->usrInfo.msg.size(), ' ');
		if (this->usrInfo.msg.size())
		{
			// ��Ϣ���ڴ�ӡ�Լ���������Ϣ
			console.SetXY(console.pos_Info.x, console.pos_Info.y);
			console.pos_Info.y += 1;
			std::cout << this->usrInfo.name << ">> " << this->usrInfo.msg << std::endl;
		}
		this->mtx.unlock();
		/****************************** ����      ***********************/

		// ת����ϢΪ���ݣ�������
		if (usrInfo.msg.size() != 0)
		{
			int size = usrInfo.Transfrom_to_Date(usrInfo, buf, usrInfo.code[0]);					// תΪ��������
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
/*   ��ȡ�û���Ϣ   */
void User::Input()
{
	std::cout << "�û�����" << std::endl;
	std::cin >> this->usrInfo.name;
	std::cout << "���룺" << std::endl;
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
			// ������תΪ�û���Ϣ
			this->usrInfo.inTransfrom_to_UsrInfor(this->usrInfo_Recv, RecvBuf);
			/*************************  ���� ********************/
			this->mtx.lock();

			// ������Ϣ���λ��
			console.SetXY(console.pos_Info.x, console.pos_Info.y);
			// �����Ϣ
			std::cout <<this->usrInfo_Recv->name<<">> "<< this->usrInfo_Recv->msg << std::endl;

			// �޸���Ϣ���λ
			POINT pos;
			console.GetCurXY(pos);
			console.pos_Info.y = pos.y;
			// ��ԭ���λ��Ϊ������Ϣ 
			console.SetXY(console.pos_Usr.x, console.pos_Usr.y);
			this->mtx.unlock();
			/*************************  ���� ********************/
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
	// �ɹ�ע�ᡢ���߳ɹ���½
	if ((rep[0] == this->CL_CMD_LOGIN && rep[1]=='1') || (rep[0] == this->CL_CMD_REG && rep[1]=='1'))
	{
		return true;
	}
	return false;
}
// ת���û���ϢΪ���ݽ��з���
/*   ����Ƿ�����Ϣ����û�����벿��     */
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
// ת����������Ϊ�û���Ϣ
int UsrInfor::inTransfrom_to_UsrInfor(UsrInfor*& user, char*& buf)
{
	if (user == nullptr)
	{
		user = new UsrInfor;
	}
	std::string Data = buf;
	int pos_Dos[2];				// �ָ���λ��  1,111,
	pos_Dos[0] = Data.find(Separator);
	pos_Dos[1] = Data.find(Separator, pos_Dos[0]+1);
	// �и��ַ���
	user->code = Data.substr(0, pos_Dos[0]);
	user->name = Data.substr(pos_Dos[0] + 1, pos_Dos[1] - pos_Dos[0] - 1);
	user->sec = "";
	user->msg = Data.substr(pos_Dos[1] + 1);
	Data.clear();
	return 0;
}

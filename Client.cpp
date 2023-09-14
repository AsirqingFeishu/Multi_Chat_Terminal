#include "Socket.h"
#include "User.h"
#include "Console.h"
#include <iostream>

using namespace std;


int main()
{
	// �ն���ʾ��
	Console ConsoleShow;
	// ��½�ն���ʾ
	ConsoleShow.LoginShow(ConsoleShow.width, ConsoleShow.height);

	// �����׽���
	Socket cliSock;
	// ������������ַ
	Address_v4 addr;
	addr.SetAddr();		// �Ѹ���
	// ��ʼ����
	cliSock.connect(&addr);

	// �����û�
	User user(cliSock);
	// �û���½
	user.Login();

	// ���촰����ʾ
	ConsoleShow.ChatShow(ConsoleShow.width+40, ConsoleShow.height+15);
	// �û�����
	user.Chat(ConsoleShow);

	system("pause");


	return 0;
}
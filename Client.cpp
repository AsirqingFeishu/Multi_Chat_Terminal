#include "Socket.h"
#include "User.h"
#include <iostream>

using namespace std;
int main()
{
	// �����׽���
	Socket cliSock;
	// ������������ַ
	Address_v4 addr;
	addr.SetAddr();
	// ��ʼ����
	cliSock.connect(&addr);

	// �����û�
	User user(cliSock);
	// �û���½
	user.Login();
	// �û�����
	user.Chat();

	system("pause");


	return 0;
}

#include "stdafx.h"

#include "CLogIn.h"
#include "CField.h"
//http ://ospace.tistory.com/96?category=20180
//https ://m.blog.naver.com/PostView.nhn?blogId=sunxodid79&logNo=140075151448&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F


using namespace std;


int Menu();

////////////////////////////////////////////////
int main()
{
	int menu;
	int num = -1;
	CManager *g_manager = new CLogIn();

	while (1)
	{
		menu = Menu();
		switch (menu)
		{
		case 1:
			((CLogIn*)g_manager)->SignUp();
			break;
		case 2:
			g_manager->ShowAllMemberInfo();
			break;
		case 3:
			((CLogIn*)g_manager)->ChangePassword();
			break;
		case 4:
			num = ((CLogIn*)g_manager)->SignIn();
			if (num >= 0) {
				((CField*)g_manager)->Play(num);
			}
			break;
		case 0:
			g_manager->FileSave();
			return 0;
		default:
			break;
		}
	}
	return 0;
}
////////////////////////////////////////////////

int Menu()
{
	int menu_num = NULL;
	fflush(stdin);
	cout << "/* ============================================== */\n";
	cout << "/* ==            �޴��� �����Ͻÿ�.            == */\n";
	cout << "/* ==  1. ����                                 == */\n";
	cout << "/* ==  2. ���� ���                            == */\n";
	cout << "/* ==  3. ��й�ȣ �� ����                     == */\n";
	cout << "/* ==  4. �α���                               == */\n";
	cout << "/* ==  0. ����!!!!!                            == */\n";
	cout << "/* ============================================== */\n";
	cout << "�Է� : ";
	cin >> menu_num;
	return menu_num;
}



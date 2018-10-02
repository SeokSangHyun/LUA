#include "CLogIn.h"

using namespace std;


CLogIn * CLogIn::Instance()
{
	static CLogIn instance;
	return &instance;
}

CLogIn::CLogIn() : CManager()
{
}


CLogIn::~CLogIn()
{
}
 


void CLogIn::SignUp()
{
	char temp_id[BUFFER_SIZE];
	char temp_password[BUFFER_SIZE];
	ZeroMemory(temp_id, sizeof(char)*BUFFER_SIZE);
	ZeroMemory(temp_password, sizeof(char)*BUFFER_SIZE);

	cout << "������ ID : ";
	cin >> temp_id;
	cout << "������ Password : ";
	cin >> temp_password;

	int user_num = -1;
	bool exist = true;
	for (int i = 0; i < MAX_USER; ++i)
	{
		exist = m_member[i]->GetIsLogin();
		if (exist == false) {
			user_num = i;
			break;
		}
	}

	if (user_num == -1) {
		cout << "�� �̻� ���ԺҰ�!" << endl;
	}
	else {
		lua_getglobal(m_member[user_num]->LUA(), "SetMyInfo");
		lua_pushstring(m_member[user_num]->LUA(), temp_id);
		lua_pushstring(m_member[user_num]->LUA(), temp_password);
		lua_pcall(m_member[user_num]->LUA(), 2, 0, 0);
		m_member[user_num]->SetLogin(true);
	}
}

//ĳ���� ����â
int CLogIn::SignIn()
{
	bool exist = false;
	int serial_num = -1;
	char id[BUFFER_SIZE];
	char password[BUFFER_SIZE];

	ZeroMemory(id, sizeof(char)*BUFFER_SIZE);
	ZeroMemory(password, sizeof(char)*BUFFER_SIZE);

	cout << endl << "====================" << "===== �α��� =====" << endl;
	cout << "ID : ";	cin >> id;
	cout << "PASSWORD : ";	cin >> password;

	exist = IsUser(id, &serial_num);
	if (!exist || serial_num == -1) {
		cout << "�ùٸ� ���̵� �����ϴ�." << endl;
		return serial_num;
	}
	cout <<serial_num<< "�α��� �Ǽ̽��ϴ�. �Ǽ̽��ϴ�!!" << endl;
	
	exist = IsJob(&serial_num);
	if (!exist)
	{
		if (m_member[serial_num]->IsClass())
			return serial_num;
		lua_getglobal(main_lua, "SelectCharacter");
		lua_pcall(main_lua, 0, 7, 0);

		const char * temp_job = lua_tostring(main_lua, -1);
		int temp_level = lua_tointeger(main_lua, -2);
		float temp_exp = lua_tonumber(main_lua, -3);
		int temp_hp = lua_tointeger(main_lua, -4);
		int temp_mp = lua_tointeger(main_lua, -5);
		int temp_dam = lua_tointeger(main_lua, -6);
		int temp_def = lua_tointeger(main_lua, -7);
		m_member[serial_num]->SetNewChamp(temp_job, temp_level, temp_exp, temp_hp, temp_mp, temp_dam, temp_def);
	}
	else
		cout << "ĳ���Ͱ� �����մϴ�." << endl;
	lua_pop(main_lua, 7);


	return serial_num;
}




void CLogIn::ChangePassword()
{
	bool exist = false;
	int serial_num = -1;
	char id[BUFFER_SIZE];
	char new_password[BUFFER_SIZE];

	ZeroMemory(id, sizeof(char)*BUFFER_SIZE);
	ZeroMemory(new_password, sizeof(char)*BUFFER_SIZE);

	cout << "���̵� �Է����ּ��� : ";
	cin >> id;

	exist = IsUser(id, &serial_num);
	if (!exist || serial_num ==-1) {
		cout << "�ùٸ� ���̵� �����ϴ�." << endl;
		return;
	}

	lua_getglobal(m_member[serial_num]->LUA(), "my_password");
	const char* password = lua_tostring(m_member[serial_num]->LUA(), -1);
	
	cout << "���� ��й�ȣ : " << password << endl;
	cout << "���ο� �����ȣ : ";
	cin >> new_password;

	lua_pushstring(m_member[serial_num]->LUA(), new_password);
	lua_setglobal(m_member[serial_num]->LUA(), "my_password");
	lua_pop(m_member[serial_num]->LUA(), 2);
}


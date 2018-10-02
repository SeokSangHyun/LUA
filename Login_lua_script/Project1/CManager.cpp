#include "CManager.h"

using namespace std;

CManager::CManager()
{
	for (int i = 0; i < MAX_USER; ++i)
		m_member[i] = new CMember();
	main_lua = luaL_newstate();
	luaL_openlibs(main_lua);

	lua_register(main_lua, "API_CharacterList", API_CharacterList);

	if (luaL_loadfile(main_lua, "./lua_Manager.lua") || lua_pcall(main_lua, 0, 0, 0)) {
		printf("%s\n", lua_tostring(main_lua, -1));
		lua_pop(main_lua, 1);
	}
	FileLoad(".\\User_data.txt");
}
CManager::~CManager()
{
	for (int i = 0; i < MAX_USER; ++i)
	{
		delete m_member[i];
	}
	lua_close(main_lua);
}

void CManager::FileLoad(const char* str_path)
{
	lua_getglobal(main_lua, "DataLoad");
	lua_pushstring(main_lua, str_path);

	lua_pcall(main_lua, 1, 1, 0);
	const char* str_temp = lua_tostring(main_lua, -1);
	lua_pop(main_lua, 1);

	int str_len = strlen(str_temp) + 1;
	if (str_len == 1) return;

	int idTurn = 0;
	char str_id[BUFFER_SIZE] = "\0";
	char str_password[BUFFER_SIZE] = "\0";
	char str_job[BUFFER_SIZE] = "\0";
	int j = 0, k = 0;

	for (int i = 0; i < str_len+1; ++i) {
		if (str_temp[i] == ' ' || str_temp[i] == '\n' || str_temp[i] == '\0')
		{
			idTurn = (idTurn + 1) % 3;
			k = 0;
			if (str_temp[i] == '\n' || str_temp[i] == '\0') {
 				m_member[j]->SetInfo(str_id, str_password, str_job);

				ZeroMemory(str_id, BUFFER_SIZE);
				ZeroMemory(str_password, BUFFER_SIZE);
				ZeroMemory(str_job, BUFFER_SIZE);
				++j;
			}
			++i;
		}
		
		if(idTurn==0)
			str_id[k] = str_temp[i];
		else if(idTurn==1)
			str_password[k] = str_temp[i];
		else
			str_job[k] = str_temp[i];
		k++;
	}
}

void CManager::FileSave()
{
	const char *file_name = ".\\User_data.txt";
	string str_temp;
	char temp[BUFFER_SIZE] = "\0";

	for (int i = 0; i < MAX_USER; ++i) {
		if (m_member[i]->GetIsLogin()) {
			str_temp.append(m_member[i]->GetId());
			str_temp.append(" ");

			str_temp.append(m_member[i]->GetPassword());
			str_temp.append(" ");
			
			//durlÇØ
			strcpy_s(temp, sizeof(temp), m_member[i]->Getjob());
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetLevel(), temp, 10);
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetExp(), temp, 10);
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetHp(), temp, 10);
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetMp(), temp, 10);
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetDamage(), temp, 10);
			str_temp.append(temp);
			str_temp.append("/");

			itoa(m_member[i]->GetDefense(), temp, 10);
			str_temp.append(temp);
			str_temp.append("\n");
		}
	}

	lua_getglobal(main_lua, "DataSave");
	lua_pushstring(main_lua, file_name);
	lua_pushstring(main_lua, str_temp.data());
	lua_pcall(main_lua, 2, 0, 0);
	lua_pop(main_lua, 1);

}



bool CManager::IsUser(const char* id, int* num)
{
	for (int i = 0; i < MAX_USER; ++i)
	{
		if (!strcmp(m_member[i]->GetId(), id)) {
			*num = i;
			return true;
		}
	}
	return false;
}

bool CManager::IsJob(int * num)
{
	const char *temp = m_member[*num]->Getjob();

	if (strcmp(temp, "nono") == 0)
		return false;
	return true;
}



int CManager::SelectMode()
{
	int act = 0;
	cout << "==========" << endl;
	cout << "=1. ½Î¿ò =" << endl;
	cout << "==========" << endl;
	cout << "¼±ÅÃ :" << endl;
	cin >> act;

	return act;
}

void CManager::ShowAllMemberInfo()
{
	for (int i = 0; i < MAX_USER; ++i)
		m_member[i]->PersonalShow();
}

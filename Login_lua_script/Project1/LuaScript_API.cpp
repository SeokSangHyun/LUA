
#include "LuaScript_API.h"


//
int API_CharacterList(lua_State *new_state)
{
	int count_method = 0;

	int top = lua_gettop(new_state);
	std::cout << "==============================" << std::endl;
	lua_pushstring(new_state, "����");
	lua_gettable(new_state, top);
	std::cout << "����" << std::endl;

		lua_pushstring(new_state, "hp");
		lua_gettable(new_state, top + 1);
		int info = lua_tointeger(new_state, -1);
		std::cout << "hp : "<< info << std::endl;
		lua_pop(new_state, 1);
		
		lua_pushstring(new_state, "mp");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "mp : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "damage");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "damage : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "def");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "def : " << info << std::endl;
		lua_pop(new_state, 1);

	lua_pop(new_state, 1);

	std::cout << "----------------------------------" << std::endl;
	lua_pushstring(new_state, "�ü�"); count_method++;//���� Ű�� ���ÿ� Ǫ��
	lua_gettable(new_state, top); count_method;//1��° ���̺���
	std::cout << "�ü�" << std::endl;

		lua_pushstring(new_state, "hp");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "hp : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "mp");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "mp : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "damage");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "damage : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "def");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "def : " << info << std::endl;
		lua_pop(new_state, 1);

	lua_pop(new_state, 1);

	std::cout << "----------------------------------" << std::endl;
	lua_pushstring(new_state, "������"); count_method++;//���� Ű�� ���ÿ� Ǫ��
	lua_gettable(new_state, top); count_method;//1��° ���̺���
	std::cout << "������" << std::endl;

		lua_pushstring(new_state, "hp");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "hp : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "mp");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "mp : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "damage");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "damage : " << info << std::endl;
		lua_pop(new_state, 1);

		lua_pushstring(new_state, "def");
		lua_gettable(new_state, top + 1);
		info = lua_tointeger(new_state, -1);
		std::cout << "def : " << info << std::endl;
		lua_pop(new_state, 1);

	lua_pop(new_state, 1);

	std::cout << "==============================" << std::endl;

	char job[BUFFER_SIZE] = "\0";
	while (true)
	{
		std::cout << "====ĳ���� ����" << std::endl;
		std::cin >> job;

		if (strcmp(job, "����") == 0 || strcmp(job, "�ü�") == 0 || strcmp(job, "������") == 0)
			break;
		std::cout << "�˸��� ������ �����ϼ���!!!!!!!" << std::endl;
	}

	lua_pushstring(new_state, job);
	return 1;
}
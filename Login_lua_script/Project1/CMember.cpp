#include "CMember.h"



CMember::CMember()
{
	m_IsLogin = false;

	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);

	//필요한 함수들 추가
	if (luaL_loadfile(m_lua, "./test.lua") || lua_pcall(m_lua, 0, 0, 0)) {
		printf("%s\n", lua_tostring(m_lua, -1));
		lua_pop(m_lua, 1);
	}
}

CMember::~CMember()
{
	lua_close(m_lua);
}


bool CMember::IsClass() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);
	lua_gettable(m_lua, top);

	bool tf = lua_istable(m_lua, top);
	lua_pop(m_lua, 1);

	return tf;
}



const char * CMember::GetId() const
{
	lua_getglobal(m_lua, "my_id");
	const char *id = lua_tostring(m_lua, -1);
	lua_pop(m_lua, 1);
	return id;
}

const char* CMember::GetPassword() const
{
	lua_getglobal(m_lua, "my_password");
	const char *password = lua_tostring(m_lua, -1);
	lua_pop(m_lua, 1);
	return password;
}

const char * CMember::Getjob() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "job");
	lua_gettable(m_lua, top);
	
	if (lua_isstring(m_lua, -1)) {
		const char *job = lua_tostring(m_lua, -1);
		lua_pop(m_lua, 2);
		return job;
	}
	else
		return "nono";
}

int CMember::GetLevel() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "level");
	lua_gettable(m_lua, top);
	int level = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return level;
}

float CMember::GetExp() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "exp");
	lua_gettable(m_lua, top);
	int exp = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return exp;
}

int CMember::GetHp() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "hp");
	lua_gettable(m_lua, top);
	int hp = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return hp;
}

int CMember::GetMp() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "mp");
	lua_gettable(m_lua, top);
	int mp = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return mp;
}

int CMember::GetDamage() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "damage");
	lua_gettable(m_lua, top);
	int dam = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return dam;
}

int CMember::GetDefense() const
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "def");
	lua_gettable(m_lua, top);
	int def = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 2);
	return def;
}

void CMember::SetInfo(const char * id, const char * password, const char * job)
{
	m_IsLogin = true;
	lua_pushstring(m_lua, id);
	lua_pushstring(m_lua, password);

	lua_setglobal(m_lua, "my_password");
	lua_setglobal(m_lua, "my_id");

	int len = strlen(job);
	char temp[BUFFER_SIZE] = "\0";
	char temp_job[BUFFER_SIZE] = "\0";
	int level = 1;
	float exp = 0.f;
	int hp = 0, mp = 0, dam = 0, def = 0;
	int j = 0, k = 0;
	for (int i = 0; i < len+1; ++i) {
		if (job[i] == '/'|| job[i] == '\0') {
			switch (k) {
			case 0: strcpy_s(temp_job, BUFFER_SIZE, temp);	break;
			case 1: level = atoi(temp); break;
			case 2: exp = atof(temp); break;
			case 3: hp = atoi(temp); break;
			case 4: mp = atoi(temp); break;
			case 5: dam = atoi(temp); break;
			case 6: def = atoi(temp); break;
			default: break;
			}
			i++;
			j = 0;
			k++;
			ZeroMemory(temp, sizeof(temp));
		}
		temp[j] = job[i];
		j++;
	}
	SetNewChamp(temp_job, level, exp, hp, mp, dam, def);
}

void CMember::SetLevelExp(int level, float exp)
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);

	lua_pushstring(m_lua, "level");
	lua_pushnumber(m_lua, level);
	lua_settable(m_lua, top);

	lua_pushstring(m_lua, "exp");
	lua_pushnumber(m_lua, exp);
	lua_settable(m_lua, top);

	lua_pop(m_lua, 1);
}

void CMember::SetNewChamp(const char* job, const int lv, const float exp, const int hp, const int mp, const int dam, const int def)
{
	lua_getglobal(m_lua, "my_info");
	int top = lua_gettop(m_lua);
	lua_newtable(m_lua);

		lua_pushstring(m_lua, "job");
		lua_pushstring(m_lua, job);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "level");
		lua_pushnumber(m_lua, lv);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "exp");
		lua_pushnumber(m_lua, exp);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "hp");
		lua_pushnumber(m_lua, hp);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "mp");
		lua_pushnumber(m_lua, mp);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "damage");
		lua_pushnumber(m_lua, dam);
		lua_settable(m_lua, top);

		lua_pushstring(m_lua, "def");
		lua_pushnumber(m_lua, def);
		lua_settable(m_lua, top);
}

void CMember::PersonalShow()
{
	lua_getglobal(m_lua, "showAll");
	lua_pcall(m_lua, 0, 0, 0);
}






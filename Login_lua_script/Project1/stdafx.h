#pragma once

#include <iostream>
#include <Windows.h>
#include <stdlib.h>

#include <string>

extern "C" {
#include "LuaScript\lauxlib.h"
#include "LuaScript\lua.h"
#include "LuaScript\lualib.h"
}
#pragma comment(lib, "lua53.lib")

#define MAX_USER 50
#define BUFFER_SIZE 128


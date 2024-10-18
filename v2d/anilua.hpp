#pragma once
#include "DxLib.h"
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
#include <vector>
#include "vector.hpp"
#include "sprite.hpp"

class AniLua {
public:
	AniLua(std::string path);
	void CallNext(Sprite* head, Sprite* body, Sprite* eye1, Sprite* eye2, Sprite* mouth);
private:
	lua_State* L;
};

extern std::vector<AniLua> aniluas;
extern int startms;

void GetAniluaState(Sprite *head, Sprite *body, Sprite *eye1, Sprite *eye2, Sprite *mouth);

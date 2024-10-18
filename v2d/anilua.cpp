#include "anilua.hpp"

std::vector<AniLua> aniluas;
int startms;
bool is_running = true;

#pragma region Lua Globals
int Lprint(lua_State* Le) {
	const char* str = luaL_checkstring(Le, 1);
	printfDx(str);
	return 0;
}

int Lclear(lua_State* Le) {
	clsDx();
	return 0;
}

int LloadGraph(lua_State* Le) {
	int id = LoadGraph(luaL_checkstring(Le, 1));
	lua_pushinteger(Le, id);
	return 1;
}

int LdeleteGraph(lua_State* Le) {
	int id = luaL_checkinteger(Le, 1);
	DeleteGraph(id);
	return 0;
}

#pragma endregion

AniLua::AniLua(std::string path) {
	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L, path.c_str());

	lua_pushcfunction(L, Lprint);
	lua_setglobal(L, "print");

	lua_pushcfunction(L, Lclear);
	lua_setglobal(L, "cls");

	lua_pushcfunction(L, LloadGraph);
	lua_setglobal(L, "loadGraph");

	lua_pushcfunction(L, LdeleteGraph);
	lua_setglobal(L, "deleteGraph");

	if (lua_pcall(L, 0, 0, 0) != 0) {
		printfDx("AniLuaスクリプトでエラーが発生しました:\n%s\n", lua_tostring(L, -1));
		lua_close(L);
		throw;
	}
	else {
		lua_getglobal(L, "Initialize");
		if (lua_pcall(L, 0, 0, 0) != 0) {
			printfDx("AniLuaの初期化スクリプトでエラーが発生しました:\n%s\n", lua_tostring(L, -1));
			lua_close(L);
			throw;
		}
	}
}

#pragma region SetToLua

void PushVectorTable(lua_State* L, vct2d vec, const char* name) {
	lua_pushstring(L, name);
	lua_newtable(L);

	lua_pushstring(L, "x");
	lua_pushnumber(L, vec.x);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, vec.y);
	lua_settable(L, -3);

	lua_settable(L, -3);
}

void PushSpriteTable(lua_State* L, Sprite sprite, const char* name) {
	lua_pushstring(L, name);
	lua_newtable(L);

	PushVectorTable(L, sprite.Cent, "Cent");
	PushVectorTable(L, sprite.Pos, "Pos");
	PushVectorTable(L, sprite.Stren, "Stren");

	lua_pushstring(L, "Deg");
	lua_pushnumber(L, sprite.Deg);
	lua_settable(L, -3);

	lua_pushstring(L, "Image");
	lua_pushinteger(L, sprite.Image);
	lua_settable(L, -3);

	lua_pushstring(L, "Size");
	lua_pushnumber(L, sprite.Size);
	lua_settable(L, -3);

	lua_pushstring(L, "isFlip");
	lua_pushnumber(L, sprite.isFlip ? 1 : 0);
	lua_settable(L, -3);

	lua_settable(L, -3);
}

#pragma endregion

#pragma region SetToV2d

vct2d ReadVectorTable(lua_State* L, const char* name) {
	vct2d vect;
	lua_getfield(L, -1, name);
	lua_getfield(L, -1, "x");
	vect.x = luaL_checknumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, -1, "y");
	vect.y = luaL_checknumber(L, -1);
	lua_pop(L, 2);
	return vect;
}

void ReadSpriteTable(lua_State* L, Sprite* sprite, const char* name) {
	lua_getglobal(L, "V2d");
	lua_getfield(L, -1, name);

	lua_getfield(L, -1, "Deg");
	sprite->Deg = luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "Image");
	sprite->Image = luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "Size");
	sprite->Size = luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "isFlip");
	sprite->isFlip = (luaL_checknumber(L, -1) != 0);
	lua_pop(L, 1);

	sprite->Pos = ReadVectorTable(L, "Pos");
	sprite->Cent = ReadVectorTable(L, "Cent");
	sprite->Stren = ReadVectorTable(L, "Stren");
	lua_pop(L,2);
}

#pragma endregion

void AniLua::CallNext(Sprite *head, Sprite* body, Sprite* eye1, Sprite* eye2, Sprite* mouth) {
	lua_settop(L,0);
	lua_newtable(L);
	PushSpriteTable(L, *head, "Head");
	PushSpriteTable(L, *body, "Body");
	PushSpriteTable(L, *eye1, "Eye1");
	PushSpriteTable(L, *eye2, "Eye2");
	PushSpriteTable(L, *mouth, "Mouth");
	lua_setglobal(L, "V2d");

	lua_getglobal(L, "Frame"); //Func
	lua_pushnumber(L, GetNowCount() - startms);
	try {
		if (lua_pcall(L, 1, 1, 0) != 0) {
			printfDx("AniLuaの常時スクリプト内でエラーが発生しました:%s\n", lua_tostring(L, -1));
			lua_close(L);
			throw;
		}
		else {
			ReadSpriteTable(L, head, "Head");
			ReadSpriteTable(L, body, "Body");
			ReadSpriteTable(L, eye1, "Eye1");
			ReadSpriteTable(L, eye2, "Eye2");
			ReadSpriteTable(L, mouth, "Mouth");
		}
	}
	catch(...){
		printfDx("AniLuaで例外が発生しました。");
		lua_close(L);
		throw;
	}
}

void GetAniluaState(Sprite* head, Sprite* body, Sprite* eye1, Sprite* eye2, Sprite* mouth) {
	if (!is_running) return;
	try {
		for (int i = 0; i < (int)aniluas.size(); i++)
			aniluas[i].CallNext(head, body, eye1, eye2, mouth);
	}
	catch(...){
		is_running = false;
	}
}

void ClearAniLua() {
	aniluas.clear();
}

void AddAniLua(AniLua data) {
	aniluas.push_back(data);
}

void SetStartMs() {
	startms = GetNowCount();
}
#include "anilua.hpp"

std::string path;
lua_State* L;
bool is_loading = true;
int startms;

#pragma region SetToLua

void PushVectorTable(vct2d vec, const char* Sname, const char* name) {
	lua_newtable(L);

	lua_pushnumber(L, vec.x);
	lua_setfield(L, -2, "x");

	lua_pushnumber(L, vec.y);
	lua_setfield(L, -2, "y");

	lua_setfield(L, -2, name);
}

void PushSpriteTable(Sprite sprite, const char* name) {
	lua_getglobal(L, "V2d");
	lua_newtable(L);

	PushVectorTable(sprite.Cent, name, "Cent");
	PushVectorTable(sprite.Pos, name, "Pos");
	PushVectorTable(sprite.Stren, name, "Stren");

	lua_pushnumber(L, sprite.Deg);
	lua_setfield(L, -2, "Deg");

	lua_pushnumber(L, sprite.Size);
	lua_setfield(L, -2, "Size");

	lua_pushnumber(L, sprite.isFlip ? 1 : 0);
	lua_setfield(L, -2, "isFlip");

	lua_setfield(L, -2, name);
}

#pragma endregion

#pragma region SetToV2d

vct2d ReadVectorTable(const char* Sname,const char* Vname) {
	lua_getglobal(L, "V2d");
	lua_getfield(L, -1, Sname);
	lua_getfield(L, -1, Vname);
	lua_getfield(L, -1, "x");
	lua_getfield(L, -2, "y");
	vct2d vect;
	vect.x = luaL_checknumber(L, -2);
	vect.y = luaL_checknumber(L, -1);
	return vect;
}

void ReadSpriteTable(Sprite* sprite, const char* name) {
	sprite->Pos = ReadVectorTable(name, "Pos");
	sprite->Cent = ReadVectorTable(name, "Cent");
	sprite->Stren = ReadVectorTable(name, "Stren");
	lua_getglobal(L, "V2d");
	lua_getfield(L, -1, name); //[V2d, Sprite, NULL]
	lua_getfield(L, -1, "Deg");
	lua_getfield(L, -2, "Size"); // -5     -4     -3   -2    -1
	lua_getfield(L, -3, "isFlip"); //[V2d, Sprite, Deg, Size, Flip]
	sprite->Deg = luaL_checknumber(L, -3);
	sprite->Size = luaL_checknumber(L, -2);
	sprite->isFlip = luaL_checknumber(L, -1) == 1;
}

#pragma endregion


void GetAniluaState(Sprite *head, Sprite* body, Sprite* eye1, Sprite* eye2, Sprite* mouth) {
	if (is_loading) return;
	lua_newtable(L);
	lua_setglobal(L, "V2d");
	PushSpriteTable(*head, "Head");
	PushSpriteTable(*body, "Body");
	PushSpriteTable(*eye1, "Eye1");
	PushSpriteTable(*eye2, "Eye2");
	PushSpriteTable(*mouth, "Mouth");
	lua_getglobal(L, "Frame"); //Func
	lua_pushnumber(L, GetNowCount() - startms);
	if (lua_pcall(L, 1, 1, 0) != 0) {
		printfDx("AniLuaでエラーが発生しました☆:%s\n", lua_tostring(L, -1));
		lua_close(L);
		is_loading = true;
		return;
	}
	else {
		/*ReadSpriteTable(head, "Head");
		ReadSpriteTable(body, "Body");
		ReadSpriteTable(eye1, "Eye1");
		ReadSpriteTable(eye2, "Eye2");
		ReadSpriteTable(mouth, "Mouth");*/
		if (!lua_toboolean(L, -1)) {
			lua_close(L);
			is_loading = true;
			return;
		}
	}
}

int Lprint(lua_State* Le) {
	const char* str = luaL_checkstring(Le, 1);
	printfDx(str);
	return 1;
}

int Lclear(lua_State* Le) {
	clsDx();
	return 1;
}

void AniLuaMsg(WPARAM wp, LPARAM lp) {
	switch (wp) {
	case 0: //Initialize
		is_loading = true;
		path.clear();
		break;
	case 1: //Input
		path.append((char*)&lp);
		break;
	case 2: //Load
		startms = GetNowCount();
		L = luaL_newstate();
		luaL_openlibs(L);
		luaL_loadfile(L, path.c_str());

		lua_pushcfunction(L, Lprint);
		lua_setglobal(L, "print");

		lua_pushcfunction(L, Lclear);
		lua_setglobal(L, "cls");

		if (lua_pcall(L, 0, 0, 0) != 0) {
			printfDx("AniLuaでエラーが発生しました:\n%s\n", lua_tostring(L, -1));
			lua_close(L);
		}
		else {
			lua_getglobal(L, "Initialize");
			if (lua_pcall(L, 0, 0, 0) != 0) {
				printfDx("AniLuaの初期化関数でエラーが発生しました:\n%s\n", lua_tostring(L, -1));
				lua_close(L);
			}
			else {
				is_loading = false;
			}
		}
		break;
	}
}
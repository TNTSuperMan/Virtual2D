#pragma once
#include "DxLib.h"
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
#include "vector.hpp"
#include "sprite.hpp"

void GetAniluaState(Sprite *head, Sprite *body, Sprite *eye1, Sprite *eye2, Sprite *mouth);

void AniLuaMsg(WPARAM wp, LPARAM lp);
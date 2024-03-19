#pragma once
#include <DxLib.h>
#include <string>
#include <future>
#include <nlohmann/json.hpp>
#include "Dialog.h"
using json = nlohmann::json;

//size_t callbackWrite(char* ptr, size_t size, size_t nmemb, string* stream);
void Say(const char* rs);
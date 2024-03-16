#pragma once
#include <DxLib.h>
#include <string>
#include <future>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/header.h>
#include <curl/mprintf.h>
#include <curl/multi.h>
#include <curl/options.h>
#include <curl/system.h>
#include <curl/urlapi.h>
#include <curl/websockets.h>
#include "Dialog.h"
using json = nlohmann::json;

//size_t callbackWrite(char* ptr, size_t size, size_t nmemb, string* stream);
void Say(const char* rs);
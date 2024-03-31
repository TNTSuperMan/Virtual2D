#include "Setting.h"
#include "Dialog.h"
using json = nlohmann::json;
#define sett(name, type ) name = j[#name].get<type>();
#define set(name) name = j[#name].get<int>();

Setting::Setting() {
	std::ifstream cfg(".\\model\\model.json");
	if (!cfg || cfg.fail()) {
		Dialog("設定ファイル\".\\model\\model.json\"にアクセスできません。");
		return;
	}
	char c;
	json j;
	std::string fd;
	while ((c = cfg.get()) != -1) {
		fd += c;
	}
	cfg.close();
	try {
		j = json::parse(fd);
		sett(backgroundColor, unsigned int);
		sett(GetdownMode, bool);
		set(BodyY);
		set(BodyCentY);
		set(BodySize);
		set(neckY);
		set(HeadY);
		set(HeadSize);
		set(EyePos);
		set(EyeSize);
		set(EyeKankaku);
		set(MabatakiKankaku);
		set(MabatakiTime);
		set(MabatakiSize);
		set(BodyFurehaba);
		set(HeadFurehaba);
		set(FureSpeed);
		set(EyePointerSize);
		set(HeadPointerSize);
		set(PointerHoseX);
		set(PointerHoseY);
	}
	catch (...) {
		Dialog(".\\model\\mode.jsonの記述が不正です。");
	}

}
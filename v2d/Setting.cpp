#include "Setting.h"
#include "Dialog.h"
using json = nlohmann::json;

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
		backgroundColor = j["backgroundColor"].get<unsigned int>();
		BodyY = j["BodyY"].get<int>();
		BodyCentY = j["BodyCentY"].get<int>();
		BodySize = j["BodySize"].get<int>();
		neckY = j["neckY"].get<int>();
		HeadY = j["HeadY"].get<int>();
		HeadSize = j["HeadSize"].get<int>();
		EyePos = j["EyePos"].get<int>();
		EyeSize = j["EyeSize"].get<int>();
		EyeKankaku = j["EyeKankaku"].get<int>();
		BodyFurehaba = j["BodyFurehaba"].get<int>();
		HeadFurehaba = j["HeadFurehaba"].get<int>();
		FureSpeed = j["FureSpeed"].get<int>();
		GetdownMode = j["GetdownMode"].get<int>();
		EyePointerSize = j["EyePointerSize"].get<int>();
		HeadPointerSize = j["HeadPointerSize"].get<int>();
		PointerHoseX = j["PointerHoseX"].get<int>();
		PointerHoseY = j["PointerHoseY"].get<int>();
	}
	catch (...) {
		Dialog("ちゃんとa.txtかきやがれ");
	}

}
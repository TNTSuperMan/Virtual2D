#include "setting.hpp"
#include "dialog.hpp"
using json = nlohmann::json;
#define sett(name, type ) name = j[#name].get<type>();
#define set(name) sett(name,int)

Setting::Setting() {
	std::ifstream cfg(".\\model\\model.json");
	if (!cfg || cfg.fail()) {
		Dialog("�ݒ�t�@�C��\".\\model\\model.json\"�ɃA�N�Z�X�ł��܂���B");
		return;
	}
	char c;
	json j;
	std::string fd;
	ClearAniLua();
	while ((c = cfg.get()) != -1)
		fd += c;
	
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
		set(MouthSize);
		set(CloseMouthSize);
		set(MouthY);
		set(MouthPointerSize);
		if (j["aniluas"].is_array()) {
			for (json::iterator it = j["aniluas"].begin(); it != j["aniluas"].end(); ++it) {
				AddAniLua(AniLua(*it));
			}
		}
		if (HeadPointerSize == 0) {
			Dialog(".\\model\\model.json�̐ݒ�\"HeadPointerSize\"��0�ł��B\n0�ȊO�ɂ��Ă��������B");
			return;
		}
		isInitialized = true;
	}
	catch (...) {
		Dialog(".\\model\\model.json�̋L�q���s���ł��B");
	}

}
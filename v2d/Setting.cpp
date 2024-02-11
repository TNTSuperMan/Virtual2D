#include "Setting.h"
Setting::Setting() {
	ifstream cfg(".\\model\\model.txt");
	if (!cfg || cfg.fail()) {
		MessageBoxA(NULL, "設定ファイル\".\\model\\model.txt\"にアクセスできません。", APP_NAME, MB_OK);
		return;
	}
	cfg >> backgroundColor >> BodyY >>
		BodyCentY >> BodySize >> neckY >>
		HeadY >> HeadSize >> EyePos >> EyeSize >>
		EyeKankaku >> BodyFurehaba >> HeadFurehaba >>
		FureSpeed >> GetdownMode;
	cfg.close();
}
#include "Dialog.h"
void Dialog(const char* msg) {
	 MessageBoxA(GetMainWindowHandle(), msg, APP_NAME, MB_OK);
}
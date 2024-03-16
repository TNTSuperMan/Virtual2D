#define _CRT_SECURE_NO_WARNINGS
#include "getvoice.h"

using namespace std;

size_t callbackWrite(void* contents, size_t size, size_t nmemb, void* userp)
{
	//((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string fetch(const char* url) {
	CURL* curl = curl_easy_init();
	CURLcode ret;
	string chunk;
	if (curl == NULL) {
		return NULL;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
	ret = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (ret != CURLE_OK) {
		return "NULL";
	}
	return chunk;
}

void Say(const char* rs){
	#pragma region ローマ字変換
	string h;
	int  orl = 0;
	while (orl < strlen(rs)) {
		switch (tolower(rs[orl])) {
			case 'a':
				h.append("あ");
				break;
			case 'i':
				h.append("い");
				break;
			case 'u':
				h.append("う");
				break;
			case 'e':
				h.append("え");
				break;
			case 'o':
				h.append("お");
				break;
			case '-':
				h.append("ー");
				break;
			case '.':
				h.append("。");
				break;
			case ',':
				h.append("、");
				break;
			case '/':
				break;
			case 'k':
			case 'c':
				k:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'k':
						h.append("っ");
						goto k;
						break;
					case 'a':
						h.append("か");
						break;
					case 'i':
						h.append("き");
						break;
					case 'u':
						h.append("く");
						break;
					case 'e':
						h.append("け");
						break;
					case 'o':
						h.append("こ");
						break;
				}
				break;
			case 's':
				s:;
				orl++;
				switch (tolower(rs[orl])) {
					case 's':
						h.append("っ");
						goto s;
						break;
					case 'a':
						h.append("さ");
						break;
					case 'i':
						h.append("し");
						break;
					case 'u':
						h.append("す");
						break;
					case 'e':
						h.append("せ");
						break;
					case 'o':
						h.append("そ");
						break;
				}
				break;
			case 't':
				t:;
				orl++;
				switch (tolower(rs[orl])) {
					case 't':
						h.append("っ");
						goto t;
						break;
					case 'a':
						h.append("た");
						break;
					case 'i':
						h.append("ち");
						break;
					case 'u':
						h.append("つ");
						break;
					case 'e':
						h.append("て");
						break;
					case 'o':
						h.append("と");
						break;
					}
				break;
			case 'n':
				orl++;
				switch (tolower(rs[orl])) {
					case 'n':
						h.append("ん");
						break;
					case 'a':
						h.append("な");
						break;
					case 'i':
						h.append("に");
						break;
					case 'u':
						h.append("ぬ");
						break;
					case 'e':
						h.append("ね");
						break;
					case 'o':
						h.append("の");
						break;
					default:
						h.append("ん");
						orl--;
						break;

				}
				break;
			case 'h':
				h:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'h':
						h.append("っ");
						goto h;
						break;
					case 'a':
						h.append("は");
						break;
					case 'i':
						h.append("ひ");
						break;
					case 'u':
						h.append("ふ");
						break;
					case 'e':
						h.append("へ");
						break;
					case 'o':
						h.append("ほ");
						break;
				}
				break;
			case 'm':
				orl++;
				switch (tolower(rs[orl])) {
					case 'a':
						h.append("ま");
						break;
					case 'i':
						h.append("み");
						break;
					case 'u':
						h.append("む");
						break;
					case 'e':
						h.append("め");
						break;
					case 'o':
						h.append("も");
						break;
				}
				break;
			case 'y':
				orl++;
				switch (tolower(rs[orl])) {
					case 'a':
						h.append("や");
						break;
					case 'u':
						h.append("ゆ");
						break;
					case 'e':
						h.append("いぇ");
						break;
					case 'o':
						h.append("よ");
						break;
				}
				break;
			case 'r':
				r:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'r':
						h.append("っ");
						goto r;
						break;
					case 'a':
						h.append("ら");
						break;
					case 'i':
						h.append("り");
						break;
					case 'u':
						h.append("る");
						break;
					case 'e':
						h.append("れ");
						break;
					case 'o':
						h.append("ろ");
						break;
				}
				break;
			case 'w':
				w:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'w':
					h.append("っ");
					goto w;
				case 'a':
					h.append("わ");
					break;
				case 'o':
					h.append("を");
					break;
				}
				break;
			case 'g':
				g:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'g':
						h.append("っ");
						goto g;
						break;
					case 'a':
						h.append("が");
						break;
					case 'i':
						h.append("ぎ");
						break;
					case 'u':
						h.append("ぐ");
						break;
					case 'e':
						h.append("げ");
						break;
					case 'o':
						h.append("ご");
						break;
				}
				break;
			case 'z':
				z:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'z':
					h.append("っ");
					goto z;
					break;
				case 'a':
					h.append("ざ");
					break;
				case 'i':
					h.append("じ");
					break;
				case 'u':
					h.append("ず");
					break;
				case 'e':
					h.append("ぜ");
					break;
				case 'o':
					h.append("ぞ");
					break;
				}
				break;
			case 'd':
				d:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'd':
						h.append("っ");
						goto d;
						break;
					case 'a':
						h.append("だ");
						break;
					case 'i':
						h.append("ぢ");
						break;
					case 'u':
						h.append("づ");
						break;
					case 'e':
						h.append("で");
						break;
					case 'o':
						h.append("ど");
						break;
				}
				break;
			case 'b':
			b:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'b':
					h.append("っ");
					goto b;
					break;
				case 'a':
					h.append("ば");
					break;
				case 'i':
					h.append("び");
					break;
				case 'u':
					h.append("ぶ");
					break;
				case 'e':
					h.append("べ");
					break;
				case 'o':
					h.append("ぼ");
					break;
				}
				break;
			case 'j':
				j:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'j':
					h.append("っ");
					goto j;
					break;
				case 'a':
					h.append("じゃ");
					break;
				case 'i':
					h.append("じ");
					break;
				case 'u':
					h.append("じゅ");
					break;
				case 'e':
					h.append("じぇ");
					break;
				case 'o':
					h.append("じょ");
					break;
				}
				break;
			case 'f':
			f:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'f':
					h.append("っ");
					goto f;
					break;
				case 'a':
					h.append("ふぁ");
					break;
				case 'i':
					h.append("ふぃ");
					break;
				case 'u':
					h.append("ふ");
					break;
				case 'e':
					h.append("ふぇ");
					break;
				case 'o':
					h.append("ふぉ");
					break;
				}
				break;
			default:
				h.append(" ");
				break;
		}
		orl++;
	}
	#pragma endregion

	const char* say = h.c_str();

	#pragma region 音声をリクエスト
	//auto voice = thread([say] {
		curl_global_init(CURL_GLOBAL_ALL);

		printfDx("あ\n");
		#pragma region /audio_query
		#pragma endregion
	//});
	#pragma endregion

}
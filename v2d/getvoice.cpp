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
	#pragma region ���[�}���ϊ�
	string h;
	int  orl = 0;
	while (orl < strlen(rs)) {
		switch (tolower(rs[orl])) {
			case 'a':
				h.append("��");
				break;
			case 'i':
				h.append("��");
				break;
			case 'u':
				h.append("��");
				break;
			case 'e':
				h.append("��");
				break;
			case 'o':
				h.append("��");
				break;
			case '-':
				h.append("�[");
				break;
			case '.':
				h.append("�B");
				break;
			case ',':
				h.append("�A");
				break;
			case '/':
				break;
			case 'k':
			case 'c':
				k:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'k':
						h.append("��");
						goto k;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 's':
				s:;
				orl++;
				switch (tolower(rs[orl])) {
					case 's':
						h.append("��");
						goto s;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 't':
				t:;
				orl++;
				switch (tolower(rs[orl])) {
					case 't':
						h.append("��");
						goto t;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
					}
				break;
			case 'n':
				orl++;
				switch (tolower(rs[orl])) {
					case 'n':
						h.append("��");
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
					default:
						h.append("��");
						orl--;
						break;

				}
				break;
			case 'h':
				h:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'h':
						h.append("��");
						goto h;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'm':
				orl++;
				switch (tolower(rs[orl])) {
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'y':
				orl++;
				switch (tolower(rs[orl])) {
					case 'a':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("����");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'r':
				r:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'r':
						h.append("��");
						goto r;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'w':
				w:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'w':
					h.append("��");
					goto w;
				case 'a':
					h.append("��");
					break;
				case 'o':
					h.append("��");
					break;
				}
				break;
			case 'g':
				g:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'g':
						h.append("��");
						goto g;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'z':
				z:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'z':
					h.append("��");
					goto z;
					break;
				case 'a':
					h.append("��");
					break;
				case 'i':
					h.append("��");
					break;
				case 'u':
					h.append("��");
					break;
				case 'e':
					h.append("��");
					break;
				case 'o':
					h.append("��");
					break;
				}
				break;
			case 'd':
				d:;
				orl++;
				switch (tolower(rs[orl])) {
					case 'd':
						h.append("��");
						goto d;
						break;
					case 'a':
						h.append("��");
						break;
					case 'i':
						h.append("��");
						break;
					case 'u':
						h.append("��");
						break;
					case 'e':
						h.append("��");
						break;
					case 'o':
						h.append("��");
						break;
				}
				break;
			case 'b':
			b:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'b':
					h.append("��");
					goto b;
					break;
				case 'a':
					h.append("��");
					break;
				case 'i':
					h.append("��");
					break;
				case 'u':
					h.append("��");
					break;
				case 'e':
					h.append("��");
					break;
				case 'o':
					h.append("��");
					break;
				}
				break;
			case 'j':
				j:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'j':
					h.append("��");
					goto j;
					break;
				case 'a':
					h.append("����");
					break;
				case 'i':
					h.append("��");
					break;
				case 'u':
					h.append("����");
					break;
				case 'e':
					h.append("����");
					break;
				case 'o':
					h.append("����");
					break;
				}
				break;
			case 'f':
			f:;
				orl++;
				switch (tolower(rs[orl])) {
				case 'f':
					h.append("��");
					goto f;
					break;
				case 'a':
					h.append("�ӂ�");
					break;
				case 'i':
					h.append("�ӂ�");
					break;
				case 'u':
					h.append("��");
					break;
				case 'e':
					h.append("�ӂ�");
					break;
				case 'o':
					h.append("�ӂ�");
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

	#pragma region ���������N�G�X�g
	//auto voice = thread([say] {
		curl_global_init(CURL_GLOBAL_ALL);

		printfDx("��\n");
		#pragma region /audio_query
		#pragma endregion
	//});
	#pragma endregion

}
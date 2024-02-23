#include "getvoice.h"
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
			default:
				h.append(" ");
				break;
		}
		orl++;
	}
	printfDx(h.data());
	printfDx("\n\n");
	#pragma endregion
}
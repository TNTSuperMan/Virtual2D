#include "getvoice.h"
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
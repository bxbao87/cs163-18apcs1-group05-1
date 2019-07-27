#include"frontEnd.h"

void FrontEnd() {
	SetWindow(168, 44);
	system("chcp 437");
	system("cls");
	BogosearchSplash();
	Center("Created by", 250, 20, 10);
	Center("NGUYEN THANH NHAN", 220, 21, 11);
	Center("PHAM KHA LUAN", 220, 22, 12);
	Center("DANG KHANH MAI", 220, 23, 13);
	Center("BUI XUAN BAO", 220, 24, 14);
	std::string a = "press any key to continue...";
	Center(a, 0, 27, 15);
	_getch();
	system("cls");
	SearchScreen();
}

void Gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void Color(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = 200;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

void S(int x, int y, int colour) {
	Gotoxy(x, y);
	Color(colour);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";
	for (int i = 0; i < 2; ++i) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	Gotoxy(x, y + 3);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";
	for (int i = 0; i < 2; ++i) {
		Gotoxy(x + 8, y + 4 + i);
		std::cout << "  ";
	}
	Gotoxy(x, y + 6);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";
	Color(15);
}

void E(int x, int y, int colour) {
	Gotoxy(x, y);
	Color(colour);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";
	for (int i = 0; i < 6; ++i) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	Gotoxy(x, y + 3);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";

	Gotoxy(x, y + 6);
	for (int i = 0; i < 10; ++i)
		std::cout << " ";
	Color(15);
}

void A(int x, int y, int colour) {
	Color(colour);
	Gotoxy(x + 1, y);
	for (int i = 0; i < 8; ++i)
		std::cout << " ";
	Gotoxy(x + 1, y + 1);
	std::cout << " ";
	Gotoxy(x + 8, y + 1);
	std::cout << " ";
	for (int i = 0; i < 6; ++i) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	Gotoxy(x + 1, y + 3);
	for (int i = 0; i < 8; ++i)
		std::cout << " ";
	for (int i = 0; i < 6; ++i) {
		Gotoxy(x + 8, y + 1 + i);
		std::cout << "  ";
	}

	Color(15);
}

void R(int x, int y, int colour) {
	Gotoxy(x, y);
	Color(colour);
	for (int i = 0; i < 9; ++i)
		std::cout << " ";
	for (int i = 0; i < 6; ++i) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	Gotoxy(x, y + 3);
	for (int i = 0; i < 9; ++i)
		std::cout << " ";
	for (int i = 1; i < 3; ++i) {
		Gotoxy(x + 8, y + i);
		std::cout << "  ";
	}
	for (int i = 2; i < 5; ++i) {
		Gotoxy(x + i + i, y + 2 + i);
		std::cout << "  ";
	}
	Color(15);
}

void C(int x, int y, int colour) {
	Color(colour);
	Gotoxy(x + 1, y);
	for (int i = 0; i < 8; ++i) {
		std::cout << " ";
	}
	Gotoxy(x + 8, y + 1);
	std::cout << "  ";
	for (int i = 0; i < 5; i++) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	Gotoxy(x + 8, y + 5);
	std::cout << "  ";
	Gotoxy(x + 1, y + 6);
	for (int i = 0; i < 8; ++i) {
		std::cout << " ";
	}
	Color(15);
}

void H(int x, int y, int colour) {
	Color(colour);
	for (int i = 0; i < 7; ++i) {
		Gotoxy(x, y + i);
		std::cout << "  ";
	}
	for (int i = 0; i < 7; ++i) {
		Gotoxy(x + 8, y + i);
		std::cout << "  ";
	}
	Gotoxy(x + 2, y + 3);
	for (int i = 2; i < 8; ++i)
		std::cout << " ";
	Color(15);
}

void B(int x, int y, int colour) {
	Color(colour);
	for (int i = 0; i < 7; ++i) {
		Gotoxy(x, y + i);
		std::cout << "  ";
	}
	Gotoxy(x + 2, y);
	for (int i = 0; i < 7; ++i)
		std::cout << " ";
	for (int i = 1; i < 6; ++i) {
		if (i != 3) {
			Gotoxy(x + 8, y + i);
			std::cout << "  ";
		}
	}
	Gotoxy(x + 2, y + 3);
	for (int i = 0; i < 7; ++i)
		std::cout << " ";
	Gotoxy(x + 2, y + 6);
	for (int i = 0; i < 7; ++i)
		std::cout << " ";
	Color(15);
}

void O(int x, int y, int colour) {
	Color(colour);
	for (int i = 1; i < 6; ++i) {
		Gotoxy(x, y + i);
		std::cout << "  ";
	}
	for (int i = 1; i < 6; ++i) {
		Gotoxy(x + 8, y + i);
		std::cout << "  ";
	}
	Gotoxy(x + 1, y);
	for (int i = 2; i < 10; ++i)
		std::cout << " ";
	Gotoxy(x + 1, y + 6);
	for (int i = 2; i < 10; ++i)
		std::cout << " ";
	Color(15);
}

void G(int x, int y, int colour) {
	Color(colour);
	Gotoxy(x + 1, y);
	for (int i = 0; i < 8; ++i) {
		std::cout << " ";
	}
	for (int i = 0; i < 5; i++) {
		Gotoxy(x, y + 1 + i);
		std::cout << "  ";
	}
	for (int i = 1; i < 6; ++i) {
		if (i != 2) {
			Gotoxy(x + 8, y + i);
			std::cout << "  ";
		}
	}
	Gotoxy(x + 5, y + 3);
	for (int i = 0; i < 3; ++i)
		std::cout << " ";
	Gotoxy(x + 1, y + 6);
	for (int i = 0; i < 8; ++i) {
		std::cout << " ";
	}
	Color(15);
}

void Center(std::string a, int s, int y, int colour)
{
	Color(colour);
	int x;
	x = (168 - a.length()) / 2;
	Gotoxy(x, y);
	std::cout << a << std::endl;
	Sleep(s);
	Color(15);
}

void BogosearchSplash() {
	bool a[10];
	for (int i = 0; i < 10; ++i)
		a[i] = false;
	std::srand(time(NULL));
	int t = 0;
	while (t < 10) {
		int x = std::rand() % 10;
		if (!a[x]) {
			a[x] = true;
			switch (x) {
			case 0:
				B(12, 5, 204);
				break;
			case 1:
				O(27, 4, 153);
				break;
			case 2:
				G(42, 6, 119);
				break;
			case 3:
				O(57, 5, 170);
				break;
			case 4:
				S(72, 3, 51);
				break;
			case 5:
				E(87, 5, 238);
				break;
			case 6:
				A(102, 7, 221);
				break;
			case 7:
				R(117, 4, 68);
				break;
			case 8:
				C(132, 6, 187);
				break;
			case 9:
				H(147, 5, 102);
				break;
			}
			Sleep(300);
			++t;
		}

	}
}

void SearchScreen() {
	B(12, 5, 204);
	O(27, 5, 153);
	G(42, 5, 119);
	O(57, 5, 170);
	S(72, 5, 51);
	E(87, 5, 238);
	A(102, 5, 221);
	R(117, 5, 68);
	C(132, 5, 187);
	H(147, 5, 102);

	Color(1);
	Gotoxy(27, 20);
	std::cout << (char)201;
	for (int i = 1; i < 114; ++i)
		std::cout << (char)205;
	std::cout << (char)187;
	Gotoxy(27, 21);
	std::cout << (char)186;
	Gotoxy(141, 21);
	std::cout << (char)186;
	Gotoxy(27, 22);
	std::cout << (char)200;
	for (int i = 1; i < 114; ++i)
		std::cout << (char)205;
	std::cout << (char)188;
	Color(15);
}

void ExitScreen() {
	system("cls");
	Color(11);
	Gotoxy(0, 5);
	std::cout << R"(
                                   :::::::::   ::::::::   ::::::::   ::::::::   ::::::::  ::::::::::     :::     :::::::::   ::::::::  :::    :::)";
	Sleep(100);
	Color(3);
	std::cout << R"(
                                  :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:          :+: :+:   :+:    :+: :+:    :+: :+:    :+:
                                 +:+    +:+ +:+    +:+ +:+        +:+    +:+ +:+        +:+         +:+   +:+  +:+    +:+ +:+        +:+    +:+)";
	Sleep(100);                 
	Color(9);
	std::cout << R"(
                                +#++:++#+  +#+    +:+ :#:        +#+    +:+ +#++:++#++ +#++:++#   +#++:++#++: +#++:++#:  +#+        +#++:++#++
                               +#+    +#+ +#+    +#+ +#+   +#+# +#+    +#+        +#+ +#+        +#+     +#+ +#+    +#+ +#+        +#+    +#+)";
	Sleep(100);
	Color(1);
	std::cout << R"(
                              #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#        #+#     #+# #+#    #+# #+#    #+# #+#    #+#
                             #########   ########   ########   ########   ########  ########## ###     ### ###    ###  ########  ###    ###)";
	Sleep(100);
	Center("NGUYEN THANH NHAN", 220, 21, 11);
	Center("PHAM KHA LUAN", 220, 22, 12);
	Center("DANG KHANH MAI", 220, 23, 13);
	Center("BUI XUAN BAO", 220, 24, 14);
	Color(14);
	std::cout << R"(
                                          ________                __           ______               __  __      _              __
                                         /_  __/ /_  ____ _____  / /_______   / ____/____  _____   / / / /_____(_)____  ____ _/ /
                                          / / / __ \/ __ `/ __ \/ //_/ ___/  / /_   / __ \/ ___/  / / / // ___/ // __ \/ __ `/ / 
                                         / / / / / / /_/ / / / / ,< (__  )  / __/  / /_/ / /     / /_/ /(__  ) // / / / /_/ /_/  
                                        /_/ /_/ /_/\__,_/_/ /_/_/|_/____/  /_/     \____/_/      \____//____/_//_/ /_/\__, (_)  
                                                                                                                     /____/      )";
}

void OutOfRange(std::string a) {
	Gotoxy(28, 21);
	int len = a.length();
	for (int i = len - 111; i < len; ++i)
		std::cout << a[i];
}

std::vector<std::string> DisplayHistory(const std::vector<std::string> &v) {
	int xC = 27, yC = 23;

	Gotoxy(xC, yC);
	for (int i = yC; i < 29; ++i) {
		Gotoxy(xC, i);
		for (int j = 0; j < 115; ++j)
			std::cout << " ";
	}
	int t = 1;
	std::vector<std::string> returnedVec;
	if (!v.empty()) {

		for (int i = v.size() - 1; i >= 0 && t < 6; --i) {
			Color(3);
			Gotoxy(xC, yC);
			std::cout << (char)179;
			Gotoxy(141, yC);
			std::cout << (char)179;
			Color(8);
			Gotoxy(xC + 1, yC++);
			std::cout << v[i];
			++t;
			returnedVec.push_back(v[i]);
		}

	}
	Color(3);
	Gotoxy(xC, yC);
	std::cout << (char)192;
	for (int i = 1; i < 114; ++i)
		std::cout << (char)196;
	std::cout << (char)217;
	Color(15);
	return returnedVec;
}

int ChooseLink(int n) {
	if (n == 0)
		return -1;
	Gotoxy(10, 31);
	Color(14);
	std::cout << "|>|>";
	int key = _getch();
	int a = 0;
	while (key != 13 && key != 27) {
		if (key == 224) {
			int ex = _getch();
			Gotoxy(10, a * 10 + 31);
			Color(15);
			std::cout << "    ";
			if (ex == 72) {
				if (a == 0)
					a = n - 1;
				else
					--a;
			}
			else if (ex == 80) {
				if (a == n - 1)
					a = 0;
				else
					++a;
			}
			Gotoxy(10, a * 10 + 31);
			Color(14);
			std::cout << "|>|>";
		}
		key = _getch();
	}
	Color(15);
	if (key == 27)
		return -1;
	return a;
}

#include"Support.h"

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
	Color(240);
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
	Color(240);
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

	Color(240);
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
	Color(240);
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
	Color(240);
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
	Color(240);
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
	Color(240);
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
	Color(240);
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
	Color(240);
}

void Center(std::string a, int s, int y, int colour)
{
	Color(colour);
	int x;
	x = (168 - a.length()) / 2;
	Gotoxy(x, y);
	std::cout << a << std::endl;
	Sleep(s);
	Color(240);
}

void BogosearchSplash() {
	bool a[10];
	for (int i = 0; i < 10; ++i)
		a[i] = false;
	std::srand(std::time(NULL));
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
				O(27, 4, 17);
				break;
			case 2:
				G(42, 6, 221);
				break;
			case 3:
				O(57, 5, 34);
				break;
			case 4:
				S(72, 3, 51);
				break;
			case 5:
				E(87, 5, 0);
				break;
			case 6:
				A(102, 7, 85);
				break;
			case 7:
				R(117, 4, 102);
				break;
			case 8:
				C(132, 6, 187);
				break;
			case 9:
				H(147, 5, 68);
				break;
			}
			Sleep(300);
			++t;
		}

	}
}

void SearchScreen() {
	B(12, 5, 204);
	O(27, 5, 17);
	G(42, 5, 221);
	O(57, 5, 34);
	S(72, 5, 51);
	E(87, 5, 0);
	A(102, 5, 85);
	R(117, 5, 102);
	C(132, 5, 187);
	H(147, 5, 68);

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
}

void OutOfRange(std::string a) {

}

void FrontEnd() {
	SetWindow(168, 44);
	system("color f0");
	system("chcp 437");
	system("cls");
	BogosearchSplash();
	Center("Created by", 250, 20, 240);
	Center("NGUYEN THANH NHAN", 220, 21, 241);
	Center("PHAM KHA LUAN", 220, 22, 245);
	Center("DANG KHANH MAI", 220, 23, 250);
	Center("BUI XUAN BAO", 220, 24, 252);
	std::string a = "press any key to continue...";
	Gotoxy((168 - a.length()) / 2, 27);
	system("pause");
	system("cls");
	SearchScreen();
	Gotoxy(28, 21);
	

}
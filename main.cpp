#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main() {
	Search a;
	std::string str;
	FrontEnd();
	while (a.InputKey(str)) {
		str.clear();
	}
	_getch();
	return 0;
}
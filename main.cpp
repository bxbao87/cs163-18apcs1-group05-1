#include "Search.h"
#include "Support.h"
#include "History.h"

int main()
{
	Search bogoSearch;
	bogoSearch.Run();
	FrontEnd();
	bogoSearch.InputKey(28, 21);
	if (bogoSearch.createIndex())
		std::cout << "OK";
	else
		std::cout << "Nah";

	system("pause");
	return 0;
}
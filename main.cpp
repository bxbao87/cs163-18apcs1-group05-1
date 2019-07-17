#include "Search.h"
#include "Support.h"
#include "History.h"

int main()
{
	//Search bogoSearch;
	//bogoSearch.Run();
	Search ab;
	if (ab.createIndex())
		std::cout << "OK";
	else
		std::cout << "Deo on!";

	system("pause");
	return 0;
}
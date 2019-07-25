#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main()
{
	Search bogoSearch;
	//Search bogoSearch;
	//bogoSearch.Run();
	//std::string query("la la land AND (\"made in China\" OR intitle:something good");
	//std::cout << bogoSearch.InfixToPostfix(query);
	//FrontEnd();
	//bogoSearch.InputKey(28, 21);
	//auto a = bogoSearch.GetFilename("Data");
	//system("Start Data/1.txt");
	std::string query = "VU LAN CELEBRATION IN VIETNAM";
	auto tmp = bogoSearch.SearchExact(query);
	for (auto i : tmp) std::cout << i << ' ';
	system("pause");
	return 0;
}
#include "Search.h"
#include "Support.h"
#include "History.h"

int main()
{
	Search bogoSearch;
	bogoSearch.Run();
	/*std::string query;
	std::cout << "Input what you want to search: ";
	getline(std::cin, query);
	query = bogoSearch.PreProcess(query);
	query = bogoSearch.InfixToPostfix(query);
	std::cout << query << std::endl;*/
	auto v = bogoSearch.SearchExact("inbox and chat" );
	std::cout << v.size() << std::endl;
	for (auto i : v) {
		std::cout << i << std::endl;
	}
	//Search bogoSearch;
	//bogoSearch.Run();
	//std::string query("la la land AND (\"made in China\" OR intitle:something good");
	//std::cout << bogoSearch.InfixToPostfix(query);
	//FrontEnd();
	//bogoSearch.InputKey(28, 21);
	//auto a = bogoSearch.GetFilename("Data");
	//system("Start Data/1.txt");
	system("pause");
	return 0;
}
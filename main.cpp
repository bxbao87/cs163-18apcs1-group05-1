#include "Search.h"
#include "Support.h"
#include "History.h"

int main()
{
	Search bogoSearch;
	std::string query = "chat prayers";
	auto tmp = bogoSearch.SearchExact(query);
	for (auto i : tmp) std::cout << i << ' ';

	system("pause");
	return 0;
}
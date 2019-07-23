#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main()
{
	Search bogoSearch;
	std::string query = "VU LAN CELEBRATION IN VIETNAM";
	auto tmp = bogoSearch.SearchExact(query);
	for (auto i : tmp) std::cout << i << ' ';

	system("pause");
	return 0;
}
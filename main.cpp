#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main() {
	Search bogoSearch;
	bogoSearch.Run();
	/// Luan's draft
	while (true) {
		std::string query;
		std::getline(std::cin, query);
		bogoSearch.SearchPlaceHolder(query);
		std::cout << query << std::endl;
	}
	///End of Luan's draft
	system("pause");
	return 0;
}
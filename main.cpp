#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main() {
	Search bogosearch;
	bogosearch.Run();
	// Mai's testing zone 
	/*Document doc("Data/Group25News41.txt");
	doc.ReadFile();
	std::vector<std::string> p = { "Google" };
	doc.GetParagraphForShowing(p);
	doc.debug();
*/
	/*if (IsStringWiths("Nintendo","Nintendo's"))
		std::cout << "True" << '\n';
	else
		std::cout << "False" << std::endl;
	system("pause");*/
	// End of Mai's testing zone

	/*///Luan's draft starts here
	while (true) {
		std::string query;
		std::getline(std::cin, query);
		std::vector <std::string> title, content;
		bogoSearch.SplitQuery(query, title, content);
		std::cout << "TITLE" << std::endl;
		for (auto word : title)
			std::cout << word << std::endl;
		std::cout << std::endl;
		std::cout << "CONTENT" << std::endl;
		for (auto word : content) {
			std::cout << word << std::endl;
		}
	}
	///End of Luan's draft*/
	return 0;
}
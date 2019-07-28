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
	return 0;
}
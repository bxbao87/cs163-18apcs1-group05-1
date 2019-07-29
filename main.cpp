#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main() {
	Search bogoSearch;
	//bogoSearch.Test200Query();
	bogoSearch.Run();
	// Mai's testing zone 
	/*Document doc("Data/Group21News97.txt");
	doc.ReadFile();
	std::vector<std::string> p = { "Nintendo" };
	doc.GetParagraphForShowing(p);
	doc.debug();*/

	/*if (IsStringWiths("Nintendo","Nintendo's"))
		std::cout << "True" << '\n';
	else
		std::cout << "False" << std::endl;
	system("pause");*/
	// End of Mai's testing zone

	/*///Luan's draft starts here
	std::cout << "XONG ROI" << std::endl;
	std::string queryCucSuc = "Camera";
	std::vector <std::string> a, b;
	bogosearch.TrimQuery(queryCucSuc,a ,b);
	std::cout << queryCucSuc << std::endl;
	///End of Luan's draft*/
	//system("cls");
	return 0;
}
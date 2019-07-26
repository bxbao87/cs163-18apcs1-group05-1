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

	/*while (true) {
		std::cout << "Search normal" << std::endl;
		std::string query;
		getline(std::cin, query);
		query = bogoSearch.InfixToPostfix(query);
		std::cout << query;
		auto v = bogoSearch.Process(query);
		std::cout << v.size() << std::endl;
		bogoSearch.Debug(v);
		for(auto i:v)
		system("pause");
	}
	*/

	/*Document doc("Data/03.txt");
	doc.ReadFile();
	std::vector<std::string> keyword = {"ivory"};
	doc.GetParagraphForShowing(keyword);
	doc.debug();*/
	return 0;
}
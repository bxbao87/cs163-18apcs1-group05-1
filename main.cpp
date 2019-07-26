#include "Search.h"
#include "Support.h"
#include "History.h"
#include <map>

int main()
{
	Search bogoSearch;
	bogoSearch.Run();
	//std::string query("la la land AND (\"made in China\" OR intitle:something good");
	//std::cout << bogoSearch.InfixToPostfix(query);
	//FrontEnd();
	//bogoSearch.InputKey(28, 21);
	//auto a = bogoSearch.GetFilename("Data");
	//system("Start Data/1.txt");

	// while (true) {
	// 	std::cout << "Search normal" << std::endl;
	// 	std::string query;

	// 	getline(std::cin, query);
	// 	std::vector<std::string> keyword = splitSentence(query);
	// 	std::string tmp = query;
	// 	query = bogoSearch.InfixToPostfix(query);
	// 	std::cout << query << '\n';
	// 	auto v = bogoSearch.Process(query);
	// 	std::cout << v.size() << std::endl;
	// 	bogoSearch.Debug(v);
	// }
		std::vector<std::string> fileList;
		bogoSearch.GetFileNameByInt(v, fileList);
		std::vector<Document> result;
		CreateVectorDoc(fileList, result);
		/*std::cout << v.size() << std::endl;
		bogoSearch.Debug(v);*/

		for (auto i:result)
		{
			i.GetParagraphForShowing(keyword, tmp);
			i.debug();
			std::cout << '\n';
		}
		
		/*for(auto i:v)
		system("pause");*/
	}
	/*std::string query = "de nhi quoc su";
	auto v=bogoSearch.SearchExact(query);
	std::vector<std::string> keyword = splitSentence(query);
	std::vector<std::string> fileList;
		bogoSearch.GetFileNameByInt(v, fileList);
		std::vector<Document> result;
		CreateVectorDoc(fileList, result);
		for (auto i : result)
		{
			i.GetParagraphForShowing(keyword, query);
			i.debug();
			std::cout << '\n';
	
		}*/
	/*Document doc("Data/03.txt");
	doc.ReadFile();
	std::vector<std::string> keyword = {"Vietnam","News","Agency"};
	doc.GetParagraphForShowing(keyword,"Vietnam News Agency");
	doc.debug();*/

	system("pause");
	return 0;
}
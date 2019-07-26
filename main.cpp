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

	while (true) {
		SetWindow(168, 44);
		system("cls");
		std::cout << "Search normal" << std::endl;
		std::string query;

		getline(std::cin, query);
		std::vector<std::string> keyword = splitSentence(query);
		std::string tmp = query;
		query = bogoSearch.InfixToPostfix(query);
		std::cout << query << '\n';
		auto v = bogoSearch.Process(query);
		std::vector<std::string> fileList;
		bogoSearch.GetFileNameByInt(v, fileList);
		std::vector<Document> result;
		CreateVectorDoc(fileList, result);
		/*std::cout << v.size() << std::endl;
		bogoSearch.Debug(v);*/
		int t = 0;
		std::cout << result.size() << std::endl;
		Sleep(1000);
		for (auto i:result)
		{
			i.GetParagraphForShowing(keyword, tmp);
			i.DisplayResult(5, 5 + t++ * 10);
			std::cout << '\n';
			Sleep(2000);
		}
		_getch();
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
	return 0;
}
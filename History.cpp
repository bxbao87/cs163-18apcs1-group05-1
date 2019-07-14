#include "History.h"

History::History()
{
	std::ifstream inFile;
	inFile.open("Process/History.txt");
	if (!inFile.is_open())
	{
		std::ofstream outFile;
		outFile.open("Process/History.txt");
		outFile.close();
	}
	else {
		inFile.close();
		LoadHistory();
	}
}

History::~History()
{
	WriteHistory();
}

void History::LoadHistory()
{
	std:: ifstream inFile;
	inFile.open("Process/History.txt");
	if (inFile.is_open())
	{
		std::string query;
		while (getline(inFile, query)) {
			getline(inFile, query);
			history.push(query);
		}
	}
	else
		std::cout << "File History.txt is not found" << std::endl;
	inFile.close();
}

void History::WriteHistory()
{
	std::ofstream outFile;
	outFile.open("Process/History.txt");
	while (!history.empty()) {
		std::string query = history.front();
		history.pop();
		outFile << query << std::endl;
	}
	outFile.close();
}

void History::Add(const std::string & query)
{
	if (history.size() < 20)
		history.push(query);
	else {
		history.pop();
		history.push(query);
	}
}

std::vector<std::string> History::GetHistory(const std::string & searchKeyword)
{
	std::vector <std::string> resultVector;

	for (int i = 0; i < history.size(); i++)
	{
		std::string cur = history.front();

		if (isPrefix(cur, searchKeyword)) 
			resultVector.push_back(cur);
		
		history.pop();
		history.push(cur);
	}
	return resultVector;
}

bool isPrefix(const std::string & check, const std::string & query)
{
	if (check.size() < query.size())
		return false;
	std::string compareString(check, 0, query.size());
	return !compareString.compare(query);
}

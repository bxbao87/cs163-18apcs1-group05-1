#include "Search.h"

Search::Search()
{
	system("md Process");
	system("md Data");

	if (!trie.LoadTrie())
	{
		//CreateIndex();
		trie.SaveTrie();
		numIndex.SaveNumIndex();
	}
	else numIndex.LoadNumIndex();
}

Search::~Search()
{
}

void Search::Run()
{
	trie.LoadTrie();
	trie.SaveTrie();
}

std::vector<std::string> Search::ReadSingleFile(const std::string & fileName)
{
	std::vector<std::string> tokenVector;
	std::string filePath = "Data/" + fileName;
	std::ifstream inFile;
	inFile.open(filePath.c_str());
	if (inFile.is_open()) {
		std::string fileData;
		//read everything into string
		while (!inFile.eof()) {
			std::string line;
			getline(inFile, line);
			fileData += " " + line;
		}

		std::stringstream ss(fileData);
		std::string token;
		//extract token from string stream
		while (ss >> token) {
			if (isDelimiter(token[token.size() - 1])) //check for the last char is a delimiter or not
				token.erase(token.end()-1);
			tokenVector.push_back(token);
		}
		//eliminate duplicate element
		std::sort(tokenVector.begin(), tokenVector.end());
		tokenVector.erase(std::unique(tokenVector.begin(), tokenVector.end()), tokenVector.end());
	}
	else
		std::cout << "File " << fileName << " is not found";
	inFile.close();

	return tokenVector;
}

std::vector<std::string> Search::GetFilename(const std::string rootDirectory)
{
	std::vector <std::string> pathVector;
	std::stringstream ss;
	for (auto & entry : std::experimental::filesystem::directory_iterator(rootDirectory))
		ss << entry.path() << " ";
	std::string path;
	while (ss >> path) {
		pathVector.push_back(path);
	}
	return pathVector;
}

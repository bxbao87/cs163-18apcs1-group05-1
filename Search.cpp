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
	std::ifstream inFile;
	inFile.open(fileName.c_str());
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
			while (isDelimiter(token[0]))
				token.erase(0, 1);
			if (token != "")
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

bool Search::createIndex()
{
	std::vector<std::string> fileList;
	fileList.clear();
	fileList = GetFilename("Data");

	if (fileList.empty())
		return false;
	for (auto i : fileList)
	{
		std::cout << i << ' ';
		std::vector<std::string> wordsInFile;
		wordsInFile.clear();
		wordsInFile = ReadSingleFile(i);

		if (wordsInFile.empty())
		{
			std::cout << "Can't load file";
			return false;
		}

		wordsInFile = RemoveStopWord(wordsInFile);

		for (int j=0;j<(int)wordsInFile.size();++j)
		{
			if (isNumberWithChar(wordsInFile[j]))
			{
				double val = stod(wordsInFile[j]);
				numIndex.AddNum(val, i);
			}
			else
			{
				trie.AddKey(wordsInFile[j], i);
			}
		}
	}
	return true;
}




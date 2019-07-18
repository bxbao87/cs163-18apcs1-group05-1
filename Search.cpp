#include "Search.h"

Search::Search()
{
	system("md Process");
	system("md Data");

	if (!loadStopWord(stopWord))
		std::cerr << "Can't open stop word file\n";

	if (!trie.LoadTrie())
	{
		createIndex();
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
		std::vector<std::string> wordsInFile;
		wordsInFile.clear();
		wordsInFile = ReadSingleFile(i);

		if (wordsInFile.empty())
		{
			std::cout << "Can't load file";
			return false;
		}

		wordsInFile = RemoveStopWord(wordsInFile);

		for (int j = 0; j < (int)wordsInFile.size(); ++j)
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



std::string Search::InputKey(int x, int y) {
	int key, len = 0;
	std::string str, resultStr;
	History h;

	Gotoxy(x, y);
	key = _getch();
	while (key != 13) {
		if (key == 8 && len > 0)
		{
			--len;
			str.pop_back();
			resultStr.pop_back();
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << "\b \b";
			DisplayHistory(h.GetHistory(str));
		}
		else if (key == 0 || key == 224)
			int ex = _getch();
		else if (key != 0 && key != 224 && key != 8)
		{
			str += tolower((char)key);
			resultStr += (char)key;
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << (char)key;
			++len;
			if (str != " ")
				DisplayHistory(h.GetHistory(str));
		}

		if (len < 111)
			Gotoxy(x + len, y);
		else
			Gotoxy(x + 111, y);
		key = _getch();
	}

	h.Add(str);

	return resultStr;
}



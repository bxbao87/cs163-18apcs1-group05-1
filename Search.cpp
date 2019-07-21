#include "Search.h"

Search::Search()
{
	system("md Process");
	system("md Data");

	if (!LoadSynonym())
		std::cerr << "Can't open synonym file\n";
	if (!LoadStopWord(stopWord))
		std::cerr << "Can't open stop word file\n";

	if (!trie.LoadTrie())
	{
		CreateIndex();
		trie.SaveTrie();
		numIndex.SaveNumIndex();
	}
	else numIndex.LoadNumIndex();
}

Search::~Search()
{
}

bool Search::LoadSynonym()
{
	std::ifstream in("Process\\synonym.txt");
	if (!in.is_open()) return false;
	std::string word;
	while (std::getline(in, word) && word != "")
	{
		std::string listOfWord;
		std::getline(in, listOfWord);
		std::stringstream ss(listOfWord);

		std::string wordInList;
		while (ss >> wordInList) synonym[word].push_back(wordInList);
	}
	in.close();
	return true;
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
			while ((int)token.size()>0 && isDelimiter(token.back())) //check for the last char is a delimiter or not
				token.erase(token.end()-1);
			while ((int)token.size()>0 && isDelimiter(token[0]))
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

bool Search::LoadStopWord(std::set<std::string>& stopword)
{
	std::ifstream fin;
	fin.open("Process/stopword.txt");
	if (!fin.is_open()) return false;
	std::string word;
	while (!fin.eof())
	{
		fin >> word;
		stopword.insert(word);
	}
	fin.close();
	return true;
}

std::vector<std::string> Search::RemoveStopWord(const std::vector<std::string>& words)
{
	std::vector<std::string> afterRemove;
	afterRemove.clear();

	std::string word;

	for (int i = 0; i <(int) words.size(); ++i)
	{
		word = words[i];
		Tolower(word);
		if (stopWord.find(word) == stopWord.end())
			afterRemove.push_back(word);
	}
	return afterRemove;
}


bool Search::CreateIndex()
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
			bool mixType = false;
			if (isNumberWithChar(wordsInFile[j], mixType))
			{
				double val = stod(wordsInFile[j]);
				numIndex.AddNum(val, i);
			}
			else
			{
				if (!mixType)
				{
					trie.AddKey(wordsInFile[j], i);
				}
			}

		}
	}
	return true;
}


std::string Search::InputKey(int x, int y) {
	int key, len = 0;
	int moveCursor = -1;
	std::string resultStr;
	std::vector<std::string> lsHis;
	History h;

	Gotoxy(x, y);
	key = _getch();
	while (key != 13) {
		if (key == 8 && len > 0)
		{
			moveCursor = -1;
			--len;
			resultStr.pop_back();
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << "\b \b";
			lsHis=DisplayHistory(h.GetHistory(resultStr));
		}
		else if (key != 0 && key != 224 && key != 8)
		{
			moveCursor = -1;
			resultStr += (char)key;
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << (char)key;
			++len;
			if (resultStr != " ")
				lsHis=DisplayHistory(h.GetHistory(resultStr));
		}
		else if (key == 0 || key == 224)
		{
			int ex = _getch();
			int noHistory = lsHis.size();
			if (noHistory > 0) {
				if (ex == 72 && moveCursor > -1) {
					Gotoxy(x, y + moveCursor + 2);
					std::cout << lsHis[moveCursor--];
					Color(112);
					if (moveCursor != -1) {
						Gotoxy(x, y + moveCursor + 2);
						std::cout << lsHis[moveCursor];
					}
				}
				else if (ex == 80 && moveCursor<noHistory-1) {
					if (moveCursor != -1) {
						Gotoxy(x, y + moveCursor + 2);
						std::cout << lsHis[moveCursor];
					}
					Color(112);
					Gotoxy(x, y + ++moveCursor + 2);
					std::cout << lsHis[moveCursor];
				}
				Color(240);
			}
		}
		if (len < 111)
			Gotoxy(x + len, y);
		else
			Gotoxy(x + 111, y);
		key = _getch();
	}

	if (moveCursor != -1) {
		resultStr = lsHis[moveCursor];
		Gotoxy(x, y);
		std::cout << resultStr;
		for (int j = resultStr.length(); j < 113; ++j)
			std::cout << " ";
	}
	h.Add(resultStr);

	return resultStr;
}



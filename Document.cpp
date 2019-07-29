#include "Document.h"
#include "frontEnd.h"

Document::Document()
{
}

Document::Document(std::string fileName) : fileName(fileName)
{
}

void Document::SetFileName(const std::string& name)
{
	fileName = name;
}

void Document::ReadFile()
{
	std::ifstream in(fileName);
	while (getline(in, title))
		if (title != "")
			break;
	if (title.length() > 120) {
		std::string tmp, word;
		tmp = title;


		title.clear();
		std::stringstream ss;
		for (int i = 0; i < 15; ++i)
		{
			ss << tmp;
			ss >> word;
			title += word + ' ';
		}
		title += "...";

		content = tmp;
	}

	std::string tmp;
	while (std::getline(in, tmp))
	{
		content += '\n' + tmp;
	}

	in.close();
}

void Document::OpenFile()
{
	std::string command = "start " + fileName;
	system(command.c_str());
}

int Document::SearchForPhraseInContent(const std::string& phrase)
{
	auto pos = content.find(phrase);
	if (pos == std::string::npos) return -1;
	else return (int)pos;
}

int Document::SearchForPhraseInTitle(const std::string& phrase)
{
	auto pos = title.find(phrase);
	if (pos == std::string::npos) return -1;
	else return (int)pos;
}

void Document::DisplayResult(int x, int &y) {
	Gotoxy(x, y);
	Color(9);
	std::cout << "File: " << fileName;
	Gotoxy(x, ++y);
	ColorTitle();
	Gotoxy(x, ++y);
	Color(15);
	int len = 0;
	for (auto i : paragraphForShowing) {
		if (len + i.first.length() > 100)
		{
			Gotoxy(x, ++y);
			len = 0;
		}
		len += i.first.length();
		if (len > 100) {
			std::string tmp = i.first.substr(0, 120), tmp2 = i.first.substr(121, len);
			std::cout << tmp;
			Gotoxy(x, ++y);
			std::cout << tmp2;
			len = tmp2.length();
		}
		else if (i.second == true) {
			Color(12);
			std::cout << i.first;
			Color(15);
			std::cout << " ";
		}
		else
			std::cout << i.first << " ";
	}
}

bool Document::IsDelimeter(const char & c, const std::set<char>& delimeter)
{
	if (delimeter.count(c) != 0) return true;
	else return false;
}

void Document::GetParagraphForShowing(const std::vector<std::string>& phrase)
{
	//process content
	paragraphForShowing.clear();
	const std::set <char> delimeter = { '.', ',', '\'', '?', '\"', '\n', '!', '(', ')','-','/',
			'&','[',']','+',':','`','@','%','^','=','_', '\\', '|', '$', '~' };

	for (auto ph : phrase)
	{
		int posP = SearchForPhraseInContent(ph);
		std::vector<std::string> keyword = splitSentence(ph);

		if (posP != -1)
		{
			int count = 0, len = 0;
			for (int i = posP; i<(int)content.size() && count < 50; ++i)
			{

				if ((content[i] == ' ' && i > 0 && content[i - 1] != ' ') ||
					(content[i] == '\n' && i > 0 && content[i - 1] != '\n' && content[i - 1] != ' '))
				{
					++count;
				}
				++len;
			}

			std::string toDisplay = content.substr(posP, len);
			std::vector<std::string> splitToDisplay = splitSentence(toDisplay);
			std::vector<std::string> process;

			for (auto i : splitToDisplay)
			{
				//std::string tmp = TolowerExtend(i);
				std::string tmp = i;
				while ((int)tmp.size() > 0 && IsDelimeter(tmp[0], delimeter))
					tmp.erase(0, 1);
				while ((int)tmp.size() > 0 && IsDelimeter(tmp.back(), delimeter))
					tmp.pop_back();
				process.push_back(tmp);
			}

			for (int i=0; i < (int)splitToDisplay.size(); ++i)
			{
				std::pair<std::string, bool> word;
				word.first = splitToDisplay[i];
				if (std::find(keyword.begin(), keyword.end(), process[i]) != keyword.end())
					word.second = true;
				paragraphForShowing.push_back(word);
			}

		}
		else
		{
			std::vector<std::string> wordsContent = splitSentence(content);
			std::vector<std::string> toloweredContent;
			
			for (auto i : wordsContent)
			{
				std::string tmp = TolowerExtend(i);
				while ((int)tmp.size() > 0 && IsDelimeter(tmp[0], delimeter))
					tmp.erase(0, 1);
				while ((int)tmp.size() > 0 && IsDelimeter(tmp.back(), delimeter))
					tmp.pop_back();
				toloweredContent.push_back(tmp);
			}

			for (auto& i : keyword)
				Tolower(i);

			std::vector<int> pos;

			for (auto i : keyword)
			{
				auto it = std::find(toloweredContent.begin(), toloweredContent.end(), i);
				if (it != toloweredContent.end())
				{
					int d = (int)std::distance(toloweredContent.begin(), it);
					pos.push_back(d);
				}
			}
			if (pos.empty())
				continue;
			int min = pos[0], cnt = 0;
			for (auto i : pos)
				if (i < min)
					min = i;
			for (int i = min; i < (int)wordsContent.size() && cnt < 50; ++i)
			{
				std::pair<std::string, bool> word;
				word.first = wordsContent[i];
				if (std::find(keyword.begin(), keyword.end(), toloweredContent[i]) != keyword.end())
					word.second = true;
				paragraphForShowing.push_back(word);
				++cnt;
			}
			if ((int)paragraphForShowing.size() == 1)
			{
				cnt = 1;
				for (int i = min - 1; i >= 0 && cnt < 50; ++i)
				{
					std::pair<std::string, bool> word;
					word.first = wordsContent[i];
					word.second = false;
					paragraphForShowing.insert(paragraphForShowing.begin(), word);
					++cnt;
				}
			}

		}
	}
}

void Document::debug()
{
	if (paragraphForShowing.empty())
		return;
	std::cout << "size: " << paragraphForShowing.size() << '\n';
	std::cout << fileName << '\n';
	for (auto i : paragraphForShowing)
		std::cout << i.first << ' ';
}
void Document::getWordsIntitle(std::vector<std::string> &phrase) {
	for (auto i : phrase)
		wordsIntitle.insert(i);
}
void Document::ColorTitle() {
	std::string word;
	std::stringstream ss;
	while (ss) {
		ss >> word;
		if (wordsIntitle.find(word) != wordsIntitle.end()) {
			Color(10);
			std::cout << " " + word;
			Color(14);
		}
		else
			std::cout << " " + word;
		word.clear();
	}
}

void CreateVectorDoc(const std::vector<std::string>& fileName, std::vector<Document>& result)
{
	for (auto i : fileName)
	{
		Document tmp(i);
		tmp.ReadFile();
		result.push_back(tmp);
	}
}

void Document::DisplayFile() {
	system("cls");
	int y = 10;
	Gotoxy(20, y);
	Color(9);
	std::cout << "File: " << fileName;
	Gotoxy(20, ++y);
	Color(14);
	std::cout << "Title: " << title;
	Color(15);
	std::vector<std::string> a;
	a = splitSentence(content);
	int len = 0;
	Gotoxy(20, ++y);
	for (auto i : a) {
		len += i.length();
		if (len > 100)
		{
			len = i.length();
			Gotoxy(20, ++y);
		}
		if (len > 100) {
			std::string tmp = i.substr(0, 120), tmp2 = i.substr(121, len);
			std::cout << tmp;
			Gotoxy(20, ++y);
			std::cout << tmp2;
			len = tmp2.length();
		}
		else
			std::cout << i << " ";
	}
}
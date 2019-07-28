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
		title+="...";

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
	Color(14);
	std::cout << "Title: " << title;
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
		if (i.second == true) {
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
	paragraphForShowing.clear();
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

			for (auto i : splitToDisplay)
			{
				std::pair<std::string, bool> word;
				word.first = i;
				if (std::find(keyword.begin(), keyword.end(), i) != keyword.end())
					word.second = true;
				paragraphForShowing.push_back(word);
			}

		}
		else
		{
			std::vector<std::string> wordsContent = splitSentence(content);
			std::vector<std::string> toloweredContent;
			const std::set <char> delimeter = { '.', ',', '\'', '?', '\"', '\n', '!', '(', ')','-','/',
			'&','[',']','+',':','`','@','%','^','=','_', '\\', '|', '$', '~' };

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
			pos.clear();
			for (auto i : keyword)
			{
				auto it = std::find(toloweredContent.begin(), toloweredContent.end(), i);
				if (it != toloweredContent.end())
				{
					int d = std::distance(toloweredContent.begin(), it);
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
		std::cout << i << " ";
	}
}
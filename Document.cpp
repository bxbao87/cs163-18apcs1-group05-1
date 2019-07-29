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
	if (pos == std::string::npos) 
		return -1;

	while (pos != std::string::npos && !IsTheSameString(phrase, content, pos))
	{
		pos = content.find(phrase, pos + 1);
	}

	if (pos == std::string::npos) 
		return -1;
	else 
		return (int)pos;
}

int Document::SearchForPhraseInTitle(const std::string& phrase)
{
	auto pos = title.find(phrase);
	if (pos == std::string::npos)
		return -1;

	while (pos != std::string::npos && !IsTheSameString(phrase, title, pos))
	{
		pos = title.find(phrase, pos + 1);
	}

	if (pos == std::string::npos)
		return -1;
	else
		return (int)pos;
}

void Document::DisplayResult(int x, int &y) {
	Gotoxy(x, y);
	Color(9);
	std::cout << "File: " << fileName;
	Gotoxy(x, ++y);
	Color(14);
	std::cout << "Title:";
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
	std::vector<std::string> wordsContent = splitSentence(content);
	//std::vector<int> posOfPhrase;
	std::set<int> posOfPhrase;
	std::set<std::string> keyword;
	for (auto ph : phrase) // process phrase of keyword
	{
		std::vector<std::string> tmp = splitSentence(ph);
		for (auto i : tmp)
		{
			std::string tmp = i;
			Tolower(tmp);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp[0], delimeter))
				tmp.erase(0, 1);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp.back(), delimeter))
				tmp.pop_back();
			if (IsStringWiths(tmp))
			{
				tmp.pop_back();
				tmp.pop_back();
			}
			keyword.insert(tmp);
		}
	}
	//
	for (auto p : phrase) // define which phrase appear first;
	{
		int tmp = SearchForPhraseInContent(p);
		if (tmp != -1)
			posOfPhrase.insert(tmp);
	}
	if (!posOfPhrase.empty())
	{
		int min = (*posOfPhrase.begin()), cnt = 0;
		int count = 0, len = 0;
		for (int i = min; i < (int)content.size() && count < 50; ++i)
		{

			if ((content[i] == ' ' && i > 0 && content[i - 1] != ' ') ||
				(content[i] == '\n' && i > 0 && content[i - 1] != '\n' && content[i - 1] != ' '))
			{
				++count;
			}
			++len;
		}
		std::string toDisplay = content.substr(min, len);
		std::vector<std::string> splitToDisplay = splitSentence(toDisplay);
		std::vector<std::string> process;

		for (auto i : splitToDisplay)
		{
			std::string tmp = i;
			Tolower(tmp);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp[0], delimeter))
				tmp.erase(0, 1);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp.back(), delimeter))
				tmp.pop_back();
			if (IsStringWiths(tmp))
			{
				tmp.pop_back();
				tmp.pop_back();
			}
			process.push_back(tmp);
		}

		if (min != 0)
		{
			std::pair<std::string, bool> last;
			last.first = "...";
			last.second = false;
			paragraphForShowing.push_back(last);
		}

		for (int i = 0; i < (int)splitToDisplay.size(); ++i)
		{
			std::pair<std::string, bool> word;
			word.first = splitToDisplay[i];
			if (std::find(keyword.begin(), keyword.end(), process[i])!=keyword.end())
				word.second = true;
			paragraphForShowing.push_back(word);
		}
	}
	else
	{
		std::vector<std::string> toloweredContent;

		for (auto i : wordsContent)
		{
			std::string tmp = TolowerExtend(i);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp[0], delimeter))
				tmp.erase(0, 1);
			while ((int)tmp.size() > 0 && IsDelimeter(tmp.back(), delimeter))
				tmp.pop_back();
			if (IsStringWiths(tmp))
			{
				tmp.pop_back();
				tmp.pop_back();
			}
			toloweredContent.push_back(tmp);
		}

		std::set<int> pos;

		for (auto i : keyword)
		{
			auto it = std::find(toloweredContent.begin(), toloweredContent.end(), i);
			if (it != toloweredContent.end())
			{
				int d = (int)std::distance(toloweredContent.begin(), it);
				pos.insert(d);
			}
		}
		if (pos.empty())
		{
			int cnt = 0;
			for (int i = 0; i < (int)wordsContent.size() && cnt < 50; ++i)
			{
				std::pair<std::string, bool> word;
				word.first = wordsContent[i];
				word.second = false;
				paragraphForShowing.push_back(word);
				++cnt;
			}
		}
		else
		{
			//int min = pos[0], cnt = 0;
			int min = (*pos.begin()), cnt = 0;
			if (min != 0)
			{
				std::pair<std::string, bool> last;
				last.first = "...";
				last.second = false;
				paragraphForShowing.push_back(last);
			}

			for (int i = min; i < (int)wordsContent.size() && cnt < 50; ++i)
			{
				std::pair<std::string, bool> word;
				word.first = wordsContent[i];
				auto kw = std::find(keyword.begin(), keyword.end(), toloweredContent[i]);
				auto phr = std::find(phrase.begin(), phrase.end(), toloweredContent[i]);
				if (kw != keyword.end() || phr != phrase.end())
					word.second = true;
				paragraphForShowing.push_back(word);
				++cnt;
			}
		}
	}
	if ((int)paragraphForShowing.size() < 5)
	{
		std::pair<std::string, bool> last;
		last.first = "...";
		last.second = false;
		paragraphForShowing.insert(paragraphForShowing.begin(), last);
		int cnt = (int)paragraphForShowing.size();
		for (int i = (int)(wordsContent.size() - cnt); i >= 0 && cnt < 50; --i)
		{
			std::pair<std::string, bool> word;
			word.first = wordsContent[i];
			word.second = false;
			paragraphForShowing.insert(paragraphForShowing.begin(), word);
			++cnt;
		}
	}
	else
	{
		std::pair<std::string, bool> last;
		last.first = "...";
		last.second = false;
		paragraphForShowing.push_back(last);
	}
}

void Document::debug()
{
	/*if (paragraphForShowing.empty())
		return;*/
	std::cout << "size: " << paragraphForShowing.size() << '\n';
	std::cout << fileName << '\n';
	for (auto i : paragraphForShowing)
		std::cout << i.first << ' ';
}

void Document::getWordsIntitle(std::vector<std::string> &phrase) {
	for (auto i : phrase) {
		std::vector<std::string> words = splitSentence(i);
		for(auto j:words)
			wordsIntitle.insert(j);
	}
}

void Document::ColorTitle() {
	std::string word;
	std::stringstream ss(title);
	while (ss) {
		ss >> word;
		if (wordsIntitle.find(word) != wordsIntitle.end()) {
			Color(10);
			std::cout << " " + word;
			Color(14);
		}
		else {
			bool found = false;
			for (auto i : wordsIntitle) {
				auto pos = word.find(i);
				if (pos != std::string::npos) {
					std::cout << " ";
					int k = 0;
					while (k != pos)
						std::cout << word[k++];
					int len = i.length();
					Color(10);
					while (k < len)
						std::cout << word[k++];
					Color(14);
					len = word.length();
					while (k < len)
						std::cout << word[k++];
					found = true;
					break;
				}
			}
			if(!found)
				std::cout << " " + word;
		}
		word.clear();
	}
}

bool Document::IsTheSameString(const std::string& stringToCompare, const std::string& paragraph, const int& pos)
{
	if (pos > 0)
	{
		int pre = pos - 1;
		if (paragraph[pre] >= 'a' && paragraph[pre] <= 'z') return false;
		if (paragraph[pre] >= 'A' && paragraph[pre] <= 'Z') return false;
		if (paragraph[pre] == '-') return false;
	}
	if (pos + (int)stringToCompare.length() < (int)paragraph.length())
	{
		int next = pos + (int)stringToCompare.length();
		if (paragraph[next] >= 'a' && paragraph[next] <= 'z') return false;
		if (paragraph[next] >= 'A' && paragraph[next] <= 'Z') return false;
		if (paragraph[next] == '-') return false;
	}
	return true;
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
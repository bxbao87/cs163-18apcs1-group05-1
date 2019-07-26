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
	std::getline(in, title);
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

void Document::Display(int x, int y) {// not finished
	Gotoxy(x, y);
	Color(9);
	std::cout << fileName;
	Gotoxy(x, y + 1);
	Color(14);
	std::cout << title;
	Gotoxy(x, y + 2);
	int len = 0;
	for (auto i : paragraphForShowing) {
		if (len + i.first.length() > 140)
		{
			Gotoxy(x, ++y);
			len = 0;
		}
		len += i.first.length();
		if (i.second == true) {
			Color(12);
			std::cout << i.first;
			Color(15);
		}
		else
			std::cout << i.first;
	}
}

void Document::GetParagraphForShowing(const std::vector<std::string>& keyword)
{
	std::vector<int> pos;
	pos.clear();
	for (auto i : keyword)
	{
		auto cur = content.find(i);
		if (cur != std::string::npos)
			pos.push_back((int)cur);
	}

	int minPos = pos[0];
	for (auto i : pos)
		if (i < minPos)
			minPos = i;

	int count = 0,len=0;
	for (int i =minPos; count < 50; ++i)
	{
		std::cout << content[i];
		if ((content[i] == ' ' && content[i - 1] != ' ') || 
			(content[i] == '\n' && content[i - 1] != '\n' && content[i-1]!=' '))
		{
			++count;
		}
		++len;
	}

	std::string toDisplay = content.substr(minPos, len);
	std::cout << toDisplay << '\n';
	std::vector<std::string> splitToDisplay = splitSentence(toDisplay);
	paragraphForShowing.clear();
	for (auto i : splitToDisplay)
	{
		std::pair<std::string, bool> word;
		word.first = i;
		if (std::find(keyword.begin(), keyword.end(), i) != keyword.end())
			word.second = true;
		paragraphForShowing.push_back(word);
	}

}

void Document::debug()
{
	std::cout << "size: " << paragraphForShowing.size() << '\n';
	for (auto i : paragraphForShowing)
		std::cout << i.first << ' ';
}


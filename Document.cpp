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

void Document::Display(int x, int y) {
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
#include "Document.h"

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

void Document::DisplayFile()
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

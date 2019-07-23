#pragma once
#ifndef Document_h
#define Document_h
#include "Support.h"

class Document
{
private:
	std::string fileName;
	std::string title;
	std::string content;
	std::vector<std::pair<std::string, bool> > paragraphForShowing; // If bool is true then the word need to be highlighted

	//const std::string link = "Data\\";
public:
	Document();
	Document(std::string fileName);

	void SetFileName(const std::string& name); // Set filename of this object
	void ReadFile(); // Read file txt to this object
	void OpenFile(); // Open file using notepad

	int SearchForPhraseInContent(const std::string& phrase); // Return the position of the phrase need to be searched in content
	int SearchForPhraseInTitle(const std::string& phrase); // Retunr the position of the phrase need to be searched in title
};

#endif

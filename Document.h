#pragma once
#ifndef Document_h
#define Document_h
#include "Support.h"

class Document
{
private:
	std::string fileName;
	std::string title;
	std::vector<std::string> content;

	const std::string link = "Data\\";
public:
	Document();
	Document(std::string fileName);
	void SetFileName(const std::string& name);
	void ReadFile();
};

#endif

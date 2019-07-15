#pragma once
#ifndef NumIndex_h
#define NumIndex_h
#include "Support.h"

class NumIndex
{
private:
	std::map<double, std::vector<std::string> > numList;
	const std::string link = "Process\\index_num.txt";
public:
	NumIndex();
	~NumIndex();

	void SaveNumIndex(); // Save the numIndex to Process/index_num.txt
	bool LoadNumIndex(); // Load the numIndex from Process/index_num.txt
	void AddNum(const double& val, const std::string& inFile); // Add val from inFile
	void AddNum(const double& val, const std::vector<std::string>& fileList); // Add val from fileList
};

#endif

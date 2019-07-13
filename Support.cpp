#include "Support.h"

bool isDelimiter(const char & c)
{
	std::vector <char> delimiter = { '.', ',', '\'', '?', '\"', '\n', '!' };
	for (int i = 0; i < delimiter.size(); i++)
		if (c == delimiter[i])
			return true;
	return false;
}

std::vector<std::string> AND(std::vector<std::string>& v1, std::vector<std::string>& v2)
{
	std::vector<std::string> intersection;
	
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	int index1 = 0, index2 = 0;
	while (index1 < v1.size() && index2 < v2.size())
	{
		if (v1[index1].compare(v2[index2]) < 0)//v1[i] < v2[j]
			++index1;
		else if (v1[index1].compare(v2[index2]) > 0)//v1[i] > v2[j]
			++index2;
		else 
		{
			intersection.push_back(v1[index1]);
			++index1, ++index2;
		}
	}

	while (index1 < v1.size()) {
		if (v1[index1] == v2[v2.size()-1])
			intersection.push_back(v1[index1]);
		++index1;
	}

	while (index2 < v2.size()) {
		if (v1[v1.size()-1] == v2[index2])
			intersection.push_back(v2[index2]);
		++index2;
	}

	return intersection;
}

#include "NumIndex.h"

NumIndex::NumIndex()
{
	numList.clear();
}

NumIndex::~NumIndex()
{
}

void NumIndex::SaveNumIndex()
{
	std::ofstream ou(link);
	for (auto i : numList)
	{
		ou << i.first << ' ';
		ou << i.second.size() << '\n';
		for (auto j : i.second) ou << j << ' ';
		ou << '\n';
	}
	ou.close();
}

bool NumIndex::LoadNumIndex()
{
	std::ifstream in(link);
	if (!in.is_open()) return false;
	double num;
	while (in >> num)
	{
		std::vector<int> fileList;
		int total;
		in >> total;
		for (int i = 0; i < total; ++i)
		{
			int fileName;
			in >> fileName;
			fileList.push_back(fileName);
		}
		AddNum(num, fileList);
	}
	in.close();
	return true;
}

void NumIndex::AddNum(const double& val, const int& inFile)
{
	numList[val].push_back(inFile);
}

void NumIndex::AddNum(const double& val, const std::vector<int>& fileList)
{
	numList[val] = fileList;
}

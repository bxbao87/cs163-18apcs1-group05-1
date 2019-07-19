#include "Support.h"

bool isNumber(const char& c)
{
	if (c < '0' || c > '9')
		return false;
	return true;
}

bool isNumberWithChar(std::string & s)
{
	if (s.empty()) return false;
	if (s[0] == '$') s.erase(0, 1);
	if (s.empty()) return false;
	if (s.back() == '$') s.pop_back();
	if (s.empty()) return false;

	for (int i = 0; i < (int)s.size(); ++i)
	{
		if (s[i] == '.' || s[i] == ',') continue;
		if (s[i] < '0' || s[i] > '9')
		{
			return false;
		}
	}
	return true;
	
}

bool isMixType(const std::string & s)
{
	bool flag = false;

	if (isNumber(s[0]))
		flag = true; // if the first char is number, flag is true
	for (int i = 0; i < (int)s.size(); ++i)
	{
		if (flag == true && s[i]!='.' && s[i]!=',' && !isNumber(s[i]))
			return true;
		if (flag == false && isNumber(s[i]))
			return false;
	}
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
			if (v1[index1] == v2[v2.size() - 1])
				intersection.push_back(v1[index1]);
			++index1;
		}

		while (index2 < v2.size()) {
			if (v1[v1.size() - 1] == v2[index2])
				intersection.push_back(v2[index2]);
			++index2;
		}

		return intersection;
	}


std::vector<std::string> splitSentence(const std::string& s) // split string into vector<string>
{
	std::vector<std::string> a;
	a.clear();
	std::istringstream iss(s);

	while (iss)
	{
		std::string word;
		iss >> word;
		if (word.length())
			a.push_back(word);
	}
	return a;
}

void Tolower(std::string& s) // Change a string to lower case
{
		for (int i = 0; i < s.length(); ++i)
			s[i] = tolower(s[i]);
}


std::vector<std::string> OR(const std::vector<std::string>& v1, const std::vector<std::string>& v2)
{
	std::vector<std::string> res;
	res.clear();

	std::set<std::string> tmp;
	tmp.clear();

	std::string s;

	for (int i = 0; i < v1.size() && i<v2.size(); ++i)
	{
		s = v1[i];
		tmp.insert(s);
		s = v2[i];
		tmp.insert(s);
	}
	for (int i = v1.size(); i < v2.size(); ++i)// if v1 is shorter than v2
	{
		s = v2[i];
		tmp.insert(s);
	}
	for (int i = v2.size(); i < v1.size(); ++i) // if v2 is shorter than v1
	{
		s = v1[i];
		tmp.insert(s);
	}
	for (std::set<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		res.push_back(*it);
	}
	return res;
}

bool isSub(const std::string & hist, const std::string & query)
{
	if (hist.find(query) != std::string::npos)
		return true;
	return false;
}

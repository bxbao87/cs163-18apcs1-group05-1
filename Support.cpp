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
			return true;
	}
	return false;
}


void AND(std::vector<int>& v1, std::vector<int>& v2,std::vector<int>& intersection)
{

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	int index1 = 0, index2 = 0;
	while (index1 < v1.size() && index2 < v2.size())
	{
		if (v1[index1]<v2[index2])//v1[i] < v2[j]
			++index1;
		else if (v1[index1] > v2[index2])//v1[i] > v2[j]
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
		for (int i = 0; i <(int)s.length(); ++i)
			s[i] = tolower(s[i]);
}


void OR(const std::vector<int>& v1, const std::vector<int>& v2,std::vector<int>& res)
{
	res.clear();

	std::set<int> tmp;
	tmp.clear();

	//std::string s;

	for (int i = 0; i <(int)v1.size() && i<(int)v2.size(); ++i)
	{
		//s = v1[i];
		tmp.insert(v1[i]);
		//s = v2[i];
		tmp.insert(v2[i]);
	}
	for (int i =(int)v1.size(); i <(int)v2.size(); ++i)// if v1 is shorter than v2
	{
		//s = v2[i];
		tmp.insert(v2[i]);
	}
	for (int i =(int)v2.size(); i <(int)v1.size(); ++i) // if v2 is shorter than v1
	{
		//s = v1[i];
		tmp.insert(v1[i]);
	}
	for (std::set<int>::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		res.push_back(*it);
	}
}

bool isSub(const std::string & hist, const std::string & query)
{
	if (hist.find(query) != std::string::npos)
		return true;
	return false;
}

int IsWhichKind(const std::string& var)
{
	if (var.empty()) return 0;
	bool isNum = true;
	for (auto i : var)
	{
		if (i < 0 || i > 255) return 0;
		if (i == '.' || i == ',') continue;
		if (i < '0' || i > '9')
		{
			isNum = false;
			break;
		}
	}
	if (isNum) return 1;
	return 2;
}

int ConvertCharToNum(const char& c)
{
	if (c >= 'a' && c <= 'z') return c - 'a';
	if (c >= '0' && c <= '9') return c - '0' + 26;
	if (c == '-') return 36;
	if (c == '#') return 37;
	return -1;
}

char ConvertNumToChar(const int& x)
{
	if (x >= 0 && x <= 25) return (char)(x + 'a');
	if (x >= 26 && x <= 35) return (char)(x - 26 + '0');
	if (x == 36) return '-';
	if (x == 37) return '#';
	return '?';
}

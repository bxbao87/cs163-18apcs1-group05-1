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

bool isNumberWithCharExtended(const std::string & s)
{
	if (s.empty()) return false;

	for (int i = 0; i < (int)s.size(); ++i)
	{
		if (s[i] == '.' || s[i] == ',' || s[i] == '%' || s[i] == '$') continue;
		if (s[i] < '0' || s[i] > '9')
		{
			return false;
		}
	}
	return true;
}


void AND(std::vector<int>& v1, const std::vector<int>& v2)
{
	std::set<int> intersection;
	AddToSet(v1, intersection);
	v1.clear();
	for (auto i : v2)
	{
		if (intersection.count(i) != 0) 
			v1.push_back(i);
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

std::string TolowerExtend(std::string & s)
{
	std::string tmp = s;
	for (int i = 0; i < (int)tmp.length(); ++i)
		tmp[i] = tolower(tmp[i]);
	return tmp;
}


void OR(std::vector<int>& v1, const std::vector<int>& v2)
{
	std::set<int> uni;
	AddToSet(v1, uni);
	AddToSet(v2, uni);
	v1.clear();
	for (auto i : uni)
		v1.push_back(i);
}

void NOT(std::vector<int>& res, const std::vector<int>& complement)
{
	for (auto i : complement) {
		auto it = find(res.begin(), res.end(), i);
		if (it != res.end())
			res.erase(it);
	}
}

bool isSub(const std::string & hist, const std::string & query)
{
	if (hist.find(query) != std::string::npos)
		return true;
	return false;
}

void AddToSet(const std::vector<int>& a, std::set<int>& s)
{
	for (auto i : a)
		s.insert(i);
}

void AddToMap(const std::vector<int>& v, std::map<int,int> &mp) {
	for (auto i : v)
		++mp[i];
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
	if (c == '\'') return 38;
	return -1;
}

char ConvertNumToChar(const int& x)
{
	if (x >= 0 && x <= 25) return (char)(x + 'a');
	if (x >= 26 && x <= 35) return (char)(x - 26 + '0');
	if (x == 36) return '-';
	if (x == 37) return '#';
	if (x == 38) return '\'';
	return '?';
}

bool IsNothing(const std::string &str) {
	int len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ')
			return false;
	}
	return true;
}
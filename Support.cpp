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

bool loadStopWord(std::set<std::string>& stopword) // load stopword into set 
{
	std::ifstream fin;
	fin.open("/cs163-18apcs1-group05/Process/stopword.txt");
	if (!fin.is_open()) return false;
	std::string word;
	while (!fin.eof())
	{
		fin >> word;
		stopword.insert(word);
	}
	fin.close();
	return true;
}

void Tolower(std::string& s) // Change a string to lower case
{
	for (int i = 0; i < s.length(); ++i)
		s[i] = tolower(s[i]);
}

std::vector<std::string> RemoveStopWord(const std::vector<std::string>& words)
{
	std::vector<std::string> afterRemove;
	afterRemove.clear();

	std::set<std::string> stopwords;
	if(!loadStopWord(stopwords))
		std::cout<<"Can't open file stopword";

	std::string word;

	for (int i = 0; i < words.size(); ++i)
	{

		word = words[i];
		Tolower(word);
		if (stopwords.find(word) == stopwords.end())
			afterRemove.push_back(word);
	}
	return afterRemove;
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

bool isPrefix(const std::string & check, const std::string & query)
{
	if (check.size() < query.size())
		return false;
	std::string compareString(check, 0, query.size());
	return !compareString.compare(query);
}
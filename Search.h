#pragma once
#ifndef Search_h
#define Search_h
#include "Support.h"
#include "Trie.h"
#include "frontEnd.h"
#include "NumIndex.h"
#include "History.h"
#include "Document.h"

#define CalcTime 

class Search
{
private:
	Trie trie;
	NumIndex numIndex;
	std::set<std::string> stopWord;
	std::map<std::string, std::vector<std::string> > synonym;
	std::vector<std::string> theFullListOfFile;

	const std::set <char> delimeter = { '.', ',', '\'', '?', '\"', '\n', '!', '(', ')','-','/',
		'&','[',']','+',':','`','@','%','^','=','_', '\\', '|', '$', '~'};

public:
	Search();
	~Search();

	void Run(); // main function
	void ReadSingleFile(const std::string &fileName, std::vector<std::string>& tokenVector);//Read a single file and return a vector string of tokens
	void GetFilename(const std::string rootDirectory, std::vector<std::string>& pathVector);//Return all file in rootDirectory folder
	std::vector<std::string> RemoveStopWord(const std::vector<std::string>& words); // Remove stop word from words
	std::vector<std::string> RemoveWeirdWord(const std::vector<std::string>& words); // Remove weird word containing weird character

	bool IsStopWord(const std::string& word);
	bool IsDelimeter(const char& c); //Check if char c is a delimiter . , ! ? ' " 
	bool IsWeirdWord(const std::string& word); // Check if word has weird character
	bool LoadSynonym(); // Load file synonym from synonym.txt into map synonym
	bool LoadStopWord(); // load stopword from stopword.txt into set stopWord
	//bool CreateIndexForAFile(const std::string& fileName); // create inverted index for a single file
	bool CreateIndex(); // create inverted index

	//Extract command and split into subqueries
	std::string InfixToPostfix(const std::string &query);
	std::string PreProcess(const std::string & query);
	void SplitQuery(const std::string& query, std::vector<std::string> &intitle, std::vector<std::string> &content);
	void TrimQuery(std::string &query, std::vector <std::string> &intitle, std::vector <std::string> &content);
	bool IsExactQuery(const std::string & query);//check if it there is a quote in query
	bool IsOpenBracket(const std::string & query); //check if there is a open bracket in the query
	bool IsCloseBracket(const std::string & query);//check if there is a close bracket in the query
	bool IsIntitleQuery(const std::string & query);
	bool IsPlaceHolderQuery(const std::string & query);
	bool IsPlusQuery(const std::string & query);
	bool IsMinusQuery(const std::string & query);
	bool IsRangeQuery(const std::string & query);
	//Process subqueries
	int SwitchQuery(const std::string & subquery);
	std::vector <int> Process(const std::string &query);//Need to changes data structure corresponding to OR and AND ds

	bool LoadListOfFile();
	void SaveListOfFile();

	// search exact query
	std::vector<int> SearchExact(const std::string &phrase);
	std::vector<int> SearchNormal(const std::string &phrase);
	bool HaveExactString(const int& pos, const std::string& phrase);
	bool SearchNumber(const double& key,std::vector<int>& result ); // Search number
	bool SearchRange(const double& key1, const double& key2,std::vector<int>& result);// Search range
	void PreProcessRangeQuery(const std::string query, double &lo, double &hi);//Return range of the query
	std::vector<int> SearchSynonym(const std::string &phrase);
	std::vector<int> SearchPlus(const std::string &phrase);
	std::vector<int> SearchMinus(const std::string &phrase);
	std::vector<int> SearchPlaceHolder(const std::string &phrase);//Search place holder
	std::vector<int> SearchIntitle(const std::string &phrase);

	bool InputKey(std::string &resultStr);
	void GetFileNameByInt(const std::vector<int>& toGet, std::vector<std::string>& fileName);

	void Debug(std::vector <int>& v);

	std::vector<int> Ranking(std::vector<int>& finalList, std::vector<std::string>& subQuery);

	void Test200Query();
};

#endif

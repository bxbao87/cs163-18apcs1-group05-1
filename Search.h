#pragma once
#ifndef Search_h
#define Search_h
#include "Support.h"
#include "Trie.h"
#include "frontEnd.h"
#include "NumIndex.h"
#include "History.h"

//#define CalcTime 

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
	bool IsExactQuery(const std::string & query);//check if it there is a quote in query
	bool IsOpenBracket(const std::string & query); //check if there is a open bracket in the query
	bool IsCloseBracket(const std::string & query);//check if there is a close bracket in the query

	bool LoadListOfFile();
	void SaveListOfFile();

	// search exact query
	void SearchExact(std::string &str);





	std::string InputKey(int x, int y);

};

#endif

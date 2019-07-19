#pragma once
#ifndef Search_h
#define Search_h
#include "Support.h"
#include "Trie.h"
#include "frontEnd.h"
#include "NumIndex.h"
#include "History.h"

class Search
{
private:
	Trie trie;
	NumIndex numIndex;
	std::set<std::string> stopWord;
	std::map<std::string, std::vector<std::string> > synonym;

	const std::set <char> delimeter = { '.', ',', '\'', '?', '\"', '\n', '!', '(', ')','-','/',
		'&','[',']','+',':','`','@','%','^','=','_', '\\', '|' };

public:
	Search();
	~Search();

	void Run(); // main function
	void ReadSingleFile(const std::string &fileName, std::vector<std::string>& tokenVector);//Read a single file and return a vector string of tokens
	std::vector<std::string> GetFilename(const std::string rootDirectory);//Return all file in rootDirectory folder
	std::vector<std::string> RemoveStopWord(const std::vector<std::string>& words); // Remove stop word from words
	std::vector<std::string> RemoveWeirdWord(const std::vector<std::string>& words); // Remove weird word containing weird character

	bool IsStopWord(const std::string& word);
	bool IsDelimeter(const char& c); //Check if char c is a delimiter . , ! ? ' " 
	bool IsWeirdWord(const std::string& word); // Check if word has weird character
	bool LoadSynonym(); // Load file synonym from synonym.txt
	bool LoadStopWord(); // load stopword into set 
	//bool CreateIndexForAFile(const std::string& fileName); // create inverted index for a single file
	bool CreateIndex(); // create inverted index

	std::string InputKey(int x, int y);

};

#endif

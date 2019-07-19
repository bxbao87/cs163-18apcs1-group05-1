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
public:
	Search();
	~Search();

	bool LoadSynonym();
	void Run();
	std::vector<std::string> ReadSingleFile(const std::string &fileName);//Read a single file and return a vector string of tokens
	std::vector<std::string> GetFilename(const std::string rootDirectory);//Return all file in rootDirectory folder
	bool LoadStopWord(std::set<std::string>& stopword); // load stopword into set 
	std::vector<std::string> RemoveStopWord(const std::vector<std::string>& words);

	bool CreateIndex();

	std::string InputKey(int x, int y);

};

#endif

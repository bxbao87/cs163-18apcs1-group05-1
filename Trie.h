#pragma once
#ifndef Trie_h
#define Trie_h
#include "Support.h"

struct Node
{
	Node* Next[40]; // a..z : 0..25, 0..9 : 26..35, - : 36, # : 37, ' : 38
	std::vector<int> fileList;
	Node();
	~Node();
};

class Trie
{
private:
	Node* pRoot;
	const std::string link = "Process\\index.txt";

	void PrintTrieTo(Node* pRoot, std::string key, std::ostream& cout); // print the key and its filelist to file
	Node* TraverseTrie(Node*& pRoot, const std::string& key, const bool& newBranch); 
		// return the node of string key on trie if newBranch is true then 
		// this function will create new branch if there wasn't a branch there before (new branch = true only for add key)
public:
	Trie();
	~Trie();
	void AddKey(const std::string& key, const int& inFile); // Add a key from a file to trie
	void AddKey(const std::string& key, std::vector<int>& fileList); // Add a key and its fileList to trie
	void AddManyKey(const std::vector<std::string>& keyList, const int& inFile); // Add a list of key and their file

	std::vector<int> GetKey(const std::string& key); // Return fileList of a key
	void SaveTrie(); // Save trie into link
	bool LoadTrie(); // Load trie from file
};

#endif
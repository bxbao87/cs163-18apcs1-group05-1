#pragma once
#ifndef Trie_h
#define Trie_h
#include "Support.h"

struct Node
{
	std::map<char, Node*> Next;
	std::vector<std::string> fileList;
	Node();
	~Node();
};

class Trie
{
private:
	Node* pRoot;

	void PrintTrieTo(Node* pRoot, std::string key, std::ostream& cout); // print the key and its filelist to file
	Node* TraverseTrie(Node*& pRoot, const std::string& key, const bool& newBranch); // return the node of string key on trie
public:
	Trie();
	void AddKey(const std::string& key, const std::string& inFile); // Add a key from a file to trie
	void AddKey(const std::string& key, const std::vector<std::string> fileList); // Add a key and its fileList to trie
	
	std::vector<std::string> GetKey(const std::string& key); // Return fileList of a key
	void SaveTrie(const std::string& fileName); // Save trie into file
	void LoadTrie(const std::string& fileName); // Load trie from file
};

#endif
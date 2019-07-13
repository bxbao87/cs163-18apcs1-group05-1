#include "Search.h"

Search::Search()
{
	system("md Process");
	system("md Data");
}

void Search::Run()
{
	std::string fileName = "Process\\index.txt";
	trie.LoadTrie(fileName);
	trie.SaveTrie(fileName);
}

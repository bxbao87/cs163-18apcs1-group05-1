#pragma once
#ifndef Search_h
#define Search_h
#include "Support.h"
#include "Trie.h"
#include "frontEnd.h"

class Search
{
private:
	Trie trie;
public:
	Search();
	void Run();
};

#endif

#include "Trie.h"

Node::Node()
{
	Next.clear();
	fileList.clear();
}

Node::~Node()
{
	for (auto i : Next)
	{
		delete i.second;
	}
	Next.clear();
	fileList.clear();
}

void Trie::PrintTrieTo(Node* pRoot, std::string key, std::ostream& cout)
{
	if (pRoot == nullptr) return;
	if (!pRoot->fileList.empty())
	{
		cout << key << ' ';
		cout << pRoot->fileList.size() << ' ';
		for (auto i : pRoot->fileList) 
			cout << i << ' ';
		cout << '\n';
	}
	for (auto i : pRoot->Next)
	{
		PrintTrieTo(i.second, key + i.first, cout);
	}
}

Node* Trie::TraverseTrie(Node*& pRoot, std::string key)
{
	if (pRoot == nullptr) pRoot = new Node();
	Node* cur = pRoot;
	for (auto c : key)
	{
		if (cur->Next.count(c) == 0) cur->Next[c] = new Node();
		cur = cur->Next[c];
	}
	return cur;
}

Trie::Trie()
{
	pRoot = nullptr;
}

void Trie::AddKey(const std::string& key, const std::string& inFile)
{
	Node* cur = TraverseTrie(pRoot, key);
	cur->fileList.push_back(inFile);
}

void Trie::AddKey(const std::string& key, const std::vector<std::string> fileList)
{
	Node* cur = TraverseTrie(pRoot, key);
	cur->fileList = fileList;
}

void Trie::SaveTrie(const std::string& fileName)
{
	std::ofstream ou(fileName);
	PrintTrieTo(pRoot, "", ou);
	ou.close();
}

void Trie::LoadTrie(const std::string& fileName)
{
	std::ifstream in(fileName);
	std::string key;
	while (in >> key)
	{
		int total;
		std::vector<std::string> fileList;
		in >> total;
		for (int i = 0; i < total; ++i)
		{
			std::string inFile;
			in >> inFile;
			fileList.push_back(inFile);
		}
		AddKey(key, fileList);
	}
}

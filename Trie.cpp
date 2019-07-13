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

Node* Trie::TraverseTrie(Node*& pRoot, const std::string& key, const bool& newBranch)
{
	if (pRoot == nullptr) pRoot = new Node();
	Node* cur = pRoot;
	for (auto c : key)
	{
		if (cur->Next.count(c) == 0)
		{
			if (!newBranch) return nullptr;
			cur->Next[c] = new Node();
		}
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
	bool newBranch = true;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur == nullptr) return;
	cur->fileList.push_back(inFile);
}

void Trie::AddKey(const std::string& key, const std::vector<std::string> fileList)
{
	bool newBranch = true;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur == nullptr) return;
	cur->fileList = fileList;
}

void Trie::AddManyKey(const std::vector<std::string>& keyList, const std::string& inFile)
{
	for (auto key : keyList)
	{
		AddKey(key, inFile);
	}
}

std::vector<std::string> Trie::GetKey(const std::string& key)
{
	bool newBranch = false;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur != nullptr) return cur->fileList;
	else return std::vector<std::string>();
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

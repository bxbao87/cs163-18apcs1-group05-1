#include "Trie.h"

Node::Node()
{
	//Next.clear();
	for (int i = 0; i < 40; ++i) Next[i] = nullptr;
	fileList.clear();
}

Node::~Node()
{
	for (int i = 0; i < 40; ++i) delete Next[i];
	fileList.clear();
}

void Trie::PrintTrieTo(Node* pRoot, std::string key, std::ostream& cout)
{
	if (pRoot == nullptr) return;
	if (!pRoot->fileList.empty())
	{
		cout << key << ' ';
		cout << pRoot->fileList.size() << '\n';
		for (auto i : pRoot->fileList)
			cout << i << ' ';
		cout << '\n';
	}
	for (int i = 0; i < 40; ++i) 
		PrintTrieTo(pRoot->Next[i], key + ConvertNumToChar(i), cout);
}

Node* Trie::TraverseTrie(Node*& pRoot, const std::string& key, const bool& newBranch)
{
	if (pRoot == nullptr) pRoot = new Node();
	Node* cur = pRoot;
	for (auto c : key)
	{
		int value = ConvertCharToNum(c);
		if (value == -1) return nullptr;
		if (cur->Next[value] == nullptr)
		{
			if (!newBranch) return nullptr;
			cur->Next[value] = new Node();
		}
		cur = cur->Next[value];
	}
	return cur;
}

Trie::Trie()
{
	pRoot = nullptr;
}

Trie::~Trie()
{
	delete pRoot;
}

void Trie::AddKey(const std::string& key, const int& inFile)
{
	bool newBranch = true;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur == nullptr) return;
	cur->fileList.push_back(inFile);
}

void Trie::AddKey(const std::string& key, std::vector<int>& fileList)
{
	bool newBranch = true;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur == nullptr) return;
	swap(cur->fileList, fileList);
}

void Trie::AddManyKey(const std::vector<std::string>& keyList, const int& inFile)
{
	for (auto key : keyList)
	{
		AddKey(key, inFile);
	}
}

std::vector<int> Trie::GetKey(const std::string& key)
{
	bool newBranch = false;
	Node* cur = TraverseTrie(pRoot, key, newBranch);
	if (cur != nullptr) return cur->fileList;
	else return std::vector<int>();
}

void Trie::SaveTrie()
{
	std::ofstream ou(link);
	PrintTrieTo(pRoot, "", ou);
	ou.close();
}

bool Trie::LoadTrie()
{
	std::ifstream in(link);
	if (!in.is_open()) return false;
	std::string key;
	while (in >> key)
	{
		int total;
		std::vector<int> fileList;
		in >> total;

		//if (total > 1000) std::cerr << key << ' ' << total << '\n';

		int tmp;
		for (int i = 0; i < total; ++i)
		{
			in >> tmp;
			fileList.push_back(tmp);
		}
		AddKey(key, fileList);
	}
	in.close();
	return true;
}

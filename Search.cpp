#include "Search.h"

Search::Search()
{
	system("md Process");
	system("md Data");

#ifdef CalcTime
	auto startTime = clock();
#endif
	if (!LoadSynonym())
		std::cerr << "Can't open synonym file\n";
	if (!LoadStopWord())
		std::cerr << "Can't open stop word file\n";

	bool loadListOfFile = LoadListOfFile();
	bool loadTrie = trie.LoadTrie();
	bool loadNumIndex = numIndex.LoadNumIndex();
#ifdef CalcTime
	auto endTime = clock();
	std::cerr << "Load Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << '\n';
#endif

	if (!(loadListOfFile && loadTrie && loadNumIndex))
	{
		CreateIndex();
		SaveListOfFile();
		trie.SaveTrie();
		numIndex.SaveNumIndex();
	}
}

Search::~Search()
{
}

bool Search::IsStopWord(const std::string& word)
{
	if (stopWord.count(word) != 0) return true;
	return false;
}

bool Search::IsDelimeter(const char& c)
{
	if (delimeter.count(c) != 0) return true;
	else return false;
}

bool Search::IsWeirdWord(const std::string& word)
{
	for (auto c : word)
	{
		if (c < 0 || c > 255) return true;
	}
	return false;
}

bool Search::LoadSynonym()
{
	std::ifstream in("Process\\synonym.txt");
	if (!in.is_open()) return false;
	std::string word;
	while (std::getline(in, word) && word != "")
	{
		std::string listOfWord;
		std::getline(in, listOfWord);
		std::stringstream ss(listOfWord);

		std::string wordInList;
		while (ss >> wordInList) synonym[word].push_back(wordInList);
	}
	in.close();
	return true;
}

void Search::Run()
{
	FrontEnd();

	std::string query = "";
	while (InputKey(query))
	{
		query = InfixToPostfix(query);
		//std::cout << "May qua no thoat roi chu khong la no bay mau cmnr" << "\n";
		std::vector<int> result = Process(query);
		
		std::vector<Document> docs;
		int total = min((int)result.size(), 5);

		for (int i = 0; i < total; ++i)
			docs.push_back(Document(theFullListOfFile[result[i]]));

		for (auto& doc : docs)
			doc.ReadFile();

		int x = 20, y = 31, step = 10;
		for (auto& doc : docs)
		{
			doc.DisplayResult(x, y);
			y += step;
		}

		int chosen = ChooseLink(total);
		if (chosen != -1) docs[chosen].DisplayFile();

		_getch();

		SearchScreen();
		query.clear();
	}

	ExitScreen();
}

void Search::ReadSingleFile(const std::string & fileName, std::vector<std::string>& tokenVector)
{
	std::ifstream inFile(fileName);
	if (inFile.is_open()) {
		std::string fileData;
		//read everything into string
		std::string token;
		std::set<std::string> tokenSet;
		while (inFile >> token)
		{
			Tolower(token);
			while ((int)token.size() > 0 && IsDelimeter(token[0]))
				token.erase(0, 1);
			while ((int)token.size() > 0 && IsDelimeter(token.back()))
				token.pop_back();
			if (IsStopWord(token)) continue;
			if (!token.empty())
				tokenSet.insert(token);
		}
		
		for (auto i : tokenSet) tokenVector.push_back(i);
	}
	else
		std::cout << "File " << fileName << " is not found\n";
	inFile.close();
}

void Search::GetFilename(const std::string rootDirectory, std::vector<std::string>& pathVector)
{
	std::stringstream ss;
	for (auto & entry : std::experimental::filesystem::directory_iterator(rootDirectory)) {
		ss << entry.path();
		std::string token;
		std::string path;
		while (ss >> token)
			path += token + " ";
		path.pop_back();
		pathVector.push_back(path);
		ss.clear();
	}
	return;
}

bool Search::LoadStopWord()
{
	std::ifstream fin;
	fin.open("Process/stopword.txt");
	if (!fin.is_open()) return false;
	std::string word;
	while (!fin.eof())
	{
		fin >> word;
		stopWord.insert(word);
	}
	fin.close();
	return true;
}

std::vector<std::string> Search::RemoveStopWord(const std::vector<std::string>& words)
{
	std::vector<std::string> afterRemove;
	afterRemove.clear();

	std::string word;

	for (int i = 0; i <(int) words.size(); ++i)
	{
		word = words[i];
		Tolower(word);
		if (stopWord.find(word) == stopWord.end())
			afterRemove.push_back(word);
	}
	return afterRemove;
}

std::vector<std::string> Search::RemoveWeirdWord(const std::vector<std::string>& words)
{
	std::vector<std::string> answer;
	for (auto word : words)
	{
		if (!IsWeirdWord(word)) answer.push_back(word);
	}
	return answer;
}


bool Search::CreateIndex()
{
#ifdef CalcTime
	auto startTime = clock();
#endif
	GetFilename("Data", theFullListOfFile);

	if (theFullListOfFile.empty())
		return false;

	int cnt = 0;
	for (auto i : theFullListOfFile)
	{
		std::vector<std::string> wordsInFile;
		wordsInFile.clear();
		ReadSingleFile(i, wordsInFile);

		//if (wordsInFile.empty())
		//{
		//	std::cout << "Can't load file\n";
		//	//return false;
		//}

		for (int j = 0; j < (int)wordsInFile.size(); ++j)
		{
			if (isNumberWithChar(wordsInFile[j]))
			{
				double val = stod(wordsInFile[j]);
				numIndex.AddNum(val, cnt);
			}
			else
			{
				if (!wordsInFile[j].empty()) trie.AddKey(wordsInFile[j], cnt);
			}
		}
		++cnt;
	}
#ifdef CalcTime
	auto endTime = clock();
	std::cerr << "Build Trie Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
#endif
	return true;
}

bool Search::LoadListOfFile()
{
	std::ifstream in("Process\\filename.txt");
	if (!in.is_open()) return false;
	int total;
	in >> total;
	std::string filename;
	std::getline(in, filename);
	for (int i = 0; i < total; ++i)
	{
		std::getline(in, filename);
		theFullListOfFile.push_back(filename);
	}
	in.close();
	return true;
}

void Search::SaveListOfFile()
{
	std::ofstream ou("Process\\filename.txt");
	ou << theFullListOfFile.size() << '\n';
	for (auto name : theFullListOfFile)
		ou << name << '\n';
	ou.close();
}


bool Search::InputKey(std::string &resultStr) {
	int x = 28, y = 21;
	int key, len = 0;
	int moveCursor = -1;
	std::vector<std::string> lsHis;
	History h;

	Gotoxy(x, y);
	key = _getch();
	while (key != 13) {
		if (key == 27)
			return false;
		if (key == 8 && len > 0)
		{
			moveCursor = -1;
			--len;
			resultStr.pop_back();
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << "\b \b";
			lsHis=DisplayHistory(h.GetHistory(resultStr));
		}
		else if (key != 0 && key != 224 && key != 8)
		{
			moveCursor = -1;
			resultStr += (char)key;
			if (len > 110)
				OutOfRange(resultStr);
			else
				std::cout << (char)key;
			++len;
			if (resultStr != " ")
				lsHis=DisplayHistory(h.GetHistory(resultStr));
		}
		else if (key == 0 || key == 224)
		{
			int ex = _getch();
			int noHistory = (int)lsHis.size();
			if (noHistory > 0) {
				Color(8);
				if (ex == 72 && moveCursor > -1) {
					Gotoxy(x, y + moveCursor + 2);
					std::cout << lsHis[moveCursor--];
					Color(6);
					if (moveCursor != -1) {
						Gotoxy(x, y + moveCursor + 2);
						std::cout << lsHis[moveCursor];
					}
				}
				else if (ex == 80 && moveCursor<noHistory-1) {
					if (moveCursor != -1) {
						Gotoxy(x, y + moveCursor + 2);
						std::cout << lsHis[moveCursor];
					}
					Color(6);
					Gotoxy(x, y + ++moveCursor + 2);
					std::cout << lsHis[moveCursor];
				}
				Color(15);
			}
		}
		if (len < 111)
			Gotoxy(x + len, y);
		else
			Gotoxy(x + 111, y);
		key = _getch();
	}
	if (moveCursor != -1) {
		resultStr = lsHis[moveCursor];
		Gotoxy(x, y);
		std::cout << resultStr;
		for (int j = (int)resultStr.length(); j < 113; ++j)
			std::cout << " ";
	}
	h.Add(resultStr);

	return true;
}

void Search::GetFileNameByInt(const std::vector<int>& toGet, std::vector<std::string>& fileName)
{
	fileName.clear();
	for (auto i : toGet)
	{
		std::string file = theFullListOfFile[i];
		fileName.push_back(file);
	}
}

void Search::Debug(std::vector<int> &v)
{
	for (auto i : v) {
		std::cout << theFullListOfFile[i] << std::endl;
	}
	return;
}

std::vector<int> Search::Ranking(std::vector<int>& finalList, std::vector<std::string>& subQuery)
{
	std::set<int> fileList;
	AddToSet(finalList, fileList);

	std::vector<int> result;
	std::map<int, int> rank;

	for (auto& query : subQuery)
	{
		std::vector<std::string> words = splitSentence(query);
		for (auto& word : words)
			Tolower(word);
		words = RemoveStopWord(words);

		for (auto word : words)
		{
			if (!isNumberWithChar(word))
			{
				result = trie.GetKey(word);
				for (auto& fileIndex : result)
					if (fileList.count(fileIndex) != 0)
						++rank[fileIndex];
			}
			else
			{
				double num = stod(word);
				result.clear();
				bool haveNum = SearchNumber(num, result);
				if (haveNum)
				{
					for (auto& fileIndex : result)
						if (fileList.count(fileIndex) != 0)
							++rank[fileIndex];
				}
			}
		}
	}

	std::vector<std::pair<int, int> > score;
	for (auto& fileAndScore : rank)
	{
		int fileIndex = fileAndScore.first;
		int numberOfOccurence = fileAndScore.second;
		score.push_back(std::make_pair(numberOfOccurence, fileIndex));
	}
	std::sort(score.begin(), score.end(), std::greater<std::pair<int, int> >());

	result.clear();
	for (auto i : score)
		result.push_back(i.second);

	return result;
}

//Extract command and split into smaller queries
std::string Search::InfixToPostfix(const std::string & query)
{

	std::string output;
	output.clear();
	std::string newquery = PreProcess(query);

	std::stringstream ss(newquery);
	std::string token, subquery;
	std::stack<std::string> st;

	while (ss >> token) {
		if (token == "AND" || token == "OR") {
			if (subquery.size()) {
				subquery.pop_back();
				subquery += ",";
			}
			output += subquery;
			subquery.clear();
			while (st.size() && st.top() != "(") {
				output += st.top() + ",";
				st.pop();
			}
			st.push(token);
		}
		else if (IsOpenBracket(token)) {
			st.push("(");
			token.erase(token.begin());
			if (token.size()) {
				token += " ";
			}
			subquery += token;
		}
		else if (IsCloseBracket(token)) {
			token.erase(token.end() - 1);
			subquery += token;
			if (subquery.size()) {
				subquery.pop_back();
				output += subquery + ",";
			}
			subquery.clear();
			while (st.size() && st.top() != "(") {
				output += st.top() + ",";
				st.pop();
			}
			st.pop();//pop the string "("
		}
		else if (IsExactQuery(token)) {//If it is exact query get everything between "" and add it to subquery 
			do {
				subquery += token + " ";
			} while (ss >> token && !IsExactQuery(token));
			if (token[0] == '\"') {
				subquery.pop_back();
			}
			else 
				subquery += token;
			output += subquery + ",";
			subquery.clear();
		}
		else {
			subquery += token + " ";
		}
	}

	if (subquery.size()) {
		subquery.pop_back();
		output += subquery + ",";
	}

	while (st.size()) {
		output += st.top() + ",";
		st.pop();
	}
	return output;
}

std::string Search::PreProcess(const std::string & query)
{
	std::string output(query);
	int bracket = 0, quote = 0;
	//open bracket +1, close bracket -1
	//open quote +1, close quote 0;
	for (int i = 0; i < (int)output.size(); i++) {
		if (output[i] == '(') {
			++bracket;
			output.insert(output.begin() + i + 1, ' ');
		}
		else if (output[i] == ')') {
			--bracket;
			output.insert(output.begin() + i, ' ');
			++i;
		}
		else if (output[i] == '\"') {
			quote = 1 - quote;
		}
	}
	for (int i = 0; i < bracket; i++) {
		output += " )";
	}
	return output;
}

bool Search::IsExactQuery(const std::string & query)
{
	if (query[0] == '\"' || query[query.size() - 1] == '\"')
		return true;
	return false;
}

bool Search::IsOpenBracket(const std::string & query)
{
	if (query[0] == '(')
		return true;
	return false;
}

bool Search::IsCloseBracket(const std::string & query)
{
	if (query[query.size() - 1] == ')')
		return true;
	return false;
}

bool Search::IsIntitleQuery(const std::string & query)
{
	std::string cmp(query, 0, 8);
	return !cmp.compare("Intitle:");
}

bool Search::IsPlaceHolderQuery(const std::string & query)
{
	return (query.find(" * ") != query.npos);
}

bool Search::IsPlusQuery(const std::string & query)
{
	return query.find(" +") != query.npos;
}

bool Search::IsMinusQuery(const std::string & query)
{
	int i = (int)query.find(" -");
	return (i != query.npos && i+1 < (int)query.size() && query[i + 1] != ' ');
}

bool Search::IsRangeQuery(const std::string & query)
{
	return (query.find("..") != query.npos);
}

std::vector<int> Search::SearchExact(const std::string &phrase) {
	std::vector<std::string> words = splitSentence(phrase);
	std::vector<int> res;
	res.clear();

	if (words.empty()) return res;

	for (auto& word : words) 
		Tolower(word);
	words = RemoveStopWord(words);
	std::map<int, int> mp;

	for (auto word : words) 
	{
		if (!isNumberWithChar(word))
		{
			res = trie.GetKey(word);
			AddToMap(res, mp);
		}
		else
		{
			double num = stod(word);
			res.clear();
			bool haveNum = SearchNumber(num, res);
			if (haveNum) AddToMap(res, mp);
		}
	}

	res.clear();
	int sz = (int)words.size();
	for (auto i : mp) if (i.second == sz)
	{
		if (HaveExactString(i.first, phrase)) // check if this file has exact string
			res.push_back(i.first);
	}

	return res;
}

std::vector<int> Search::SearchNormal(const std::string & phrase)
{
	std::vector<std::string> words = splitSentence(phrase);
	std::vector<int> res;
	res.clear();

	if (words.empty()) return res;

	for (auto& word : words)
		Tolower(word);
	words = RemoveStopWord(words);

	std::map<int, int> mp;

	for (auto word : words)
	{
		if (!isNumberWithCharExtended(word))
		{
			//Search synonym
			if (word[0] == '~') {
				word.erase(word.begin());
				res = SearchSynonym(word);
				AddToMap(res, mp);
			}
			else {
				//normal search
				res = trie.GetKey(word);
				AddToMap(res, mp);
			}
		}
		else
		{
			if (IsRangeQuery(word)) {
				double l, r;
				PreProcessRangeQuery(word, l, r);
				SearchRange(l, r, res);
				AddToMap(res, mp);
			}
			else{
				while (!isdigit(word[0]))
					word.erase(word.begin());
				while (!isdigit(word[word.size() - 1]))
					word.pop_back();
				double number = stod(word);
				SearchNumber(number, res);
			}
		}
	}
	res.clear();
	for (auto i : mp) 
		res.push_back(i.first);

	return res;

}

bool Search::HaveExactString(const int& pos, const std::string& phrase)
{
	Document doc;
	doc.SetFileName(theFullListOfFile[pos]);
	doc.ReadFile();
	if (doc.SearchForPhraseInContent(phrase) != -1 || doc.SearchForPhraseInTitle(phrase) != -1) return true;
	return false;
}

bool Search::SearchNumber(const double & key,std::vector<int>& result)
{
	numIndex.GetNumKey(result, key);
	if (result.empty())
		return false;
	return true;
	
}

bool Search::SearchRange(const double & key1, const double & key2,std::vector<int>& result)
{
	numIndex.GetRange(result, key1, key2);
	if (result.empty())
		return false;
	return true;
}

void Search::PreProcessRangeQuery(const std::string query, double & lo, double & hi)
{
	int i = (int)query.find("..");
	std::string left(query, 0, i);
	while (!isdigit(left[0]))
		left.erase(0, 1);
	while (!isdigit(left[left.size() - 1]))
		left.erase(left.end()-1);
	lo = std::stod(left);

	std::string right(query, i+2, (int)query.size()-1);
	while (!isdigit(right[0]))
		right.erase(0, 1);
	while (!isdigit(right[right.size() - 1]))
		right.erase(right.end()-1);
	hi = std::stod(right);
	return;
}


std::vector<int> Search::SearchSynonym(const std::string &phrase) {
	std::vector<std::string> syn = synonym[phrase];
	std::vector<int> res;
	std::set<int> st;
	for (auto i : syn) {
		res = trie.GetKey(i);
		for (auto j : res)
			st.insert(j);
	}
	res.clear();
	for (auto i : st)
		res.push_back(i);
	return res;
}

std::vector<int> Search::SearchPlus(const std::string & phrase)
{
	int i = phrase.find("+");
	std::string left(phrase, 0, i);
	std::string tmp(phrase.begin() + i + 1, phrase.end());
	left += tmp;
	std::vector <int> res = SearchExact(left);
	return res;
}

std::vector<int> Search::SearchMinus(const std::string & phrase)
{
	int i = phrase.find("-");
	std::string left(phrase, 0, i);
	left.pop_back();
	std::vector<int> res = SearchExact(left);
	std::string tmp(phrase.begin() + i + 1, phrase.end());
	left += " " + tmp;
	std::vector<int> complement = SearchExact(left);
	NOT(res, complement);
	return res;
}

int Search::SwitchQuery(const std::string & subquery) {
	if (IsExactQuery(subquery))
		return 1;
	if (IsIntitleQuery(subquery))
		return 2;
	if (IsPlaceHolderQuery(subquery))
		return 3;
	if (IsPlusQuery(subquery))
		return 4;
	if (IsMinusQuery(subquery))
		return 5;
	return 0;
}

std::vector <int> Search::Process(const std::string &query) {
	//This function implement stack by using a vector
	//st is a stack of vector <int> 
	std::vector <std::vector <int>> st;
	st.clear();
	std::stringstream ss(query);
	std::string subquery;
	while (getline(ss, subquery, ',')) {
		if (subquery != "AND" && subquery != "OR") {
			int u = SwitchQuery(subquery);
			std::vector <int> res;
			switch (u) {
			case 1://Exact query 
				//Process Exact query here
				subquery.pop_back();
				subquery.erase(0,1);
				res = SearchExact(subquery);
				break;
			case 2://Intitle query
				//Process Intitle query here
				break;
			case 3://Placeholder query
				//Process placeholder here
				break;
			case 4://Plus query
				//Process plus query
				res = SearchPlus(subquery);
				break;
			case 5://Minus query
				//Process minus query
				res = SearchMinus(subquery);
				break;
			default:
				res = SearchNormal(subquery);
				break;
			}
			st.push_back(res);
		}
		else {
			std::vector <int> v1 = st.back();
			st.pop_back();
			std::vector <int> v2 = st.back();
			st.pop_back();
			if (subquery == "AND")
				AND(v1, v2);
			else if (subquery == "OR")
				OR(v1, v2);
			st.push_back(v1);
		}
	}
	return st.back();
}
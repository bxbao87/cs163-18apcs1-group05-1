#pragma once
#ifndef Support_h
#define Support_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <filesystem>
#include <queue>


bool isDelimiter(const char &c);//Check if char c is a delimiter . , ! ? ' " 

std::vector<std::string> AND(std::vector<std::string> &v1, std::vector<std::string> &v2);//AND operation
std::vector<std::string> OR(const std::vector<std::string>& v1, const std::vector<std::string>& v2);// OR operator

std::vector<std::string> splitSentence(const std::string& s);
bool loadStopWord(std::set<std::string>& stopword);
void Tolower(std::string& s); // Change a string to lower case
std::vector<std::string> RemoveStopWord(const std::vector<std::string>& words);

bool isPrefix(const std::string &check, const std::string &query);// check if query is prefix of check

#endif
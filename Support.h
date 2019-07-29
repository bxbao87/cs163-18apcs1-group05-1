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
#include <stack>


bool isNumber(const char& c);// check if a string is a number (1,2,..) or not
bool isNumberWithChar(std::string&s);// check if string is number with $ and remove $ 
bool isMixType(const std::string& s);// check if a string is mix number with char (Ex: 123abc)
bool isNumberWithCharExtended(const std::string &s);// check if a string have number $ and %

void AND(std::vector<int> &v1, const std::vector<int> &v2);//AND operation after AND, the result will be in v1
void OR(std::vector<int>& v1, const std::vector<int>& v2);// OR operator
void OR(std::vector<std::string>& v1, const std::vector<std::string>& v2);//Same OR operator but for different data type
void NOT(std::vector<int> &res, const std::vector <int> & complement);
std::vector<std::string> splitSentence(const std::string& s);
void Tolower(std::string& s); // Change a string to lower case
std::string TolowerExtend(std::string& s);
bool IsStringWiths(const std::string& s);// check if s2 is s1 with 's 

bool isSub(const std::string &check, const std::string &query);// check if query is substring of check

void AddToSet(const std::vector<int>& a, std::set<int>& s); // Add elements of vector a into set s
void AddToMap(const std::vector<int>& v, std::map<int, int> &mp);

int IsWhichKind(const std::string& var); // ony accept string after trim, return 0 if it is weird, 1 if is number and 2 otherwise
int ConvertCharToNum(const char& c);
char ConvertNumToChar(const int& x);

bool IsNothing(const std::string &str);
std::string ReplaceStr(std::string &str, char delimiter);

#endif
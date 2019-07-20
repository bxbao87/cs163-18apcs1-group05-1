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

void AND(std::vector<int> &v1, std::vector<int> &v2, std::vector<int>& intersection);//AND operation
void OR(const std::vector<int>& v1, const std::vector<int>& v2,std::vector<int>& res);// OR operator

std::vector<std::string> splitSentence(const std::string& s);
void Tolower(std::string& s); // Change a string to lower case

bool isSub(const std::string &check, const std::string &query);// check if query is substring of check

int IsWhichKind(const std::string& var); // ony accept string after trim, return 0 if it is weird, 1 if is number and 2 otherwise
int ConvertCharToNum(const char& c);
char ConvertNumToChar(const int& x);

#endif
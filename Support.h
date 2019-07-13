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

bool isDelimiter(const char &c);//Check if char c is a delimiter . , ! ? ' " 


std::vector<std::string> AND(std::vector<std::string> &v1, std::vector<std::string> &v2);//AND operation

#endif
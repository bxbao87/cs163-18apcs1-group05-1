#pragma once
#ifndef __HISTORY_H__
#define __HISTORY_H__
#include "Support.h"
class History
{
public :
	History();
	~History();
	void LoadHistory();//read history from file
	void WriteHistory();//write history to file 
	void Add(const std::string & query);//add query to the history queue
	std::vector<std::string> GetHistory(const std::string &searchKeyword);//get searchKeyword and return history 
private:
	std::queue <std::string> history;
};
#endif
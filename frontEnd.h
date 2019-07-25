#ifndef FRONTEND_H
#define FRONTEND_H

#include"Support.h"

void FrontEnd();

void Gotoxy(int x, int y);
void Color(int x);
void SetWindow(int Width, int Height);
void S(int x, int y, int colour);
void E(int x, int y, int colour);
void A(int x, int y, int colour);
void R(int x, int y, int colour);
void C(int x, int y, int colour);
void H(int x, int y, int colour);
void B(int x, int y, int colour);
void O(int x, int y, int colour);
void G(int x, int y, int colour);
void Center(std::string a, int s, int y, int colour);
void BogosearchSplash();
void SearchScreen();

void OutOfRange(std::string a);
std::vector<std::string> DisplayHistory(const std::vector<std::string> &v);
int ChooseLink(int n);

#endif
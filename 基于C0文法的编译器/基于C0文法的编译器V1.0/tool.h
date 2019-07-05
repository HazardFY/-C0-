#pragma once
#ifndef TOOL_H
#define TOOL_H
#include <sstream>
#include <string>
#include<iostream>
//using namespace std;
using std::stringstream;//不添加的话stringstream未定义
using std::string;
using std::ios;

int strToInt(string str);
char strToChar(string str);
string intToString(int num);
string charToString(char c);



#endif //TOOL_H
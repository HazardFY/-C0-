#pragma once
#ifndef C0_COMPILER_MAIN_H
#define C0_COMPILER_MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctype.h>
#include <iomanip>//格式化输出

//using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ios;
using std::fstream;
using std::map;

// Restricts
const int maxIdentLength = 100;
const int maxLineLength = 100;
const int keywordCount = 14;
const int maxDigit = 15;
const int maxInt = 100000000;

//type
typedef char alpha[maxIdentLength + 1]; // Alphabet letter should be restricted to maxIdentLength
typedef enum {
	identi, // 0
	constsy, // 1
	intsy, charsy, // 2, 3
	voidsy, // 4
	intcon, charcon, stringcon, // 5, 6, 7
	plus, minus, times, idiv, // 8, 9, 10, 11
	eql, neq, gtr, geq, lss, leq, // 12, 13, 14, 15, 16, 17
	becomes, // 18
	lparent, rparent, lbrack, rbrack, lbrace, rbrace, // 19, 20, 21, 22, 23, 24
	comma, semicolon, colon, // 25, 26, 27
	ifsy, elsesy, // 28, 29
	switchsy, casesy, defaultsy, // 30, 31, 32
	forsy, // 33
	scanfsy, printfsy, // 34, 35
	mainsy, // 36
	returnsy // 37
} symbol; // All C0 reserved words
typedef enum {
	consts,
	vars,
	params,
	funcs
} kind; // All C0 kinds
typedef enum {
	ints, chars, voids
} type; // All C0 types

		// Static elements
extern alpha keywords[];
extern symbol keySymbols[];
extern map<char, symbol> specialSymbols;

// Global Variables changing all the way
extern char line[]; // One source code line
extern char ch; // Currently reading character
extern alpha token;
extern symbol sy;
extern int inum;
extern char str[];
extern int level;
extern fstream inputFile;
extern fstream infixFile;


// Lexical actions
void nextch(); // Store one source code line into line[] and store one char into ch
void insymbol(); // Read one symbol, sy stores symbol type, inum stores contents

				 //symbol functions
void setup();
#endif //C0_COMPILER_MAIN_H

#include "main.h"
#define specials '+', '-', '*', '/', '(', ')', '[', ']', '{', '}', ',', ';', ':'
//symbolNames����Ӣ�ģ�symbolΪһ�ֱ������ֱ�ʾ���������ͣ����ţ�������
fstream infixFile, inputFile;
char* symbolNames[] = {
	"Ident",
	"Const",
	"Int", "Char",
	"Void",
	"IntCon", "CharCon", "StringCon",
	"Plus", "Minus", "Times", "Div",
	"Eql", "Neq", "Gtr", "Geq", "Lss", "Leq",
	"And","Or",
	"Becomes",
	"Lparent", "Rparent", "Lbrack", "Rbrack", "Lbrace", "Rbrace",
	"Comma", "Semicolon", "Colon",
	"If", "Else",
	"Switch", "Case", "Default",
	"For","While",
	"Scanf", "Printf",
	"Main",
	"Return"
};

void setup() {
	// File initialization
	
	inputFile.open("input.txt", ios::in);
	if (inputFile.is_open() == false)cout << "���ı�ʧ��" << endl;
	else cout << "���ı��ɹ�" << endl;
	// Table initialization
	idTable.reserve(10000);
	staticTable.reserve(10000);
	infixTable.reserve(10000);

	// Keyword strings �ؼ��ʣ��������ͺͲ�����
	char* keywordList[] = {
		"const",
		"int",
		"char",
		"void",
		"if",
		"else",
		"switch",
		"case",
		"default",
		"for",
		"scanf",
		"printf",
		"main",
		"return",
		"while"
	};
	for (int i = 0; i < keywordCount; i++) {
		strcpy_s(keywords[i], keywordList[i]);//�Ѻ�����ǰ������ǰ
	}

	// Keyword symbols
	symbol keySymbolList[] = {//���ͺͲ��������ֱ�ʾ
		constsy, intsy, charsy, voidsy, ifsy, elsesy, switchsy, casesy, defaultsy, forsy,
		scanfsy, printfsy, mainsy, returnsy, whilesy
	};
	for (int i = 0; i < keywordCount; i++) {
		keySymbols[i] = keySymbolList[i];
	}

	// Special symbols
	char specialSymbolsChar[] = {//���ŵ��ַ���ʽ
		specials
	};
	symbol specialSymbolList[] = {//���ŵ�������ʽ
		plus, minus, times, idiv, lparent, rparent, lbrack, rbrack, lbrace, rbrace,
		comma, semicolon, colon
	};//'+', '-', '*', '/', '(', ')', '[', ']', '{', '}', ',', ';', ':'
	//define the map specialSymbols
	for (int i = 0; i < sizeof(specialSymbolList) / sizeof(specialSymbolList[0]); i++) {
		specialSymbols[specialSymbolsChar[i]] = specialSymbolList[i];
	}
}


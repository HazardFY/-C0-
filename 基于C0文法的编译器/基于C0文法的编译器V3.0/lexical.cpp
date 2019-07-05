//
// Created by Andy on 2017/11/19.
//
#include "main.h"

#define isLetter(a) (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a =='_')
#define isMyAscii(a) (a == 32 || a == 33 || a >= 35 && a <= 126)

const int maxStrLength = 1000;

char ch = ' ';
alpha token;
symbol sy;
int inum;
char str[maxStrLength + 1]; // +1 for \0

char line[maxLineLength + 1]; // +1 for \0
alpha keywords[keywordCount];	//.c�ļ��е������趨��extern���ͣ� Ȼ����ͷ�ļ���������һ����int��ͷ�ļ��ж��� 
symbol keySymbols[keywordCount];
map<char, symbol> specialSymbols;
//fstream inputFile, infixFile;

int lineLength = 0;//һ���ַ����� ����/n�ַ����� ������/0

int charPtr = 0;//�ַ���  ��ǰ�ַ�����һ���ַ����
int linePtr = 0;//�к�   ��1��ʼ



int isspace(char ch)
{
	if (ch == '\0' || ch == ' ' || ch == '\t' || ch == '\n') return 1;
	else return 0;
}
// Store one source code line into line[](if possible) and store the  char into ch
//use infixFile.get()�����ϻ�ȡ��һ�е��ַ� 
void nextch() {
	if (charPtr == lineLength ) {//�������У�ѡ����һ�У������ȡ��һ��char
		if (inputFile.eof()) {//End Of File ����д����ʾ���ļ����������ز���ֵ,��δ������βʱ������ֵΪ0��������βʱ������ֵΪ1
			cout << endl;
			cout << "Compiling finished." << endl;
			//exit(0);
		}
		
		lineLength = 0;
		charPtr = 0;
		linePtr++; // New line entered
				   //get the next line to line[]
		char tempChar;
		//cout << inputFile.peek() << endl;
		while (inputFile.peek() != '\n' && inputFile.peek() != EOF) { // ��������һ���ַ��ĳ���Խ���ж�  peek() ֻ��"��"����һ���ַ���û��������ȡ��
			tempChar = inputFile.get();//�����һ���ַ�
            //cout << tempChar << endl;
			line[lineLength] = tempChar;
			lineLength++;
		}
		line[lineLength] = inputFile.get(); // Get '\n' or EOF
		lineLength++;
		line[lineLength] = '\0';
		//        cout << endl;
	}
	ch = line[charPtr];
	charPtr++;
}

// Clear str's contents to \0
void clearStr() {
	for (int i = 0; i <= maxStrLength; ++i) {
		str[i] = '\0';
	}
}

// Clear token's contents to \0
void clearToken() {
	for (int i = 0; i <= maxIdentLength; ++i) {
		token[i] = '\0';
	}
}

// Set up reserved words��ȡ�����������ֵ�token[] 
void insymbol() {
	/*
	//test file si open or not
	char tempChar;
	char line[100];
	int lineLength = 0;
	if (inputFile.is_open() == false)cout << "��ʧ��" << endl;
	while (inputFile.peek() != '\n' && inputFile.peek() != EOF) { // ��������һ���ַ��ĳ���Խ���ж�  peek() ֻ��"��"����һ���ַ���û��������ȡ��
		tempChar = inputFile.get();//�����һ���ַ�
		cout << tempChar << endl;
		line[lineLength] = tempChar;
		lineLength++;
	}
	line[lineLength] = inputFile.get(); // Get '\n' or EOF
	lineLength++;
	line[lineLength] = '\0';
	cout << line << endl;
	*/
	int k = 0;
	//nextch();
	while (isspace(ch))
	{
		//cout << "dec:" << int(ch) << endl;
		nextch();//������c�Ƿ�Ϊ�ո��ַ���Ҳ�����ж��Ƿ�Ϊ�ո�(' ')��ˮƽ��λ�ַ�
								 //('\t')����λ��('\r')������('\n')����ֱ��λ�ַ�('\v')��ҳ('\f')�������
	}
	if (isLetter(ch))
	
	{ // Identifier or keyword
		// Initiate token
		clearToken();

		// Read whole alpha into token, token can't be longer than 10 characters
		do {
			if (k < maxIdentLength) {
				token[k] = ch;
				k++;
			}
			nextch();
		} while (isLetter(ch) || isdigit(ch));

		for (k = 0; k < keywordCount; k++) {
			if (strcmp(token, keywords[k]) == 0) {//�ж��ַ��Ƿ���14��������ţ���ͬ����0
				break;
			}
		}
		if (k < keywordCount) sy = keySymbols[k];//sy���������,symbol�ַ���ʽ���������
		else sy = identi;
	}
	else if (isdigit(ch)) { // IntegerΪ��������
		if (ch == '0') { // Int start with 0 (must be 0)
			inum = 0;//��ֵ��С
			sy = intcon;
			nextch();
			if (isdigit(ch)) { // Error & read till the last number
							   //error(LeadingZero);
				nextch();
				while (isdigit(ch)) {
					nextch();
				}
			}
		}
		else { // Int start with no 0
			inum = 0;
			sy = intcon;
			for (; isdigit(ch); k++) {
				inum = inum * 10 + ch - '0';
				nextch();
			}
		}
		if (k > maxDigit || inum > maxInt) {//�ַ��������Ȼ������ֹ��󣬴�����
											//error(NumRangeExceed);
			inum = 0;
			k = 0;
		}
	}
	//���ַ����������ת��Ϊ�����sy
	else if (ch == '<') { // Leq or lss
		nextch();
		if (ch == '=') {
			k++;
			sy = leq;
			nextch();
		}
		else {
			sy = lss;
		}
	}
	else if (ch == '>') { // Beq or bgt
		nextch();
		if (ch == '=') {
			k++;
			sy = geq;
			nextch();
		}
		else {
			sy = gtr;
		}
	}
	else if (ch == '=') { // Equal or becomes
		nextch();
		if (ch == '=') {
			k++;
			sy = eql;
			nextch();
		}
		else {
			sy = becomes;
		}
	}
	else if (ch == '!') { // Not equal
		nextch();
		if (ch == '=') {
			sy = neq;
			nextch();
		}
		else {
			// error(ExclamationMark);
			sy = neq;
		}
	}
	else if (ch == '\'') { // Character
		nextch();
		if (ch == '\'') {
			 error(EmptyChar); // Empty char
			sy = charcon;
			inum = 0;
		}
		else { // One or more characters in quotation marks
			if (ch != '+' && ch != '-' && ch != '*' && ch != '/'
				&& !isdigit(ch) && !isLetter(ch)) {
				error(IllegalChar); // Illigal character
				sy = charcon;
				inum = 0;
			}
			else { // Probable character
				inum = ch; // Store ch for probable output use int to store char
				nextch();
				if (ch != '\'') { // Characters more than one
					errorFlag = true;
					error(QuotMarkLost);
					sy = charcon;
					inum = 0;
					while (ch != '\'' && ch != '\n') nextch(); // End till '\n' or '
					return;
				}
				else { // Correct character
					sy = charcon; // inum is already set before
				}
			}
		}
		nextch();
	}
	else if (ch == '"') { // String
		clearStr();
		nextch();
		if (ch == '"') { // Empty string
			sy = stringcon;
			inum = 0;
		}
		else { // String inside
			k = 0;
			do {//ѭ����ȡ��֪������"���߳���,�ַ���������str��
				if (!isMyAscii(ch)) { // Illegal my ascii
									  // error(IllegalStr);
					sy = stringcon;
					inum = 0;
					while (ch != '"' && isspace(ch)) nextch(); // End till space or "
					return;
				}
				if (k == maxStrLength) { // String too long
										 //error(StrRangeExceed);
					sy = stringcon;
					inum = 0;
					while (ch != '"' && isspace(ch)) nextch(); // End till space or "
					return;
				}
				str[k] = ch;
				k++;
				if (ch == '\\') { // Keep string output same as origin
					str[k] = '\\';
					k++;
				}
				nextch();
			} while (ch != '"');
			sy = stringcon;
			inum = 0;
		}
		nextch();
	}
	//������Ż�ı�syֵΪ��Ӧ��ֵ����
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' ||
		ch == '}' || ch == ',' || ch == ';' || ch == ':') { // Symbols with single letter
		sy = specialSymbols[ch];//����symbol�жϷ�������
		nextch();
	}
	else if (ch == EOF) {
		// printTable();
		// outputInfixes();
		/* if (errorFlag) {
		cout << "Compiling failed" << endl;
		exit(0);
		} else {
		cout << "Compiling succeeded." << endl;
		}*/
		return;
	}
	else {
		error(UnknownWord); // Illegal character head
		nextch();
		insymbol();
	}
}
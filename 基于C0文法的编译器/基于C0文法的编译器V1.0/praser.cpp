/*
＜程序＞ ::= ［＜常量说明＞]［＜变量说明＞]{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞     函数部分省略处理
＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
＜常量定义＞ ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}| char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞} 
＜主函数＞ ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
＜复合语句＞ ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
＜语句列＞ ::=｛＜语句＞｝
<语句> ::= ＜条件语句＞｜＜循环语句＞| ‘{’＜语句列＞‘}’|＜赋值语句＞;
	（｜＜有返回值函数调用语句＞;| ＜无返回值函数调用语句＞;）｜（｜＜读语句＞;｜＜写语句＞;|＜情况语句＞｜＜返回语句＞;）｜＜空＞;
＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
＜条件语句＞ ::= if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
＜循环语句＞ ::= for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
＜表达式＞ ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
＜因子＞ ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’
＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
*/
#include "main.h"

#define isCompare(a) (a == eql || a == neq || a == gtr || a == geq || a == lss || a == leq)//lss < leq<=
int level = 0;
int paramCount = 0;
int labelIndex = 0;
const string labelStr = "LABEL";
//get the next integer and update sy and infixstring = (str)inum
//读下一个数，结合前面的‘-’号得出负数值
void integer(string &infixString) {
	symbol tempSy;

	if (sy == plus || sy == minus) {
		tempSy = sy;
		insymbol();//进行新的取词判断
		if (sy == intcon) {//整型数字
			if (inum != 0) {
				if (tempSy == minus) { // Get the negative number
					inum = inum * (-1);
				}
				infixString = intToString(inum);//int to string
				insymbol();
			}
			else {
				error(SignedZero); // Sign before zero
			}
		}
		else {
			error(NumErr); // Number error
		}
	}
	else if (sy == intcon) {//读数为整型数字
		infixString = intToString(inum);
		insymbol();
	}
	else {
		error(NumErr); // Number error
	}
}


// ＜程序＞ ::= ［＜常量说明＞]［＜变量说明＞]{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
void program() {
	insymbol();
	//<常量说明>
	if (sy == constsy) { // Constant statements
		constState();
	}
	//<变量说明>
	if (sy == intsy || sy == charsy) { // Variable statements or definition of function with return
		int tempCharPtr = charPtr; // Store current charPtr for later recovering
		char tempCh = ch;
		symbol tempSy = sy;
		insymbol();
		if (sy == identi) {//非关键字而是变量名
			insymbol();
		}
		else {
			error(NotVarFunc); // Not a variable or function
			charPtr = tempCharPtr; // Recover charPtr
			ch = tempCh;
			sy = tempSy;
			// Go to function definition
		}
		/*
		if (sy == lparent) { // funcWithRetDef有返回值的函数 lparent = (
			charPtr = tempCharPtr; // Recover charPtr
			ch = tempCh;
			sy = tempSy;
			// Go to function definition
		}
		//全局变量，数组，变量
		else if (sy == lbrack ||              //lbrack = [
			sy == comma || sy == semicolon) { // Variables statements ，；
			charPtr = tempCharPtr; // Recover charPtr
			ch = tempCh;
			sy = tempSy;
			globalVarState();
		}
		else {
			error(NotVarFunc); // Not a variable or function
			charPtr = tempCharPtr; // Recover charPtr
			ch = tempCh;
			sy = tempSy;
			// Go to function definition
		}*/
	}

	// Function statements
	/* while (sy == intsy || sy == charsy || sy == voidsy) {
		if (sy ==voidsy) { // Functions without returns
			funcWithoutRetDef();
		}
		else { // Functions with returns or main
			int tempCharPtr = charPtr;
			char tempCh = ch;
			symbol tempSy = sy;
			insymbol();
			if (sy == identi && sy != mainsy) { // General functions
				charPtr = tempCharPtr;
				ch = tempCh;
				sy = tempSy;
				funcWithRetDef();
			}
			else if (sy == mainsy) { // Main
				charPtr = tempCharPtr;
				ch = tempCh;
				sy = tempSy;
				break;
			}
			else {
				error(IdLost);
				charPtr = tempCharPtr;
				ch = tempCh;
				sy = tempSy;
				funcWithRetDef();
			}
		}
	}*/

	// Main
	if (sy == intsy) {
		mainDef();
	}
	else {
		error(IllegalSyntax); // Illegal syntax in program
							  // Skip to the end of program
		while (true) {
			insymbol();
		}
	}
}

// ＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
void constState() {
	while (sy == constsy) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
		constDef();
		if (sy == semicolon) {  //;
			if (skipFlag) {
				skipFlag = false;
			}
			insymbol();
		}
		else if (!skipFlag) {
			error(SemicolonLost); // Semicolon lost
		}
	}
	cout << "This is a const declaration statement." << endl;
}

/* ＜常量定义＞ ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
| char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞} */
void constDef() {
	char idName[100];
	string infixString = "";

	if (sy == intsy) { // Int const
		do {
			if (skipFlag) {
				skipFlag = false;
			}
			insymbol();
			if (sy == identi) {
				strcpy_s(idName, token);//token中的变量名复制进临时变量idName中
				insymbol();
			}
			else {
				error(IdLost); // Identifier lost
				symbol nexts[] = { comma, semicolon, rbrace };//逗号，分号，右中括号
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}

			if (sy == becomes) {   //赋值 int a = 
				insymbol();
			}
			else if (!skipFlag) {
				error(AssignSyLost); // Assignment symbol lost
				symbol nexts[] = { comma, semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
			if (!skipFlag) {          //如果不跳句子的话读int数字
				integer(infixString); // Manage integer
			}
			
			if (isDefinable(idName)) {
				insertTable(consts, ints, idName, 0, level, strToInt(infixString));
				insertInfix("CONST", infixString, "int", idName);
			}
			else {
				error(IdRepeat); // Identifier repeatedly define
			}
		} while (sy == comma);//comma逗号
	}
	else if (sy == charsy) { // Char const
		do {
			//开头先中止跳跃（如果有的话）
			if (skipFlag) {
				skipFlag = false;
			}
			//id
			insymbol();
			if (sy == identi) {
				strcpy_s(idName, token);
				insymbol();
			}
			else {
				error(IdLost); // Identifier lost
				symbol nexts[] = { comma, semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
			//=
			if (sy == becomes) {
				insymbol();
			}
			else if (!skipFlag) {
				error(AssignSyLost); // Assignment symbol lost
				symbol nexts[] = { comma, semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
			//charcon
			if (sy == charcon) {
				if (isDefinable(idName)) {
					insertTable(consts, chars, idName, 0, level, inum);
					insertInfix("CONST", charToString(inum), "char", idName);
				}
				else {
					error(IdRepeat); // Identifier repeatedly define
				}
				insymbol();
			}
			else if (!skipFlag) {
				error(CharConErr); // Char const error
				symbol nexts[] = { comma, semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
		} while (sy == comma);
	}
	else if (!skipFlag) {
		error(ConDefTypeErr); // Const definition type error
		symbol nexts[] = { comma, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
}

// ＜主函数＞ ::= int main‘(’‘)’ ‘{’＜复合语句＞‘}’
void mainDef() {
	level++;
	if (sy == intsy) { // Manage definition head
		insymbol();
	}
	else if (!skipFlag) {
		error(IllegalType); // wrong type
		symbol nexts[] = { lparent, rparent, lbrace, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	if (sy == mainsy) {
		if (isDefinable(token)) {
			insertTable(funcs, voids, token, 0, level - 1, 0); // paramCount = 0
		}
		else {
			error(IdRepeat); // Identifier repeatedly define
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { lparent, rparent, lbrace, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

	if (sy == lparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(LeftParentLost); // Left parenthesis lost
		symbol nexts[] = { rparent, lbrace, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

	if (sy == rparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(RightParentLost); // Right parenthesis lost
		symbol nexts[] = { lbrace, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

	if (sy == lbrace) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(LeftBraceLost); // Left brace lost
		symbol nexts[] = { rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

	insertInfix("FUNC", " ", "int", "main");

	if (!skipFlag) {
		complexState(); // Manage complex statement
	}

	if (sy == rbrace) {
		if (skipFlag) {
			skipFlag = false;
		}
		popLocals();
		cout << "This is the main function." << endl;
		insymbol();
	}
	else {
		error(RightBraceLost); // Right brace lost
	}
	level--;
}

// ＜复合语句＞ ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
void complexState() {
	while (sy == constsy) {
		constState();
	}
	while (sy == intsy || sy == charsy) {
		varState();
	}
	stateList();
}

// ＜变量说明＞ ::= ＜变量定义＞;{＜变量定义＞;}
void varState() {
	do {
		if (skipFlag) {
			skipFlag = false;
		}
		varDef();

		if (sy == semicolon) {
			if (skipFlag) {
				skipFlag = false;
			}
			insymbol();
		}
		else if (!skipFlag) {
			error(SemicolonLost); // Semicolon lost
		}

	} while (sy == intsy || sy == charsy);
	cout << "This is a variable declaration statement." << endl;
}
// ＜变量定义＞ ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’}
//一行最多定义两个变量（没用循环）
void varDef() {
	char idName[100] = "";
	type varType = voids;

	if (sy == intsy || sy == charsy) { // Right variable(s)
		if (sy == intsy) {
			varType = ints;
		}
		else {
			varType = chars;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(IllegalType); // Illegal type
		symbol nexts[] = { comma, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

	if (sy == identi) {
		strcpy_s(idName, token);
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { comma, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//数组的左中括号
	if (sy == lbrack) { // Following are array management左中括号
		insymbol();

		if (sy == intcon && inum != 0) {
			insymbol();
			if (isDefinable(idName)) {
				insertTable(vars, varType, idName, inum, level, 0);
				char CH = inum;
				insertInfix("VAR", charToString(CH), varType == ints ? "int" : "char", idName);
			}
			else {
				error(IdRepeat); // Identifier repeatedly define
			}
		}
		else {
			error(ArrIndexErr); // Array index error
		}

		if (sy == rbrack) {
			insymbol();
		}
		else {
			error(RightBrackLost); // Right bracket lost
			symbol nexts[] = { comma, semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}
	}

	else { // General variable
		if (isDefinable(idName)) {
			insertTable(vars, varType, idName, 0, level, 0);
			insertInfix("VAR", " ", varType == ints ? "int" : "char", idName);
		}
		else {
			error(IdRepeat); // Identifier repeatedly define
		}
	}

	while (sy == comma) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();

		if (sy == identi) {
			strcpy_s(idName, token);
			insymbol();
		}
		else {
			error(IdLost); // Identifier lost
			symbol nexts[] = { comma, semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}

		if (sy == lbrack) { // Following are array management
			insymbol();
			if (sy == intcon) {
				insymbol();
				if (isDefinable(idName)) {
					insertTable(vars, varType, idName, inum, level, 0);
					insertInfix("VAR", intToString(inum), varType == ints ? "int" : "char", idName);
				}
				else {
					error(IdRepeat); // Identifier repeatedly define
				}
			}
			else {
				error(ArrIndexErr); // Array index error
				symbol nexts[] = { comma, semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
			if (sy == rbrack) {
				insymbol();
			}
			else {
				error(RightBrackLost); // Right bracket lost
			}
		}
		else { // General variable
			if (isDefinable(idName)) {
				insertTable(vars, varType, idName, 0, level, 0); // length = 0, addr automatic set
				insertInfix("VAR", " ", varType == ints ? "int" : "char", idName);
			}
			else {
				error(IdRepeat); // Identifier repeatedly define
			}
		}
	}
}

/*
<语句> :: = ＜条件语句＞｜＜循环语句＞ | ‘{ ’＜语句列＞‘ }’ | ＜赋值语句＞;
（｜＜有返回值函数调用语句＞; | ＜无返回值函数调用语句＞; ）｜（｜＜读语句＞; ｜＜写语句＞; | ＜情况语句＞｜＜返回语句＞; ）｜＜空＞;
*/
void statement() {
	string emptyString = "";

	switch (sy) {
	case ifsy:
		ifState();
		break;
	case forsy:
		loopState();
		break;
	case lbrace: {
		insymbol();
		stateList();
		if (sy == rbrace) {
			insymbol();
		}
		else {
			error(RightBraceLost); // Right brace lost
		}
		break;
	}
	case identi: {
		int tempCharPtr = charPtr;
		char tempCh = ch;
		symbol tempSy = sy;
		char tempToken[100];
		strcpy_s(tempToken, token);
		insymbol();
		if (sy == becomes || sy == lbrack) {
			charPtr = tempCharPtr;
			ch = tempCh;
			sy = tempSy;
			assignState();
		}
		/*
		else { // Call function
			charPtr = tempCharPtr;
			ch = tempCh;
			sy = tempSy;
			if (idTable[lookUp(tempToken)].typ == voids) {
				funcWithoutRetCall();
			}
			else {
				funcWithRetCall(emptyString);
			}
		}*/
		if (sy == semicolon) {
			insymbol();
		}
		else {
			error(SemicolonLost); // Semicolon lost
		}
		break;
	}
	 /*
	case scanfsy: {
		scanfState();
		if (sy == semicolon) {
			insymbol();
		}
		else {
			error(SemicolonLost); // Semicolon lost
		}
		break;
	}
	case printfsy: {
		printfState();
		if (sy == semicolon) {
			insymbol();
		}
		else {
			error(SemicolonLost); // Semicolon lost
		}
		break;
	}
	case switchsy:
		conditionState();
		break;
	*/
	case returnsy: {
		returnState();
		if (sy == semicolon) {
			insymbol();
		}
		else {
			error(SemicolonLost); // Semicolon lost
		}
		break;
	}
	case semicolon: // Empty statement, do nothing
		insymbol();
		break;
	default:
		error(StateErr); // Statement error
	}
}

// ＜语句列＞ ::=｛＜语句＞｝
void stateList() {
	while (sy == ifsy || sy == forsy || sy == lbrace || sy == identi ||
		sy == scanfsy || sy == printfsy || sy == switchsy ||
		sy == returnsy || sy == semicolon) {
		statement();
	}
	cout << "This is a statement list." << endl;
}
// ＜条件语句＞ ::= if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
void ifState() {
	string judgeResult = "";
	string firstLabel = "";
	string secondLabel = "";

	if (sy == ifsy) {
		insymbol();
	}
	else if (!skipFlag) {
		error(IfSyLost); // If symbol lost
		symbol nexts[] = { lparent, rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//（
	if (sy == lparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(LeftParentLost); // Left parenthesis lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//<条件>
	if (!skipFlag) {
		judgement(judgeResult);//judgeresult类似于综合属性，<条件>中有比较，传回#t，无比较则传回条件中的左式
	}
	firstLabel = "LABEL" + intToString(labelIndex);
	labelIndex++;
	insertInfix("BEQ", judgeResult, "0", firstLabel); // If judgement = 0 then jump firstLabel
	//）
	if (sy == rparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(RightParentLost); // Right parenthesis lost
		symbol nexts[] = { semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//语句
	if (!skipFlag) {
		statement();
	}
	secondLabel = "LABEL" + intToString(labelIndex);
	labelIndex++;
	insertInfix("JMP", " ", " ", secondLabel); // Jump the else (If not, jump the next label)
	insertInfix("LABEL", " ", " ", firstLabel); // Where if is false go
	labelIndex++;
	//else
	if (sy == elsesy) { // Else is optional
		insymbol();
		statement();
		labelIndex++;
	}
	insertInfix("LABEL", " ", " ", secondLabel); // Where if is true go
	cout << "This is an if statement." << endl;
}
// ＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
void judgement(string &infixString) {
	string compareLeft = "";
	string compareRight = "";
	symbol compareSy = eql;

	if (!skipFlag) {
		expression(compareLeft);
	}
	if (isCompare(sy)) { // Optional branch
		compareSy = sy;
		insymbol();
		expression(compareRight);
		infixString = createTempVar();
		insertTable(vars, ints, infixString.c_str(), 0, level, 0); // 类型为数字，1表示判断成立，0表示判断不成立
		switch (compareSy) {
		case eql:
			insertInfix("EQL", compareLeft, compareRight, infixString);
			break;
		case neq:
			insertInfix("NEQ", compareLeft, compareRight, infixString);
			break;
		case lss:
			insertInfix("LSS", compareLeft, compareRight, infixString);
			break;
		case leq:
			insertInfix("LEQ", compareLeft, compareRight, infixString);
			break;
		case gtr:
			insertInfix("GTR", compareLeft, compareRight, infixString);
			break;
		case geq:
			insertInfix("GEQ", compareLeft, compareRight, infixString);
			break;
		}
	}
	else { // No compare symbol occurred
		infixString = compareLeft;
	}
}

// ＜表达式＞ ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
type expression(string &infixString) { // infixString here must be a variable or value
	type firstType = voids;
	type tempType = voids;
	symbol tempSy = voidsy;
	string tempOperand = "";
	string tempVariable = "";
	//[+|-]
	if (sy == plus || sy == minus) {
		tempSy = sy;
		insymbol();
	}
	if (!skipFlag) {                     //skipFlag = flase进入
		firstType = term(infixString);
	}

	if (tempSy == minus) { // Head is a minus, should get a negative variable
		tempVariable = createTempVar();
		insertTable(vars, ints, tempVariable.c_str(), 0, level, 0);
		insertInfix("NEG", " ", infixString, tempVariable);
		infixString = tempVariable;
	}
	//循环处理后续项
	while (sy == plus || sy == minus) {
		tempSy = sy;
		insymbol();
		tempType = term(tempOperand);
		if (firstType != tempType) { // Type check and change
			//warn(0);
			firstType = ints; // Change type to int
		}
		tempVariable = createTempVar();
		insertTable(vars, ints, tempVariable.c_str(), 0, level, 0);
		insertInfix(tempSy == plus ? "ADD" : "SUB", infixString, tempOperand, tempVariable);
		infixString = tempVariable;
	}
	return firstType;
}
// ＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
type term(string &infixString) {
	type firstType = factor(infixString);
	type tempType = voids;
	string tempOperand = "";
	string tempVariable = "";
	string ioperator = "";

	while (sy == times || sy == idiv) {
		ioperator = sy == times ? "MUL" : "DIV";
		insymbol();
		tempType = factor(tempOperand);
		if (firstType != tempType) { // Check type
			firstType = ints;
		}
		tempVariable = createTempVar();
		insertTable(vars, tempType, tempVariable.c_str(), 0, level, 0);
		insertInfix(ioperator, infixString, tempOperand, tempVariable);
		infixString = tempVariable;
	}
	return firstType;
}
// ＜因子＞ ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’
type factor(string &infixString) {
	type firstType = voids;

	switch (sy) {
	case identi: {
		int idIndex;
		int tempCharPtr = charPtr;
		char tempCh = ch;
		symbol tempSy = sy;

		idIndex = lookUp(token);
		if (idIndex == -1) {
			error(IdNotDefine); // Identifier is not defined
		}
		else {
			firstType = idTable[idIndex].typ;
		}
		infixString = token; // Get variable name

		insymbol();
		if (sy == lbrack) { // Array
			string arrayIndex;
			if (idIndex != -1) {
				if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
					|| idTable[idIndex].length == 0) {
					error(IdKindNotMatch); // Identifier kind does not match
				}
			}
			insymbol();
			if (!skipFlag) {
				expression(arrayIndex);
			}
			if (sy == rbrack) { // Array finished
				string tempVar = createTempVar();
				insertTable(vars, firstType, tempVar.c_str(), 0, level, 0);
				insertInfix("GETARR", infixString, arrayIndex, tempVar);
				infixString = tempVar; // Return temp variable
				insymbol();
			}
			else if (!skipFlag) {
				error(RightBrackLost); // Right bracket lost
				symbol nexts[] = { semicolon, rbrace };
				int length = sizeof(nexts) / sizeof(symbol);
				skipUntil(nexts,length);
			}
		}
		/*
		else if (sy == lparent) { // Call function with return
			if (idTable[idIndex].cls != funcs) {
				error(IdKindNotMatch); // Identifier kind does not match
			}
			charPtr = tempCharPtr;
			ch = tempCh;
			sy = tempSy;
			if (!skipFlag) {
				funcWithRetCall(infixString); // infixString is the temp var assigned with return value
			}
		}*/
		else { // General identifier
			if ((idTable[idIndex].cls != consts && idTable[idIndex].cls != vars && idTable[idIndex].cls != params) ||
				idTable[idIndex].length != 0) {
				error(IdKindNotMatch); // Identifier kind not match
			}
			charPtr = tempCharPtr;
			ch = tempCh;
			sy = tempSy;
			// Variable name already set to infixString
			insymbol();
		}
		break;
	}
	case plus:
	case minus:
	case intcon: {
		if (!skipFlag) {
			integer(infixString); // Get the number
		}
		firstType = ints;
		break;
	}
	case charcon: {
		infixString = intToString(inum);
		insymbol();
		firstType = chars;
		break;
	}
	case lparent: { // "(" expression ")"
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
		firstType = expression(infixString);
		if (sy == rparent) {
			insymbol();
		}
		else {
			error(RightParentLost); // Right parenthesis lost
			symbol nexts[] = { semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}
		break;
	}
	default:
		error(IllegalFact); // Illegal factor
		symbol nexts[] = { semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	return firstType;
}
// ＜循环语句＞ ::= for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
void loopState() {
	string idNameString = "";
	string idNameString2 = "";
	string expressionString = "";
	string judgeResult = "";
	string judgeLabel = "";//判断条件LABEL
	string increaseLabel = "";//步长LABEL
	string bodyLabel = "";//循环体LABEL
	string endLabel = "";

	int idIndex = -1;
	//for
	if (sy == forsy) {
		insymbol();
	}
	else if (!skipFlag) {
		error(ForSyLost); // For symbol lost
		symbol nexts[] = { lparent, semicolon, rparent, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//(
	if (sy == lparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else {
		error(LeftParentLost); // Left parenthesis lost
		symbol nexts[] = { semicolon, rparent, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//<标识符>
	if (sy == identi) {
		idIndex = lookUp(token);
		if (idIndex == -1) {
			error(IdNotDefine); // Identifier is not defined
		}
		else if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
			|| idTable[idIndex].length != 0) {
			error(IdKindNotMatch); // Identifier does not match
		}
		idNameString = token;
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { semicolon, rparent, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//=
	if (sy == becomes) {
		insymbol();
	}
	else if (!skipFlag) {
		error(BecomesSyLost); // Becomes symbol lost
		symbol nexts[] = { semicolon, rparent, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//<表达式>
	if (!skipFlag) {
		expression(expressionString);
	}
	insertInfix("ASSIGN", " ", expressionString, idNameString);
	bodyLabel = labelStr + intToString(labelIndex);//循环体的LABEL bodyLabel
	labelIndex++;
	//insertInfix("JMP", " ", " ", bodyLabel);
	//;
	if (sy == semicolon) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(SemicolonLost); // Semicolon lost
		symbol nexts[] = { semicolon, rparent, rbrace };
		int length = sizeof(nexts) / sizeof(symbol); 
		skipUntil(nexts,length);
	}
	//<条件>
	judgeLabel = labelStr + intToString(labelIndex);
	labelIndex++;
	insertInfix("LABEL", " ", " ", judgeLabel);//条件语句的（i<2）LABEL 

	if (!skipFlag) {
		judgement(judgeResult);
	}
	insertInfix("BNE", judgeResult, "0", bodyLabel); // Jump to body If judgeResult != 0(为真) then jump bodyLabel
	endLabel = labelStr + intToString(labelIndex);
	labelIndex++;
	insertInfix("BEQ", judgeResult, "0", endLabel); // Jump to end If judgeResult = 0(为假) then jump endLabel
	//;
	if (sy == semicolon) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else {
		error(SemicolonLost); // Semicolon lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//<标志符>
	increaseLabel = labelStr + intToString(labelIndex);
	++labelIndex;
	insertInfix("LABEL", " ", " ", increaseLabel);//步长部分的label（i=i+1）
	if (sy == identi) {
		if (idIndex == -1) {
			error(IdNotDefine); // Identifier is not defined
		}
		else if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
			|| idTable[idIndex].length != 0) {
			error(IdKindNotMatch); // Identifier kind does not match
		}
		idNameString = token;
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//=
	if (sy == becomes) {
		insymbol();
	}
	else if (!skipFlag) {
		error(BecomesSyLost); // Becomes symbol lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//<标志符>
	if (sy == identi) {
		if (idIndex == -1) {
			error(IdNotDefine); // Identifier is not defined
		}
		else if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
			|| idTable[idIndex].length != 0) {
			error(IdKindNotMatch); // Identifier kind does not match
		}
		idNameString2 = token;
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//(+|-)
	string ioperator;
	if (sy == plus || sy == minus) {
		ioperator = sy == plus ? "ADD" : "SUB";
		insymbol();
	}
	else if (!skipFlag) {
		error(PlusLost); // Plus or minus lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//＜步长＞
	if (sy == intcon) {
		if (inum != 0) {
			insertInfix(ioperator, idNameString2, intToString(inum), idNameString); // Increment
			insymbol();
		}
		else {
			error(StepLenZero); // Step length couldn't be 0
		}
	}
	else if (!skipFlag) {
		error(StepLenLost); // Step length lost
		symbol nexts[] = { rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	insertInfix("JMP", " ", " ", judgeLabel);
	//‘)’
	if (sy == rparent) {
		if (skipFlag) {
			skipFlag = false;
		}
		insymbol();
	}
	else if (!skipFlag) {
		error(RightParentLost); // Right parenthesis lost
		symbol nexts[] = { semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	insertInfix("LABEL", " ", " ", bodyLabel);
	//＜语句＞
	if (!skipFlag) {
		statement();
	}
	insertInfix("JMP", " ", " ", increaseLabel);
	insertInfix("LABEL", " ", " ", endLabel);
	cout << "This is a loop statement." << endl;
}
// ＜返回语句＞ ::= return[‘(’＜表达式＞‘)’]  return || return(表达式)
void returnState() {
	type firstType = idTable[findCurrentFunc()].typ;
	type secondType = voids;
	string returnString = "";
	//return 
	if (sy == returnsy) {
		insymbol();
	}
	else if (!skipFlag) {
		error(ReturnSyLost); // Return symbol lost
		symbol nexts[] = { lparent, rparent, semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//'('
	if (sy == lparent) { // Optional branch
		insymbol();
		secondType = expression(returnString);
		//')'
		if (sy == rparent) {
			if (firstType != secondType) {
				//warn(0); // Type conflicts
			}
			insertInfix("RETURN", " ", " ", returnString);
			cout << "This is a return statement." << endl;
			insymbol();
		}
		else if (!skipFlag) {
			error(RightParentLost); // Right parenthesis lost
			symbol nexts[] = { semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}
	}
	else {
		insertInfix("RETURN", " ", " ", " "); // Return null
		cout << "This is a return statement." << endl;
	}
}
// ＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
void assignState() {
	string leftToEqual = "";
	string rightToEqual = "";
	int idIndex = -1;
	type firstType = voids;
	type secondType = voids;
	//<标识符>
	if (sy == identi) {
		if ((idIndex = lookUp(token)) == -1) {
			error(IdNotDefine); // Identifier is not defined
		}
		else {
			firstType = idTable[idIndex].typ;
		}
		leftToEqual = token; // Get left variable's name
		insymbol();
	}
	else if (!skipFlag) {
		error(IdLost); // Identifier lost
		symbol nexts[] = { semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}
	//=
	if (sy == becomes) { // General variable or parameter
		if (idIndex != -1) {
			if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
				|| idTable[idIndex].length != 0) {
				error(IdKindNotMatch); // Identifier kind not match
			}
		}
		insymbol();
		secondType = expression(rightToEqual);
		if (firstType != secondType) {
			//warn(0); // Type conflicts
		}
		insertInfix("ASSIGN", " ", rightToEqual, leftToEqual);
		cout << "This is an assignment statement." << endl;
	}
	//[
	else if (sy == lbrack) { // Array
		string arrayIndex;

		if (idIndex != -1) {
			if ((idTable[idIndex].cls != vars && idTable[idIndex].cls != params)
				|| idTable[idIndex].length == 0) {
				error(IdKindNotMatch); // Identifier kind does not match
			}
		}
		insymbol();
		//表达式
		expression(arrayIndex);
		//]
		if (sy == rbrack) {
			insymbol();
		}
		else if (!skipFlag) {
			error(RightBrackLost); // Right bracket lost
			symbol nexts[] = { semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}
		//=
		if (sy == becomes) {
			insymbol();
		}
		else if (!skipFlag) {
			error(BecomesSyLost); // Becomes symbol lost
			symbol nexts[] = { semicolon, rbrace };
			int length = sizeof(nexts) / sizeof(symbol);
			skipUntil(nexts,length);
		}
		//<表达式>
		if (!skipFlag) {
			secondType = expression(rightToEqual);
		}
		if (firstType != secondType) {
			//warn(0); // Type conflicts
		}
		insertInfix("SETARR", rightToEqual, arrayIndex, leftToEqual);
		cout << "This is an assignment statement." << endl;
	}
	else if (!skipFlag) {
		error(BecomesSyLost); // Becomes symbol lost
		symbol nexts[] = { semicolon, rbrace };
		int length = sizeof(nexts) / sizeof(symbol);
		skipUntil(nexts,length);
	}

}
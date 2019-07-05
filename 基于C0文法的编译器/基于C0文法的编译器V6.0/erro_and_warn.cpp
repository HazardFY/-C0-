#include "main.h"

bool errorFlag = false;
bool skipFlag = false;//�����ж�ǰ������Ƿ�����Ծ��������Ϊ0��˵���� skipUntil�б仯Ϊtrue���������ķ�������
string errorMessages[] = {
	"Number starts with zero.",
	"Number too large or too long.",
	"! without = backward.",
	"Empty character.",
	"Illegal character between ''.",
	"Character more than one or ' lost.",
	"Illegal character inside string.",
	"String longer than 50.",
	"Unknown word.",
	"Sign before zero.",
	"Number error.",
	"Not a variable or function.",
	"Identifier repeatedly define.",
	"Char const error.",
	"Const definition type error",
	"Array index error.",
	"Definition head error.",
	"Identifier not define.",
	"Invalid factor.",
	"Identifier kind not match.",
	"Step length couldn't be 0.",
	"Case element not a constant.",
	"Parameter count exceeds.",
	"Illegal type.",
	"Printf symbol lost.",
	"Scanf symbol lost.",
	"Return symbol lost.",
	"Default symbol lost.",
	"Colon lost.",
	"Case symbol lost.",
	"Switch symbol lost.",
	"Plus or minus lost.",
	"For symbol lost.",
	"If symbol lost.",
	"Becomes symbol lost.",
	"Void symbol lost.",
	"Left brace lost.",
	"Right brace lost.",
	"Left parenthesis lost.",
	"Right parenthesis lost.",
	"Right bracket lost.",
	"Identifier lost.",
	"Semicolon lost.",
	"Assignment symbol lost.",
	"Type definition lost.",
	"Step length lost",
	"Statement error",
	"Illegal syntax."
};

void error(int errorNum) {
	static int currentLine = -1;
	if (currentLine != linePtr) { // Error in a new line, accepted
		currentLine = linePtr;
		if (!errorFlag) { // Used to avoid mips code generation
			errorFlag = true;
		}
		cout << "[Line " << linePtr << "] Error: " << errorMessages[errorNum] << endl;
	}
}
//next[]�������ݺʹ����tempSy�Ƚϣ�����ͬ�ķ���TRUE
bool inNexts(symbol nexts[], symbol tempSy,int length) {

	for (int i = 0; i < length; ++i) {
		if (nexts[i] == tempSy) {
			return true;
		}
	}
	return false;
}
//ֱ������next[]�еķ��Ų��˳���һֱinsymbol
void skipUntil(symbol nexts[],int length) {
	
	while (!inNexts(nexts, sy, length)) {
		insymbol();
	}
	skipFlag = true;
}

#include "main.h"
int main() {
	setup();
	//insymbol();
	program();
	outputInfixes();
	//optimizeInfixes();
	mipsProgram("mipsCode.asm");
	system("pause");
	return 0;
}
#include "main.h"
int main() {
	setup();
	//insymbol();
	program();
	outputInfixes();
	optimizeInfixes();
	
	mipsProgram("mipsCode.asm");
	optMipsProgram("betterMips.asm");
	system("pause");
	return 0;
}
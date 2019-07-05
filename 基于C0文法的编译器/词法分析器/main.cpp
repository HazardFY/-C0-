#include "main.h"
int main() {
	setup();//初始化keyword等数组以及文本指针 

	while (!infixFile.eof())
	{
		insymbol();
		if(sy == identi)
		cout << token << endl;//读到数字的时候token内容还是上一次的，所以会重复输出
		
	}
	system("pause");
	return 0;
}
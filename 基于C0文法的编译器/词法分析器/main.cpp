#include "main.h"
int main() {
	setup();//��ʼ��keyword�������Լ��ı�ָ�� 

	while (!infixFile.eof())
	{
		insymbol();
		if(sy == identi)
		cout << token << endl;//�������ֵ�ʱ��token���ݻ�����һ�εģ����Ի��ظ����
		
	}
	system("pause");
	return 0;
}
# 基于C0文法的编译器V5.0
本程序根据之前实现的文法，将[input.txt]中的程序翻译为四元式，利用DAG方法优化四元式存储在[betterInfixes.txt]中，并利用新生成的四元式生成MIPS代码存储在[mipsCode.asm]中  
输入代码存储在[input.txt]中，运行后四元式显示在终端，优化后的四元式存储在[betterInfixes.txt]，MIPS代码存储在[mipsCode.asm]中
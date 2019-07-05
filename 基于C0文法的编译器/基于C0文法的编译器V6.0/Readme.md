# 基于C0文法的编译器V6.0
本程序主要实现对于MIPS代码的局部优化  
本程序根据之前实现的文法，将[input.txt]中的程序翻译为四元式，原始四元式信息存储在[Infixfile.txt]利用DAG方法优化四元式存储在[betterInfixes.txt]中，并利用新生成的四元式生成MIPS代码存储在[mipsCode.asm]中,再将进一步优化后的MIPS代码存储在[betterMips.asm]

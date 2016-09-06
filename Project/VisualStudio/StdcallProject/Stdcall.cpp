#include "Stdcall.h"
#include <iostream>

EAPI int __stdcall sub(int a, int b)
{
	return a - b;
}

EAPI void func()
{
	std::cout<< "func()" << std::endl;
}

EAPI int func2(float a, double b, bool c)
{
	return c ? a + b : 0;
}

EAPI void func3(long* pL, long* pL2, double* pD)
{
	std::cout << "func4" << std::endl;
}

EAPI int func4(Node* pNode, int* pVal)
{
	return 0;
}

EAPI std::string func5(std::string* pStr)
{
	return std::string(*pStr);
}

EAPI int func6(Node* pNode)
{
	return 0;
}

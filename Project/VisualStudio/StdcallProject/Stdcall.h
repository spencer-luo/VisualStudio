#pragma once
#include <string>

#ifdef DYNAMIC_EXPORT
#define _API_ __declspec(dllexport)
#else
#define _API_ __declspec(dllimport)
#endif

#ifdef STATIC_LIBRARY
#define EAPI// int
#else
#define EAPI /*extern "C" */_API_
#endif //STATIC_LIBRARY


EAPI int __stdcall sub(int a, int b);

EAPI void func();

EAPI int func2(float a, double b, bool c);

EAPI void func3(long* pL, long* pL2, double* pD);

class Node
{
	int val;
};
EAPI int func4(Node* pNode, int* pVal);

EAPI std::string func5(std::string* pStr);

EAPI int func6(Node* pNode);
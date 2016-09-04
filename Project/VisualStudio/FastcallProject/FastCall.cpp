#include "FastCall.h"
#include <iostream>

double  multi(double a, double b)
{
	return a * b;
}

EAPI void func()
{
	std::cout << "func()" << std::endl;
}

EAPI int func2(float a, double b, bool c)
{
	return c ? a + b : 0;
}


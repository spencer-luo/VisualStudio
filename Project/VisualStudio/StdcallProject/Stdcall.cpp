#include "Stdcall.h"
#include <stdarg.h>

int __stdcall sum2(int count, ...)
{
	int nSum = 0;

	va_list args;
	va_start(args, count);
	while (count--)
	{
		nSum += va_arg(args, int);
	}
	va_end(args);

	return nSum;
}


EAPI int sub(int a, int b)
{
	return a - b;
}

#include <iostream>

void /*__cdecl */function();
int /*__stdcall */add(int a, int b);

void function()
{
	std::cout << "This is a function." << std::endl;
}

int add(int a, int b)
{
	return a + b;
}

int main()
{
	function();
}
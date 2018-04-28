// Function Pointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>	
#include <string>
void test()
{
	std::cout << "Jello" << std::endl;
}

double test2(int i1, int i2, std::string str)
{
	std::cout << str <<"  "<< i1+i2 << std::endl;
	return i1 + i2;
}
int main()
{
	test();

	void (*pTest)() = test; // pointer to the void function and no parameters


	pTest();

	double(*pTest2)(int, int, std::string) = test2;

	double count = pTest2(1, 3, "Yee");
	std::cout << count<<std::endl;
	system("pause");
    return 0;
}


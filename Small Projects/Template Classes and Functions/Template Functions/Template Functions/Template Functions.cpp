// Template Functions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
template<class T>
void print(T n)
{
	std::cout << n <<" print template used"<< std::endl;
}

void print(int value)
{
	std::cout << value <<" print int used"<< std::endl;
}
template<class T>
void show()
{
	std::cout << T() << std::endl;
}
int main()
{
	print<std::string>("Hello");

	print<int>(2);
	print(2);

	print<double>(3.612);
	print("to");

	show<double>();
	system("pause");
    return 0;
}


// Overloading Comparison Operators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Complex.h"
int main()
{
	Complex comp1(21, 3);
	Complex comp2(2, 3);

	if (comp1 == comp2) {
		std::cout << "equals" << std::endl;
	}
	else
	{
		std::cout << "not equals" << std::endl;
	}

	if (comp1 != comp2) {
		std::cout << "not equals" << std::endl;
	}
	else
	{
		std::cout << "equals" << std::endl;
	}
	system("pause");
    return 0;
}


// Lambda Expression Parameners and Return Type.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>


void testGreet(void (*greet)(std::string str))
{
	greet("Boay");
}

void runDivide(double(*pDivide)(double a, double b))
{
	pDivide(9,3);
}
int main()
{
	auto pGreet = [](std::string name) {std::cout << "name: " << name << std::endl;};
	pGreet("Geogre");

	testGreet(pGreet);

	auto pDivide = [](double a, double b) -> double {
		if (b == 0.0) return 0.0;
		return a / b;
	};

	std::cout << pDivide(10.0, 5.5)<<std::endl;

	std::cout << pDivide(10.0, 0) << std::endl;

	runDivide(pDivide);

	system("pause");
	return 0;
}


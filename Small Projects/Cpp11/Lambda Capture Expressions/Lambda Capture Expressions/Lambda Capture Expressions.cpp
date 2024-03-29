// Lambda Capture Expressions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

int main()
{
	int one = 1;
	int two = 2;
	int three = 3;
	
	// Capture one and two by value
	[one,two]() {std::cout << one << two << std::endl;}();

	// Capture all local variables by value
	[=]() {std::cout << one << two << std::endl;}();

	// Capture all local variables by value and capture three by reference
	[=, &three]() {std::cout << one << two << std::endl; three = 7;}();

	// Capture all local variables by reference
	[&]() {std::cout << one << two << std::endl; three = 2; two = 8;}();
    return 0;
}


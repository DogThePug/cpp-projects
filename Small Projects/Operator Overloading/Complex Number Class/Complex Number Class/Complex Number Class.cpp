// Complex Number Class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Complex.h"

int main()
{
	Complex comp;
	comp= Complex(1, 2);
	Complex comp2 = comp;

	std::cout << comp<< " " << comp2 <<std::endl;
	system("pause");
	
    return 0;
}


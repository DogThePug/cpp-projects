// Mutable Lambdas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	int i = 5;
	[i]() mutable {
		i = 8;
		std::cout << i << std::endl;
	}();

	system("pause");
    return 0;
}


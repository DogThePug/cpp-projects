// Nested Template Classes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ring.h"
#include <string>

int main()
{

	ring<std::string> textstring(3);
	textstring.add("one");
	textstring.add("two");
	textstring.add("three");
	textstring.add("four");


	for (int i = 0; i < textstring.size();i++) {
		std::cout << textstring.get(i) << std::endl;
	}

	// c++ 98 style
	for (ring<std::string>::iterator iter = textstring.begin();iter != textstring.end();iter++) { // uses postfix ++ operator
		std::cout << *iter << std::endl;
	}

	// c++ 11 style
	for (auto value: textstring) { //uses prefix ++ operator
		std::cout << value << std::endl;
	}
	system("pause");
    return 0;
}


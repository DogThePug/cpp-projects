// Perfect Forwarding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Test {

};


template<typename T>
void call(T &&org)
{
	check(org);  // only calls the lvalue even if rvalue is passed in
}

template<typename T>
void callA(T &&org)
{
	check(static_cast<T>(org));  // properely passes r and l values
}

template<typename T>
void callB(T &&org)
{
	check(forward<T>(org));  // using forward for the same effect
}
void check(Test &test)
{
	std::cout << "lvalue" << std::endl;
}
void check(Test &&test)
{
	std::cout << "rvalue" << std::endl;
}
int main()
{
	Test test;

	auto &&t = test;

	call(Test());

	callA(Test());

	callB(t);
	system("pause");
    return 0;
}


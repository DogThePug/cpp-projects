// Functors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>	
#include <string>

struct Test {
	virtual bool operator()(std::string &text) = 0;
};
struct MatchTest : public Test { // functor
	bool operator()(std::string &text)
	{
		return text == "lion";
	}
};

void check(std::string text, Test &test)
{
	std::cout << test(text) << std::endl;
}
int main()
{
	MatchTest pred;
	std::string value = "lion";
	std::string value2 = "Not lion";
	std::cout << pred(value) << std::endl;

	check(value, pred);
	check(value2, pred);
	
	system("pause");
    return 0;
}


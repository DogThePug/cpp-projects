// Template Classes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
template<class T>
class Test {
private:
	T obj;

public:
	Test(T obj)
	{
		this->obj = obj;
	}
	void print()
	{
		std::cout << obj << std::endl;
	}
};

int main()
{
	Test < int > marks(2);
	Test < std::string > marks2("String");
	marks.print();
	marks2.print();

	system("pause");
    return 0;
}


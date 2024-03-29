// Overloading Left Bit Shift.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <string>
class Test {
private:
	int id;
	std::string name;
public:
	Test() :name(""), id(0) {}
	Test(int id, std::string name) :id(id), name(name) {}
	void print() const
	{
		std::cout << id << ": " << name << std::endl;
	}
	//overloading "=" operator
	const Test &operator=(const Test &other)
	{
		id = other.id;
		name = other.name;
		return *this;
	}
	//copy constructor
	Test(const Test &other)
	{
		*this = other;
	}
	// Overloading Left Bit Shift
	friend std::ostream &operator<<(std::ostream &out, const Test &test)
	{
		out << test.id << ": " << test.name;
		return out;
	}
};
int main()
{
	Test test1(10, "Yun");
	test1.print();
	std::cout << test1 << std::endl;
	system("pause");
    return 0;
}


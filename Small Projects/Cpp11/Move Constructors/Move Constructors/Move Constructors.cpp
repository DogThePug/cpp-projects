// Move Constructors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
//Move Construtors and Move Assignment
class Test {
private:
	static const int SIZE = 100;
	int *_pBuffer{ nullptr };
public:
	Test()
	{

		_pBuffer = new int[SIZE] {};  //allocating memory
									  //memset(_pBuffer, 0, sizeof(int)*SIZE);
	}
	Test(int i)
	{
	
		_pBuffer = new int[SIZE] {};

		for (int i = 0; i < SIZE; i++) {
			_pBuffer[i] = 7 * i;
		}
	}
	Test(const Test&other)
	{
		

		_pBuffer = new int[SIZE] {};

		memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));

	}
	Test &operator=(const Test &other)
	{
		_pBuffer = new int[SIZE] {};

		memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));
		return *this;
	}
	~Test()
	{
		delete[]_pBuffer;
	}
	friend std::ostream &operator<<(std::ostream &out, const Test &test);
	// Move constructor -------------------------------------------
	Test(Test &&other)
	{
		std::cout << "Move constructor" << std::endl;
		_pBuffer = other._pBuffer;
		other._pBuffer = nullptr;
	}
	// Move Assignment Operator
	Test &operator=(Test &&other)
	{
		std::cout << "Move assignment" << std::endl;
		delete[] _pBuffer;
		_pBuffer = other._pBuffer;
		other._pBuffer = nullptr;
		return *this;
	}
};
std::ostream &operator<<(std::ostream &out, const Test &test)
{
	out << "Hello from test";
	return out;
}

Test getTest()
{
	return Test();
}

int main()
{
	std::vector<Test> vec;
	vec.push_back(Test());

	Test test;
	test = getTest();
	system("pause");
	return 0;
}
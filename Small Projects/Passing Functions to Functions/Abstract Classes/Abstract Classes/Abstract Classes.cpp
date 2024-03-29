// Abstract Classes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
class Animal {// abstract class
public:
	virtual void run()=0;
	virtual void speak()=0; // pure virtual function
};
class Dog : public Animal { // abstract class
public:
	virtual void speak() 
	{
		std::cout << "woof!" << std::endl;
	}
};
class Poodle :public Dog {
public:
	Poodle()
	{
		std::cout << "Poodle constroodle" << std::endl;
	}
	virtual void run()
	{
		std::cout << "Poodle skadoodle" << std::endl;
	}
};
void test(Animal &a)
{
	a.run();
}
int main()
{
	Poodle Poodle;
	Poodle.speak();
	Poodle.run();

	Animal *animals[5];
	animals[0] = &Poodle;
	
	animals[0]->speak();
	test(Poodle);
	system("pause");
    return 0;
}


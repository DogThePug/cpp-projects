// Binary Files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>


#pragma pack(push, 1) //turns off the padding for the struct, so that we write into a file exactly what is in the struct and nothing else
struct Person {
	char name[50];
	int age;
	double weight;
};
#pragma pack(pop) //turning it back
int main()
{
	Person someone = {"Azazel", 2018, 189};


	/// Writes binary file
	std::string fileName = "test.bin";

	std::fstream outputFile;
	
	outputFile.open(fileName, std::ios::binary|std::ios::out);
	
	if (outputFile.is_open()) {
		outputFile.write(reinterpret_cast<char*>(&someone), sizeof(Person));
		outputFile.close();
	}
	else {
		std::cout << "Couldn`t create file " << fileName <<std::endl;
	}

	/// Reads binary file
	std::fstream inputFile;

	Person someoneElse = {};

	inputFile.open(fileName);

	if (inputFile.is_open()) {

		inputFile.read(reinterpret_cast<char*>(&someoneElse), sizeof(Person));

		inputFile.close();
	}
	else {
		std::cout << "Coudn`t read file " + fileName << std::endl;
	}

	std::cout << someoneElse.name << " " << someoneElse.age << " " << someoneElse.weight << std::endl;
	system("pause");
	return 0;
}


// ReadingTextFiles.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
int main()
{
	std::string inFileName = "text.txt";
	std::ifstream inFile;
	inFile.open(inFileName, std::ios::in);

	if (inFile.is_open()) {

		std::string line;
		while (inFile) {
			std::getline(inFile, line);
			std::cout << line << std::endl;
		}
		inFile.close();
	}
	else {
		std::cout << "Couldn`t open file " << inFileName;
	}
	system("pause");
    return 0;
}


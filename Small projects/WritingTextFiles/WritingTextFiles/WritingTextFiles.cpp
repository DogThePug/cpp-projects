// WritingTextFiles.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
using namespace std;



int main()
{
	//ofstream outFile;
	fstream outFile;;
	string outputFileName = "text.txt";
	//outFile.open(outputFileName);
	outFile.open(outputFileName, ios::out);
	if (outFile.is_open()) {
		for (int i = 0; i < 10;i++) {
			outFile << i <<endl;
		}
		outFile.close();
	}
	else
	{
		cout << "Couldn`t open a file";
	}
	system("pause");
	return 0;
}



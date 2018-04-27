// Multi-Dimensional vectors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector< std::vector<int> > grid(3,std::vector<int>(4,7));
	grid[1].push_back(8);
	for (int row = 0; row < grid.size();row++) {
		for (int col = 0;col < grid[row].size();col++) {
			std::cout << grid[row][col]<<std::flush;
		}
		std::cout << std::endl;
	}
	system("pause");
    return 0;
}


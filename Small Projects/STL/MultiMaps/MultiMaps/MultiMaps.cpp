// MultiMaps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
int main()
{
	std::multimap<int, std::string> multmap;
	multmap.insert(std::make_pair(1, "YuMum"));
	multmap.insert(std::make_pair(6, "hsMum"));
	multmap.insert(std::make_pair(6, "HrMum"));
	multmap.insert(std::make_pair(6, "HrMum3"));
	multmap.insert(std::make_pair(22, "TsMum"));

	for (std::multimap<int, std::string>::iterator iter = multmap.begin();iter != multmap.end();iter++) {
		std::cout << iter->first << ": " << iter->second << std::endl;
	}

	for (std::multimap<int, std::string>::iterator iter = multmap.find(6);iter != multmap.end();iter++) {
		std::cout << iter->first << ": " << iter->second << std::endl;
	}

	std::cout << std::endl;

	// Getting everything with the same key
	std::pair<std::multimap<int, std::string>::iterator, std::multimap<int, std::string>::iterator> it = multmap.equal_range(6);
	for (std::multimap<int, std::string>::iterator iter = it.first; iter != it.second; iter++) {
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
	std::cout << std::endl;

	// Getting everything with the same key using an 'auto'
	auto it2 = multmap.equal_range(6);
	for (std::multimap<int, std::string>::iterator iter = it2.first; iter != it2.second; iter++) {
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
	system("pause");
    return 0;
}


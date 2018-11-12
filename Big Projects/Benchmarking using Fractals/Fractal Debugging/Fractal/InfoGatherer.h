#include <set>

#pragma once

struct Info {
	double CPUUsage;
	size_t VirtualMemUsage;
	size_t RAMUsage;
};

class InfoGatherer
{
public:
	InfoGatherer();
	~InfoGatherer();

	void GetInitialInformation();

	void InitializeNewTest();

	void TickInformationCheck();
private:
	std::set<int> AmountOfThreadsUsed;
	std::set<std::string> PriorityUsed;
	std::set<std::set<Info>> InformationSet;

	std::string CPUHardware;
	int NumberOfCores;
	int TotalRAM;
	void FindHardwareInfo();

	void initializeCPUSettings();
	double CPUCurrentlyUsed();

	
};


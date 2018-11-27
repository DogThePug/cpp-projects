

#pragma once

#include <string>
#include <vector>


struct Info {
	unsigned int CPUUsage;
	size_t VirtualMemUsage;
	size_t RAMUsage;
};

class InfoGatherer
{
public:
	InfoGatherer();
	~InfoGatherer();

	void GetInitialInformation();

	void InitializeNewTest(int PriorityCase, int ThreadsUsed, std::string ZoomUsed);

	void WriteTestsToFile();

	void TickInformationCheck();



	const int GetNumberOfCores();

	void AddNewTestTimeTaken(double TimeTakenOnTest);
private:
	std::vector<double> TimeTakenVector;
	std::vector<std::string> ZoomsUsed;
	std::vector<int> AmountOfThreadsUsed;
	std::vector<std::string> PrioritiesUsed;
	std::vector<std::vector<Info>> InformationSet;

	std::string CPUHardware;
	int NumberOfCores;
	long TotalRAM;
	
	void FindHardwareInfo();
	void initializeCPUSettings();
	double CPUCurrentlyUsed();

	
};


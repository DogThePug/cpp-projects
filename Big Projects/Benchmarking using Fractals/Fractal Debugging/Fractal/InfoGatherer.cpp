#include "stdafx.h"
#include "InfoGatherer.h"
#include "TCHAR.h"
#include "pdh.h"
#include "psapi.h"


#include <iostream>
#include <string>
#include <algorithm>
#include <intrin.h> 
#include <vector>
#include <set>
#include <string>
#include <iomanip>
#include <fstream>

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

InfoGatherer::InfoGatherer()
{
}


InfoGatherer::~InfoGatherer()
{
	
}

void InfoGatherer::GetInitialInformation()
{
	initializeCPUSettings();
	FindHardwareInfo();
}

void InfoGatherer::InitializeNewTest(int PriorityCase, int ThreadsUsed)
{
	// Starting new fresh test results
	AmountOfThreadsUsed.push_back(ThreadsUsed);

	switch (PriorityCase)
	{
	case 1:
		PrioritiesUsed.push_back("ABOVE_NORMAL_PRIORITY_CLASS");
		break;
	case 2:
		PrioritiesUsed.push_back("HIGH_PRIORITY_CLASS");
		break;
	default:
		PrioritiesUsed.push_back("NORMAL_PRIORITY_CLASS");
		break;
	}

	std::vector<Info> NewInfoVector;
	InformationSet.push_back(NewInfoVector);
}

void InfoGatherer::WriteTestsToFile()
{
	std::ofstream outData;
	outData.open("testResults.csv");
	outData << "sep=," <<std::endl;
	outData << "Testing Results." << std::endl << std::endl;
	outData << "CPU Hardware:" << ',' << CPUHardware << std::endl;
	outData << "Number of Cores:" << ',' << NumberOfCores << std::endl;
	outData << "Total RAM:" << ',' << TotalRAM << std::endl;


	int TestNumber = 1;

	int CurrentAmountOfThreadsUsed = 0;
	std::string CurrentPrioritySet = "";
	int run = 0;

	while (run <= AmountOfThreadsUsed.size()-1) 
	{
		while (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(run) && CurrentPrioritySet == PrioritiesUsed.at(run))
		{
			run++;
			if (run >= AmountOfThreadsUsed.size()) break;
		}

		if (run >= AmountOfThreadsUsed.size()) break;

		outData << "\r\n\r\n,,Test Number" << ',' << TestNumber << std::endl << std::endl;

		CurrentAmountOfThreadsUsed = AmountOfThreadsUsed.at(run);
		outData << ",,,Amount of threads used:" << ',' << CurrentAmountOfThreadsUsed << std::endl;

		CurrentPrioritySet = PrioritiesUsed.at(run);
		outData << ",,,CPU load priority used:" << ',' << CurrentPrioritySet << std::endl << std::endl;
	
		int RunNumber = 0;
		int TempRunNumber = 1;
		outData << ",CPU loads during the test:" << ',' << std::endl;
		for (auto InfoVec : InformationSet)
		{
			if (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(RunNumber) && CurrentPrioritySet == PrioritiesUsed.at(RunNumber))
			{
				outData <<"Run "<< TempRunNumber <<',';
				for (auto Info : InfoVec)
				{
					outData << Info.CPUUsage << ',';
				}
				outData << std::endl;
				TempRunNumber++;
			}
			RunNumber++;
		}

		outData << std::endl << std::endl;

		RunNumber = 0;
		TempRunNumber = 1;
		outData << ",Virtual memory loads during the test:" << ',' << std::endl;
		for (auto InfoVec : InformationSet)
		{
			if (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(RunNumber) && CurrentPrioritySet == PrioritiesUsed.at(RunNumber))
			{
				outData << "Run " << TempRunNumber << ',';
				for (auto Info : InfoVec)
				{
					outData << Info.VirtualMemUsage << ',';
				}
				outData << std::endl;
				TempRunNumber++;
			}
			RunNumber++;
		}

		outData << std::endl << std::endl;

		RunNumber = 0;
		TempRunNumber = 1;
		outData << ",Physical memory(RAM) loads during the test:" << ',' << std::endl;
		for (auto InfoVec : InformationSet)
		{
			if (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(RunNumber) && CurrentPrioritySet == PrioritiesUsed.at(RunNumber))
			{
				outData << "Run " << TempRunNumber << ',';
				for (auto Info : InfoVec)
				{
					outData << Info.RAMUsage << ',';
				}
				outData << std::endl;
				TempRunNumber++;
			}
			RunNumber++;
		}

		outData << std::endl << std::endl;

		RunNumber = 0;
		TempRunNumber = 1;
		outData << ",Times taken for each run:" << ',' << std::endl;
		outData << ",,";
		for (auto TimeTaken : TimeTakenVector)
		{
			if (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(RunNumber) && CurrentPrioritySet == PrioritiesUsed.at(RunNumber))
			{
				outData << "run " << TempRunNumber << ",";
				TempRunNumber++;
			}
			RunNumber++;
		}

		RunNumber = 0;
		TempRunNumber = 1;
		outData << std::endl;
		outData << ",,";
		for (auto TimeTaken : TimeTakenVector)
		{
			if (CurrentAmountOfThreadsUsed == AmountOfThreadsUsed.at(RunNumber) && CurrentPrioritySet == PrioritiesUsed.at(RunNumber))
			{
				outData << TimeTaken << " sec,";
				TempRunNumber++;
			}
			RunNumber++;
		}


		TestNumber++;
	}
	outData.close();
}
	


void InfoGatherer::TickInformationCheck()
{
	double CPUUsed = CPUCurrentlyUsed();

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	
	SIZE_T virtMemUsedByMe = pmc.PrivateUsage;
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

	Info InfoToInsert;
	InfoToInsert.CPUUsage = (unsigned int)CPUUsed;
	InfoToInsert.RAMUsage = physMemUsedByMe;
	InfoToInsert.VirtualMemUsage = virtMemUsedByMe;

	InformationSet.at(InformationSet.size()-1).push_back(InfoToInsert);
}



const int InfoGatherer::GetNumberOfCores()
{
	return NumberOfCores;
}

void InfoGatherer::AddNewTestTimeTaken(double TimeTakenOnTest)
{
	TimeTakenVector.push_back(TimeTakenOnTest);
}

void InfoGatherer::FindHardwareInfo()
{
	int CPUInfo[4] = { -1 };
	unsigned   nExIds, i = 0;
	char CPUBrandString[0x40];
	// Get the information associated with each extended ID.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	//string includes manufacturer, model and clockspeed
	CPUHardware = CPUBrandString;


	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	NumberOfCores = sysInfo.dwNumberOfProcessors;

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	TotalRAM = (statex.ullTotalPhys / 1024) / 1024;
}

void InfoGatherer::initializeCPUSettings()
{
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

double InfoGatherer::CPUCurrentlyUsed()
{
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = ((double)sys.QuadPart - lastSysCPU.QuadPart) +
		(user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}

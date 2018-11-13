// Fractal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <ctime>
#include "FractalCreator.h"
#include "Zoom.h"
#include "PrioritySetter.h"
#include "InfoGatherer.h"



int main()
{
	//initialising fractal creator
	int resolutionScale = 1;
	int const WIDTH = resolutionScale*800;
	int const HEIGHT = resolutionScale*600;
	std::string name = "test.bmp";

	
	FractalCreator fractalCreator(WIDTH,HEIGHT);


	// Setup for full gradient coloring method
	int Frequency = 1000;
	double softRange = 0.001*Frequency; // First couple iterations that are supposed to be blacked out
	double HardEnd = 0.05*Frequency; // Upper line for most iterations. Color should be most prominent untill this point. After that coloring is very dull.

	int rColorBegin = 20;
	int rColorEndSoft = 100;
	int rColorEndHard = 255;

	int gColorBegin = 20;
	int gColorEndSoft = 220;
	int gColorEndHard = 255;

	int bColorBegin = 20;
	int bColorEndSoft = 255;
	int bColorEndHard = 255;
	

	std::cout << "Starting." << std::endl;
	///adding color ranges
	int ColoringMethod = 2;
	switch (ColoringMethod)
	{
	case 1:
		//full random color Range
		srand(time(NULL));
		for (double i = 1;i <= 500;i += 1) {
			fractalCreator.addColorRange(i / 500, RGB((int)((rand() * (int)(255) / RAND_MAX)), (int)((rand() * (int)(255) / RAND_MAX)), (int)(rand() * (int)(255) / RAND_MAX)));
		}
		break;

	case 2:
		// Chunky color destribution
		fractalCreator.addColorRange(0.0, RGB(0, 0, 0));
		fractalCreator.addColorRange(0.005, RGB(0, 100, 200));
		fractalCreator.addColorRange(0.15, RGB(100, 200, 200));
		fractalCreator.addColorRange(1.0, RGB(100, 255, 255));
		break;

	case 3:
		//Color Gradient

		fractalCreator.addColorRange(0.0, RGB(0, 0, 0));
		fractalCreator.addColorRange(softRange / Frequency, RGB(rColorBegin, gColorBegin, bColorBegin));
		for (double i = softRange + 1;i <= HardEnd;i += 1) {
			fractalCreator.addColorRange(i / Frequency, RGB((rColorBegin + (rColorEndSoft - rColorBegin)*(i / Frequency)), gColorBegin + (gColorEndSoft - gColorBegin)* (i / Frequency), bColorBegin + (bColorEndSoft - bColorBegin)* (i / Frequency)));
		}
		for (double i = HardEnd + 1; i <= Frequency;i += 1) {
			fractalCreator.addColorRange(i / Frequency, RGB((rColorEndSoft + (rColorEndHard - rColorEndSoft)*(i / Frequency)), gColorEndSoft + (gColorEndHard - gColorEndSoft)* (i / Frequency), bColorEndSoft + (bColorEndHard - bColorEndSoft)* (i / Frequency)));
		}
		break;
	default: fractalCreator.addColorRange(0.0, RGB(0, 0, 0));
	}

	
	int PossibleThreadAmountVariation[4] = { 1,2,4,8 };
	Zoom Zooms[4] = 
	{ 
		Zoom(WIDTH / 2.0, HEIGHT / 2.0, 4.0 / WIDTH),
		Zoom(WIDTH / 2.0, HEIGHT / 2.0, 4.0 / WIDTH),
		Zoom(WIDTH / 2.0, HEIGHT / 2.0, 4.0 / WIDTH),
		Zoom(WIDTH / 2.0, HEIGHT / 2.0, 4.0 / WIDTH) 
	};
	//run
	InfoGatherer Gatherer = InfoGatherer();



	

	//adding zoom
	fractalCreator.addZoom(Zoom(WIDTH / 2.0, HEIGHT / 2.0, 4.0 / WIDTH));

	bool bTestInProgress = false;

	PrioritySetter PrSetter = PrioritySetter();


	Gatherer.GetInitialInformation();

	clock_t begin;
	clock_t end;
	double elapsed_secs;

	std::thread([&bTestInProgress, &Gatherer]() {
		while (true)
		{
			if (bTestInProgress)
			{
				// Wait 5 miliseconds
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				// Call our method
				Gatherer.TickInformationCheck();
			}
		}
	}).detach();

	for (int PriorityCaseIndex = 0; PriorityCaseIndex < 3; PriorityCaseIndex++)
	{
		int PriorityCaseIndex2 = 2;
		PrSetter.SetPriority(PriorityCaseIndex2);
		Gatherer.InitializeNewTest(PriorityCaseIndex2, 8);
		//Calculating Iterations of Mandelbrot algorythm
		begin = clock();

		bTestInProgress = true;
		
		fractalCreator.run(name, 8);


		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		std::cout << "Executing Mandelbrot algorythm took " << elapsed_secs << " seconds." << std::endl;

		bTestInProgress = false;
		Gatherer.AddNewTestTimeTaken(elapsed_secs);
	}
	


	
	Gatherer.WriteTestsToFile();
    return 0;
}


// Fractal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <cmath>
#include <memory>
#include "Bitmap.h"
#include "Zoom.h"
#include "ZoomList.h"
#include "Mandelbrot.h"

int main()
{
	

	int const WIDTH = 800;
	int const HEIGHT = 600;

	ZoomList zoomList(WIDTH,HEIGHT);
	Bitmap bitmap(WIDTH,HEIGHT);

	double min = 9999999;
	double max = -9999999;

	std::unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 });
	std::unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]);
	
	zoomList.add(Zoom( WIDTH / 2, HEIGHT / 2 , 4.0/WIDTH)); // zoom out
	//zoomList.add(Zoom(295, HEIGHT -202, 0.1));
	
	std::cout << "Starting." << std::endl;

	//executing and storing amount of Mandelbrot iterations
	std::cout << "Executiong Mandelbrot algorythm." << std::endl;
	for (int iHeight = 0;iHeight < HEIGHT;iHeight++) {
		for (int iWidth = 0; iWidth < WIDTH;iWidth++)
		{
			std::pair<double, double> coords = zoomList.ZoomIn(iWidth, iHeight);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			if (iterations != Mandelbrot::MAX_ITERATIONS) {
			histogram[iterations]++;
				
			}
			fractal[iHeight*WIDTH + iWidth] = iterations;
		}
	}

	int total = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS;i++) {
		total += histogram[i];
	}
	std::cout << "Done." << std::endl;
	//writing to bitmap
	
	std::cout << "Writing to bitmap." << std::endl;
	for (int iHeight = 0;iHeight < HEIGHT;iHeight++) {
		for (int iWidth = 0; iWidth < WIDTH;iWidth++)
		{
			int iterations = fractal[iHeight*WIDTH + iWidth];
			
			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			if (iterations != Mandelbrot::MAX_ITERATIONS) {

				double hue = 0.0;

				for (int i = 0; i <= iterations; i++) {
					hue += ((double)histogram[i]) / total;
				}

				red = (uint8_t)std::pow(255, 1 / hue);
				green = (uint8_t)std::pow(255, hue);
				if(hue>=0.5)
				blue = (uint8_t)std::pow(2*255, hue);
				else
				blue = (uint8_t)std::pow(2 * 255, 1/hue);
			}
		
			
			bitmap.setPixel(iWidth, iHeight, red, green, blue);
		}
	}
	std::cout << "Done." << std::endl;

	std::cout << "Drawing in file." << std::endl;
	//Drawing in file
	bitmap.write("test.bmp");
	std::cout <<"Finished."<< std::endl;
    return 0;
}


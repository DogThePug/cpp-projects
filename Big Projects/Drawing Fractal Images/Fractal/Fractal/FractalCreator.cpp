#include "stdafx.h"
#include "FractalCreator.h"
#include "Mandelbrot.h"
#include <assert.h> 
#include <iostream>

FractalCreator::FractalCreator(const int  WIDTH, const int HEIGHT):WIDTH(WIDTH),HEIGHT(HEIGHT),_bitmap(WIDTH,HEIGHT), _zoomList(WIDTH, HEIGHT), _fractal(new int[WIDTH*HEIGHT]), _histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }),totalIterations(0)
{
	
}


 FractalCreator::~FractalCreator()
{
}



void FractalCreator::CalculateIterations()
{
	for (int iHeight = 0;iHeight < HEIGHT;iHeight++) {
		for (int iWidth = 0; iWidth < WIDTH;iWidth++)
		{
			std::pair<double, double> coords = _zoomList.ZoomIn(iWidth, iHeight);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			if (iterations != Mandelbrot::MAX_ITERATIONS) {
				_histogram[iterations]++;

			}
			_fractal[iHeight*WIDTH + iWidth] = iterations;
		}
	}

	totalIterations = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS;i++) {
		totalIterations += _histogram[i];
	}
}

void FractalCreator::DrawFractal()
{
	for (int iHeight = 0;iHeight < HEIGHT;iHeight++) {
		for (int iWidth = 0; iWidth < WIDTH;iWidth++)
		{
		
			int iterations = _fractal[iHeight*WIDTH + iWidth];
			int range = getRange(iterations);
			int rangeTotal = _rangeTotals[range];
			int rangeStart = _ranges[range];

			//coloring
			RGB &startColor = _colors[range];
			RGB &endColor = _colors[range+1];
			RGB colorDiff = endColor - startColor;

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			if (iterations != Mandelbrot::MAX_ITERATIONS) {

				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++) {
					totalPixels += _histogram[i];
				}

				red = (uint8_t)(startColor.r + colorDiff.r*(double)totalPixels/rangeTotal);
				green = (uint8_t)(startColor.g + colorDiff.g*(double)totalPixels / rangeTotal);
				blue = (uint8_t)(startColor.b + colorDiff.b*(double)totalPixels / rangeTotal);


				/*red = (uint8_t)std::pow(255, 1 / hue);
				green = (uint8_t)std::pow(255, hue);
				if (hue >= 0.5)
					blue = (uint8_t)std::pow(2 * 255, hue);
				else
					blue = (uint8_t)std::pow(2 * 255, 1 / hue);*/
				
			}


			_bitmap.setPixel(iWidth, iHeight, red, green, blue);
		}
	}
}

void FractalCreator::addColorRange(double rangeEnd, const RGB & rgb)
{
	_ranges.push_back((int)(rangeEnd*Mandelbrot::MAX_ITERATIONS));
	_colors.push_back(rgb);
	if (_bGotFirstRange) {
		_rangeTotals.push_back(0);
	}
	_bGotFirstRange = true;

}

void FractalCreator::addZoom(const Zoom & zoom)
{
	_zoomList.add(zoom); 
}

void FractalCreator::WriteBitmap(std::string name)
{
	_bitmap.write(name);
}

void FractalCreator::calculateRangeTotals()
{
	int rangeIndex = 0;

	for (int i = 0;i < Mandelbrot::MAX_ITERATIONS;i++) {
		int pixels = _histogram[i];

		if (i >= _ranges[rangeIndex + 1]) {
			rangeIndex++;
		}
		_rangeTotals[rangeIndex] += pixels;
	}
	for (int value : _rangeTotals) {
		std::cout << "Range total:" << value << std::endl;
	}
}

int FractalCreator::getRange(int iterations) const
{
	int range = 0;

	for (int i = 1; i < (int)_ranges.size();i++) {
		range = i;

		if (_ranges[i] > iterations) break;
		
	}
	range--;

	assert(range > -1);
	assert(range < (int)_ranges.size());
	return range;
}

void FractalCreator::run(std::string name)
{
	

	//Calculating Iterations of Mandelbrot algorythm
	
	std::cout << "Executing Mandelbrot algorythm." << std::endl;
	CalculateIterations();
	std::cout << "Done." << std::endl;
	calculateRangeTotals();
	
	//Drawing 
	std::cout << "Drawing fractal." << std::endl;
	DrawFractal();
	std::cout << "Done." << std::endl;

	std::cout << "Writing to bitmap file." << std::endl;
	WriteBitmap(name);



	//writing to bitmap
	std::cout << "Finished." << std::endl;
}

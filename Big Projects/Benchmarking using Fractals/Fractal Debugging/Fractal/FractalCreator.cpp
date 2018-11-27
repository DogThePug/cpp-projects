#include "stdafx.h"
#include "FractalCreator.h"
#include "Mandelbrot.h"

#include <assert.h> 
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

FractalCreator::FractalCreator(const int  WIDTH, const int HEIGHT):WIDTH(WIDTH),HEIGHT(HEIGHT),_bitmap(WIDTH,HEIGHT), _zoomList(WIDTH, HEIGHT), _fractal(new int[WIDTH*HEIGHT]), _histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }),totalIterations(0)
{
}


 FractalCreator::~FractalCreator()
{
}

 
void FractalCreator::CalculateIterations(int AmountOfThreadsUsed)
{
	for (unsigned int a = 0; a < sizeof(_histogram); a++)
	{
		_histogram[a] = 0; // reseting the histogram;
	}
	auto IterThread = [this, AmountOfThreadsUsed](int thread)
	{
		for (int iHeight = (HEIGHT/ AmountOfThreadsUsed)*(thread - 1);iHeight < (HEIGHT/ AmountOfThreadsUsed)*(thread);iHeight++) {
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
	};
	
	
	std::vector<std::thread> v;
	for (int i = 0; i < AmountOfThreadsUsed; i++)
	{
		v.push_back(std::thread(IterThread, i + 1));
	}

	join_all(v);


	totalIterations = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS;i++) {
		totalIterations += _histogram[i];
	}
}


void FractalCreator::DrawFractal()
{
	auto IterDraw = [this](int thread) {
		for (int iHeight = (HEIGHT/4)*(thread - 1); iHeight < (HEIGHT/4)*thread; iHeight++) {
			for (int iWidth = 0; iWidth < WIDTH;iWidth++)
			{

				int iterations = _fractal[iHeight*WIDTH + iWidth];
				int range = getRange(iterations);
				int rangeTotal = _rangeTotals[range];
				int rangeStart = _ranges[range];

				//coloring
				RGB &startColor = _colors[range];
				RGB &endColor = _colors[range + 1];
				RGB colorDiff = endColor - startColor;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				if (iterations != Mandelbrot::MAX_ITERATIONS) {

					int totalPixels = 0;

					for (int i = rangeStart; i <= iterations; i++) {
						totalPixels += _histogram[i];
					}

					red = (uint8_t)(startColor.r + colorDiff.r*(double)totalPixels / rangeTotal);
					green = (uint8_t)(startColor.g + colorDiff.g*(double)totalPixels / rangeTotal);
					blue = (uint8_t)(startColor.b + colorDiff.b*(double)totalPixels / rangeTotal);

				}
				_bitmap.setPixel(iWidth, iHeight, red, green, blue);
			}
		}
	};
	std::thread t1(IterDraw, 1);
	std::thread t2(IterDraw, 2);
	std::thread t3(IterDraw, 3);
	std::thread t4(IterDraw, 4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
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

void FractalCreator::resetZoom()
{
	_zoomList.clear();
}

void FractalCreator::WriteBitmap(std::string name)
{
	_bitmap.write(name);
}

void FractalCreator::calculateRangeTotals()
{
	for (auto item : _rangeTotals)
	{
		item = 0;
	}
	int rangeIndex = 0;

	for (int i = 0;i < Mandelbrot::MAX_ITERATIONS;i++) {
		int pixels = _histogram[i];

		if (i >= _ranges[rangeIndex + 1]) {
			rangeIndex++;
		}
		_rangeTotals[rangeIndex] += pixels;
	}
	if (_rangeTotals.size() > 10)
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "Range " << i+1 << " total:" << _rangeTotals[i] << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < _rangeTotals.size(); i++)
		{
			std::cout << "Range " << i+1 << " total:" << _rangeTotals[i] << std::endl;
		}
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


void FractalCreator::run(std::string name, int AmountOfThreadsUsed)
{
	std::cout << "Executing Mandelbrot algorythm." << std::endl;
	CalculateIterations(AmountOfThreadsUsed);
	std::cout << "Finished." << std::endl;

	//calculateRangeTotals();


	//std::cout << "Drawing fractal." << std::endl;
	//DrawFractal();
	//std::cout << "Done." << std::endl;

	////writing to bitmap
	//std::cout << "Writing to bitmap file." << std::endl;
	//WriteBitmap(name);


}


void FractalCreator::do_join(std::thread & t)
{
	t.join();
}

void FractalCreator::join_all(std::vector<std::thread> & v)
{
	for (int i = 0; i < v.size(); i++)
	{
		do_join(v.at(i));
	}
}
#pragma once

#include<string>
#include <memory>
#include <vector>
#include "ZoomList.h"
#include "Bitmap.h"
#include "RGB.h"
#include <functional>
#include <mutex>

class FractalCreator
{
private:
	std::mutex _mu;
	int WIDTH;
	int HEIGHT;
	std::unique_ptr<int[]> _histogram;
	std::unique_ptr<int[]> _fractal;
	Bitmap _bitmap;
	ZoomList _zoomList;
	int totalIterations;

	std::vector<int> _ranges;
	std::vector<RGB> _colors;
	std::vector<int> _rangeTotals;

	bool _bGotFirstRange{ false };

	void CalculateIterations();
	void DrawFractal();
	void WriteBitmap(std::string name);
	void calculateRangeTotals();
	int getRange(int iterations) const;
public:
	void addColorRange(double rangeEnd, const RGB& rgb);
	void addZoom(const Zoom& zoom);
	FractalCreator(const int  WIDTH, const int HEIGHT);
	virtual ~FractalCreator();
	void run(std::string name);
};


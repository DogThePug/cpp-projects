#pragma once
#include <vector>
#include <utility>
#include "Zoom.h"

class ZoomList
{
private:
	double _xCenter{ 0 };
	double _yCenter{ 0 };
	double _scale{ 1 };

	int _width{ 0 };
	int _height{ 0 };
	std::vector<Zoom> Zooms;
public:
	ZoomList(int width, int height);
	void add(const Zoom& zoom);
	void clear();
	std::pair<double, double> ZoomIn(int x, int y);
};


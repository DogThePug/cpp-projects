#include "stdafx.h"
#include "ZoomList.h"



ZoomList::ZoomList(int width, int height):_width(width),_height(height)
{
}

void ZoomList::add(const Zoom & zoom)
{
	Zooms.push_back(zoom);

	_xCenter += (zoom.x - _width / 2)*_scale;
	_yCenter += (_height - zoom.y - _height / 2)*_scale;

	_scale *= zoom.scale;
}

void ZoomList::clear()
{
	Zooms.clear();
	_xCenter = 0;
	_yCenter = 0;
	_scale = 1;
}

std::pair<double, double> ZoomList::ZoomIn(int x, int y)
{
	double xFractal = (x - _width / 2)*_scale + _xCenter;
	double yFractal = (y - _height/ 2)*_scale + _yCenter;
	return std::pair<double, double>(xFractal,yFractal);
}




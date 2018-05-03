#pragma once

#include<string>
#include "Zoom.h"
class FractalCreator
{
public:
	FractalCreator();
	~FractalCreator();

	void CalculateIterations();
	void DrawFractal();
	void addZoom(const Zoom& zoom);
	void WriteBitmap(std::string name);
};


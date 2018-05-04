#pragma once
class Mandelbrot
{

public:
	static const int MAX_ITERATIONS = 2000;

	Mandelbrot();
	~Mandelbrot();

	static int getIterations(double x, double y);
	
};


#include "stdafx.h"
#include "Mandelbrot.h"
#include <complex>
#include <cmath>

Mandelbrot::Mandelbrot()
{
}


Mandelbrot::~Mandelbrot()
{
}

int Mandelbrot::getIterations(double x, double y)
{
	std::complex<double> z = 0.0;
	std::complex<double> c(x, y);

	int iterations = 0;

	while (iterations < MAX_ITERATIONS) {
		iterations++;
		z = z*z + c;
		if (std::abs(z) > 2) { break; }
	}

	return iterations;
}

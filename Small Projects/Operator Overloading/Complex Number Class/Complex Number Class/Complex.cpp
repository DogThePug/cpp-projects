#include "stdafx.h"
#include <iostream>
#include <ostream>
#include "Complex.h"


Complex::Complex():real(0), imaginary(0)
{
}

Complex::Complex(double real, double imaginary):real(real),imaginary(imaginary)
{
}
Complex::~Complex()
{
}
Complex::Complex(Complex &other)
{
	std::cout << "copy"<< std::endl;
	real = other.real;
	imaginary = other.imaginary;
}

const Complex & Complex::operator=(const Complex & other)
{
	std::cout << "assign" << std::endl;
	real = other.real;
	imaginary = other.imaginary;
	return *this;
}

double Complex::getReal() const
{
	return real;
}

double Complex::getImaginary() const
{
	return imaginary;
}

std::ostream &operator<<(std::ostream & out, const Complex & c)
{
	out << c.getReal() << "," << c.getImaginary();
	return out;
}

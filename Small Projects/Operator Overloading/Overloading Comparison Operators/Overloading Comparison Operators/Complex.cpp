#include "stdafx.h"
#include <iostream>
#include <ostream>
#include "Complex.h"


std::ostream &operator<<(std::ostream & out, const Complex & c)
{
	out << c.getReal() << "," << c.getImaginary();
	return out;
}


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
	real = other.real;
	imaginary = other.imaginary;
}

const Complex & Complex::operator=(const Complex & other)
{
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
bool Complex::operator==(const Complex & other) const
{
	return (real == other.real) && (imaginary == other.imaginary);
}
bool Complex::operator!=(const Complex & other) const
{
	return !(*this == other);
}
// Defining '+' operator overloading from the inside of the class
/*Complex Complex::operator+(const Complex &other) const
{
	Complex result;
	result.real = real + other.real;
	result.imaginary = imaginary + other.imaginary;
	return result;
}*/

//Defining '+' operator overloading from the outside of the class
Complex operator+(const Complex &c1, const Complex &c2)
{
Complex cSum(c1.getReal() + c2.getReal(), c1.getImaginary() + c2.getImaginary());
return cSum;
}

Complex operator+(const Complex & c1, double e)
{
	Complex cSum(c1.getReal() + e, c1.getImaginary());
	return cSum;
}

Complex operator+(double e, const Complex & c1)
{
	Complex cSum(c1.getReal() + e, c1.getImaginary());
	return cSum;
}


#pragma once

class ostream; // forward declaration
class Complex
{
private:
	double real;
	double imaginary;
public:
	Complex();
	Complex(double real, double imaginary);
	~Complex();
	// copy constructor
	Complex(Complex &other);
	// overloading "=" operator
	const Complex &operator=(const Complex &other);

	double getReal() const;
	double getImaginary() const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);
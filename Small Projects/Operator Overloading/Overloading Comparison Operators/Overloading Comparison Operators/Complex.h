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

	//Declaring '+' operator overloading from the inside of the class
	//Complex operator+(const Complex &other) const;

	//Declaring '==' and '!=' operators overloading
	bool operator==(const Complex &other) const;
	bool operator!=(const Complex &other) const;
};

std::ostream &operator<<(std::ostream &out, const Complex &c);

//Declaring '+' operator overloading from the outside of the class
Complex operator+(const Complex &c1, const Complex &c2);
Complex operator+(const Complex &c1, double e);
Complex operator+( double e, const Complex &c1);


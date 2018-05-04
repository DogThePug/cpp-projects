#pragma once

#include<string>
#include <cstdint>
#include <memory>

class Bitmap
{
	int _width{ 0 };
	int _height{ 0 };
	std::unique_ptr<uint8_t[]> _pPixels{ nullptr };
public:

	Bitmap(int width, int height);
	virtual ~Bitmap();
	
	bool write(std::string filename);
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
};


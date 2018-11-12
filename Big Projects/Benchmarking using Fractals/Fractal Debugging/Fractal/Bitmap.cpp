#include "stdafx.h"
#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>



Bitmap::Bitmap(int width, int height) :_width(width), _height(height), _pPixels(new uint8_t[width*height * 3]{})
{
}

Bitmap::~Bitmap()
{
}

// Writes the bitmap
bool Bitmap::write(std::string filename)
{
	BitMapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitmapInfoHeader) + sizeof(BitMapFileHeader) + _width + _height * 3;
	fileHeader.dataOffset = sizeof(BitmapInfoHeader) + sizeof(BitMapFileHeader);

	infoHeader.width = _width;
	infoHeader.height = _height;

	std::ofstream fileWriter;

	fileWriter.open(filename, std::ios::out | std::ios::binary);

	if (!fileWriter) {
		return false;
	}

	fileWriter.write((char*)&fileHeader, sizeof(fileHeader));
	fileWriter.write((char*)&infoHeader, sizeof(infoHeader));
	fileWriter.write((char*)_pPixels.get(), _width*_height*3);

	fileWriter.close();
	if (!fileWriter) {
		return false;
	}
	return false;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t *pPixel = _pPixels.get();

	pPixel += y * 3 * _width + x * 3;

	pPixel[0] = blue;

	pPixel[1] = green;

	pPixel[2] = red;
}

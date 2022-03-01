#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

namespace mcr {

	Bitmap::Bitmap(int width, int height)
		: m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]{}) {

	}

	Bitmap::~Bitmap() {

	}

	void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {

		uint8_t* pPixel = m_pPixels.get();
		pPixel += (y * m_width + x) * 3;

		*pPixel++ = blue;
		*pPixel++ = green;
		*pPixel = red;
	}

	void Bitmap::setImage(const std::vector< std::vector<uint8_t> > &img) {

		auto img_height = img.size();
		assert(img_height == m_height);
		if (img_height == 0)
			return;

		auto img_width = img[0].size();
		assert(img_width == m_width);

		uint8_t* pPixel = m_pPixels.get();
		for (int y = 0; y < img_height; y++)
		{
			for (int x = 0; x < img_width; x++)
			{
				auto val = img[y][x];
				setPixel(x, y, val, val, val);
			}
		}
	}

	int Bitmap::write(string filename) {

		BitmapFileHeader fileHeader;
		BitmapInfoHeader infoHeader;
		
		fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_height * 3;
		fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		infoHeader.width = m_width;
		infoHeader.height = m_height;

		ofstream file;
		file.open(filename, ios::binary); //this did not open when it said (...,ios::out | ios::binary)
		if (!file) {
			return -1;
		}
			
		file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
		file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
		file.write(reinterpret_cast<char*>(m_pPixels.get()), m_width * m_height * 3);

		file.close();
		if (!file)
			return -2;

		return 0;
	}
} // namespace mcr
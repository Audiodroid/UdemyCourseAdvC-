#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <string>
#include<cstdint>
#include <memory>

using namespace std;

namespace mcr {

	class Bitmap
	{

	private:
		int m_width{ 0 };
		int m_height{ 0 };
		unique_ptr<uint8_t[]> m_pPixels{nullptr};

	public:

		Bitmap(int width, int height);
		virtual ~Bitmap();
		
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
		void setImage(const std::vector< std::vector<uint8_t> >& img);
		int write(string filename);		
	};

} //namespace mcr

#endif //_BITMAP_H_


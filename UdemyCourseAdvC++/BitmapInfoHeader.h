#ifndef _BITMAP_INFO_HEADER_H_
#define _BITMAP_INFO_HEADER_H_

#include <cstdint>

using namespace std;

namespace mcr {

#pragma pack(2)

	struct BitmapInfoHeader {
		int32_t headerSize{ 40 };
		int32_t width{ 0 };
		int32_t height{ 0 };
		int16_t planes{ 1 };
		int16_t bitsPerPixel{ 24 };
		int16_t compression{ 0 };
		int32_t dataSize{ 0 };
		int32_t horizontalResolution{ 2400 };
		int32_t verticalResolution{ 2400 };
		int32_t colors{ 0 };
		int32_t importantColors{ 0 };
	};

} // namespace mcr

#endif //_BITMAP_INFO_HEADER_H_
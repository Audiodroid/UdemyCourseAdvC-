#ifndef _BITMAP_FILE_HEADER_H_
#define _BITMAP_FILE_HEADER_H_

#include <cstdint>

using namespace std;

namespace mcr {

#pragma pack(2)

	struct BitmapFileHeader {
		char header[2]{ 'B','M' };
		int32_t fileSize{ 0 };
		int32_t reserved{ 0 };
		int32_t dataOffset{ 0 };
	};


} // namespace mcr

#pragma pack(pop)

#endif // _BITMAP_FILE_HEADER_H_
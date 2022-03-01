#ifndef _ZOOM_H_
#define _ZOOM_H_

namespace mcr {

	struct Zoom
	{
		int x{ 0 };
		int y{ 0 };
		double scale{ 0.0 };

		Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {}
	};

}

#endif //_ZOOM_H_


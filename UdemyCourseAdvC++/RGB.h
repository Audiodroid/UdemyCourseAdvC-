#ifndef _RGB_H_
#define _RGB_H_

namespace mcr {
	struct RGB
	{
		double r;
		double g;
		double b;

		RGB(double r, double g, double b);		
	};

	RGB operator-(const RGB& first, const RGB& second);
}
#endif //_RGB_H_

#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

namespace mcr {
	class Mandelbrot
	{
	public:
		static const int MAX_ITERATIONS = 1000;

	public:
		Mandelbrot();
		virtual ~Mandelbrot();

		static int getIterations(double x, double y);
	};
}

#endif //_MANDELBROT_H_


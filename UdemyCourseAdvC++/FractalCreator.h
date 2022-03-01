
#ifndef _FRACTAL_CRETOR_H_
#define _FRACTAL_CRETOR_H_

#include <string>
#include <vector>

#include "Zoom.h"
#include "ZoomList.h"
#include "Bitmap.h"
#include "RGB.h"

using namespace std;

namespace mcr {

	class FractalCreator
	{
	private:
		int m_width{ 0 };
		int m_height{ 0 };

		Bitmap m_bitmap;
		ZoomList m_zoomList;
		unique_ptr<int[]> m_histogram{ nullptr };
		unique_ptr<int[]> m_fractal{ nullptr };
		int m_total{ 0 };

		vector<int> m_ranges;
		vector<RGB> m_colors;
		vector<int> m_rangeTotals;

		bool m_bGotFirstRange{false};
		void calculateInteration();
		void calcualteTotalIterations();
		void calculateRangeTotals();
		void drawFractal();
		void writeBitmap(string name);

	public:
		FractalCreator(int width, int height);
		virtual ~FractalCreator();
		void addRange(double rangeEnd, const RGB& rgb);
		int getRange(int interations) const;
		void addZoom(const Zoom& zoom);

		void run(string name);
	};
}

#endif //_FRACTAL_CRETOR_H_


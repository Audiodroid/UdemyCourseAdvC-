#include <assert.h>
#include <iostream>
#include<cstdint>
#include<vector>

#include "Bitmap.h"
/*
 * uint8_t conv(std::vector< std::vector<uint8_t> >& img,
	const std::vector< std::vector<int> >& kernel,
	int x, int xdiff, int w, int y, int ydiff, int h)
*/
uint8_t conv(std::vector< std::vector<uint8_t> >& img,
	const std::vector< std::vector<int> >& kernel,
	int x, size_t w, int y, size_t h)
{
	auto h_filter = kernel.size();
	auto w_filter = kernel[0].size();
	auto xdiff = (int)floor(w_filter / 2.0);
	auto ydiff = (int)floor(h_filter / 2.0);

	int val = 0;
	for (int yy = -ydiff; yy < ydiff; yy++)
	{
		for (int xx = -xdiff; xx < xdiff; xx++)
		{
			auto xpos = x + xx;
			if (xpos < 0 || xpos >= w)
				continue;

			auto ypos = y + yy;
			if (ypos < 0 || ypos >= h)
				continue;

			val += img[ypos][xpos] * kernel[xdiff - xx][ydiff - yy];			
		}
	}
	
	val /= (double)(h_filter * w_filter);

	if (val < 0) val = 0;
	if (val > 255) val = 255;

	return val;
}
/*
* void shrink(std::vector< std::vector<uint8_t> >& img, int w, int h)
*/
void shrink(std::vector< std::vector<uint8_t> >& img, int w, int h)
{
	/* define kernel */
	auto w_filter = 3;
	auto h_filter = 3;
	std::vector< std::vector<int> > kernel(h_filter, std::vector<int>(w_filter, 0));
	kernel = { {1, 1, 1},
			   {1, 1, 1},
			   {1, 1, 1} };

	/* strides... */
	auto h_old = img.size();
	assert(h_old > 0);

	assert(h > 0);
	int stride_y = (int)floor(h_old / (double)h);
	assert(stride_y > 0);

	auto w_old = img[0].size();
	assert(w > 0);
	int stride_x = (int)floor(w_old / (double)w);

	/* go! */
	std::vector< std::vector<uint8_t> > imgNew(h, std::vector<uint8_t>(w, 0));
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			//imgNew[y][x] = img[y * stride_y][x * stride_x];
			imgNew[y][x] = conv(img, kernel, x * stride_x, w_old, y * stride_y, h_old);
		}
	}

	img = imgNew;
}
/*
 * void createGradientImage(std::vector< std::vector<uint8_t> > &img)
*/
void createGradientImage(std::vector< std::vector<uint8_t> >& img)
{
	const int MAX_8BIT = 255;

	auto h = img.size();
	auto w = img[0].size();

	uint8_t r = 0, g = 0, b = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			auto val = round(MAX_8BIT * x / (double)w);
			val = val * y / (double)h;
			img[y][x] = (uint8_t)val;
		}
	}
}
/*
 * void filter(std::vector< std::vector<uint8_t> >& img,
*/
void filter1(std::vector< std::vector<uint8_t> >& img,
	const std::vector< std::vector<int> >& kernel) {

	auto h = img.size();
	auto w = img[0].size();

	std::vector< std::vector<uint8_t> > imgNew(h, std::vector<uint8_t>(w));

	auto h_filter = kernel.size();
	auto w_filter = kernel[0].size();
	auto xdiff = (int)floor(w_filter / 2.0);
	auto ydiff = (int)floor(h_filter / 2.0);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			//convolution			
			int val = 0;
			for (int yy = -ydiff; yy < ydiff; yy++)
			{
				for (int xx = -xdiff; xx < xdiff; xx++)
				{
					auto xpos = x + xx;
					if (xpos < 0 || xpos >= w)
						continue;

					auto ypos = y + yy;
					if (ypos < 0 || ypos >= y)
						continue;

					val += img[ypos][xpos] * kernel[xdiff - xx][ydiff - yy];
				}
			}

			if (val < 0) val = 0;
			if (val > 255) val = 255;
			imgNew[y][x] = (uint8_t)val;
		}
	}

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			img[y][x] = imgNew[y][x];
		}
	}
}
/*
 * void filter(std::vector< std::vector<uint8_t> >& img,
*/
void filter2(std::vector< std::vector<uint8_t> >& img,
	const std::vector< std::vector<int> >& kernel)
{
	auto h = img.size();
	auto w = img[0].size();

	std::vector< std::vector<uint8_t> > imgNew(h, std::vector<uint8_t>(w));

	auto h_filter = kernel.size();
	auto w_filter = kernel[0].size();
	auto xdiff = (int)floor(w_filter / 2.0);
	auto ydiff = (int)floor(h_filter / 2.0);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			imgNew[y][x] = conv(img, kernel, x, w, y, h);
		}
	}

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			img[y][x] = imgNew[y][x];
		}
	}
}
/*
 * int main()
*/
int main()
{
	std::cout << "Started..." << std::endl;

	auto w = 200;
	auto h = 100;
	std::vector< std::vector<uint8_t> > img(h, std::vector<uint8_t>(w, 0));
	createGradientImage(img);

	mcr::Bitmap bmp(w, h);
	bmp.setImage(img);
	bmp.write("C:\\Users\\Marcel\\Desktop\\orig.bmp");

	//{
	//	auto w_filter = 3;
	//	auto h_filter = 3;
	//	std::vector< std::vector<int> > kernel(h_filter, std::vector<int>(w_filter, 0));
	//	kernel = { {1, 1, 1},
	//				{1, 1, 1},
	//				{1, 1, 1} };
	//	//filter1(img, kernel);
	//	filter2(img, kernel);
	//}

	{
		auto w_shrink = 100;
		auto h_shrink = 50;
		shrink(img, w_shrink, h_shrink);

		mcr::Bitmap bmp2(w_shrink, h_shrink);
		bmp2.setImage(img);
		bmp2.write("C:\\Users\\Marcel\\Desktop\\filt2.bmp");
	}


	std::cout << "Finished." << std::endl;

	return 0;
}


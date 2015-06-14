#include <image.h>
#include <source.h>
#include <string.h>
#include <stdio.h>

Image::Image(void)
{
	w= new int;
	h= new int;
	*w = 0;
	*h = 0;
	data = NULL;
}

Image::~Image(void)
{
	if (data != NULL)
		delete [] data;
}

void
Image::setSize(int width, int height)
{
	*w = width;
	*h = height;
	data = new Pixel[width*height];
}

void
Image::setData(Pixel *pixelData)
{
	memcpy(data, pixelData, (*w)*(*h)*sizeof(Pixel));
}

void
Image::Update(void) const
{
	s->Update();
}

void
Image::setSource(Source *source)
{
	s = source;
}



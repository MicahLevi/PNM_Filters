#include <filters.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <logging.h>

using std::cerr;
using std::endl;

void
Shrinker::Execute(void)
{
	int hIN = imageIn1->getHeight();
	int wIN = imageIn1->getWidth();
	int w = wIN/2;
	int h = hIN/2;
	imageOut->setSize(w, h);
	Pixel *buffer = imageOut->getData();
	Pixel *data = imageIn1->getData();	
	for (int i=0; i<h; i++)
		for (int j=0; j<w; j++)
			buffer[i*w+j] = data[i*wIN*2+j*2];
}

int
Shrinker::getNumInputs(void)
{
	return 1;
}

void
LRConcat::Execute(void)
{
	if(imageIn1->getHeight()!=imageIn2->getHeight())
	{
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int h = imageIn1->getHeight();
	int wl = imageIn1->getWidth();
	int wr = imageIn2->getWidth();
	imageOut->setSize(wl+wr, h);
	Pixel *buffer = imageOut->getData();
	Pixel *imgL = imageIn1->getData();
	Pixel *imgR = imageIn2->getData();
	for (int i=0; i<h; i++)
	{
		for (int j=0; j<wl; j++)
			buffer[i*(wl+wr)+j] = imgL[i*wl+j];
		for (int k=0; k<wr; k++)
			buffer[i*(wr+wl)+k+wl] = imgR[i*wr+k];
	} 
}

void
TBConcat::Execute(void)
{
	if(imageIn1->getWidth()!=imageIn2->getWidth())
	{
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int w = imageIn1->getWidth();
	int ht = imageIn1->getHeight();
	int hb = imageIn2->getHeight();
	imageOut->setSize(w, ht+hb);
	Pixel *buffer = imageOut->getData();
	Pixel *imgT = imageIn1->getData();
	Pixel *imgB = imageIn2->getData();
	for (int i=0; i<ht; i++)
		for (int j=0; j<w; j++)
				buffer[i*w+j] = imgT[i*w+j];	
	for (int i=0; i<hb; i++)
		for (int j=0; j<w; j++)
				buffer[(ht+i)*w+j] = imgB[i*w+j];
}

void
Blender::Execute(void)
{
	if(imageIn1->getHeight()!=imageIn2->getHeight())
	{
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(imageIn1->getWidth()!=imageIn2->getWidth())
	{
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(ratio>1 || ratio<0)
	{
		char msg[1024];
		sprintf(msg, "Invalid factor for %s: %f", SinkName(), ratio);
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int w = imageIn1->getWidth();
	int h = imageIn1->getHeight();
	Pixel *buffer = new Pixel[w*h];
	Pixel *imgA = imageIn1->getData();
	Pixel *imgB = imageIn2->getData();
	for (int i=0; i<h; i++){
		for (int j=0; j<w; j++){
				buffer[i*w+j].red = imgA[i*w+j].red * ratio + imgB[i*w+j].red * (1-ratio);
				buffer[i*w+j].green = imgA[i*w+j].green * ratio + imgB[i*w+j].green * (1-ratio);
				buffer[i*w+j].blue = imgA[i*w+j].blue * ratio + imgB[i*w+j].blue * (1-ratio);}}
	imageOut->setSize(w, h);
	imageOut->setData(buffer);
	delete [] buffer;
}

void
Crop::Execute(void)
{
	//Adapted from Hank's Crop.C
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= imageIn1->getWidth() || Istop >= imageIn1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= imageIn1->getHeight() || Jstop >= imageIn1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = imageIn1->getWidth();
	imageOut->setSize(width, height);
    Pixel *buffer = imageOut->getData();
    Pixel *buffer1 = imageIn1->getData();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[idx]   = buffer1[idx1];
        }
}

int
Crop::getNumInputs(void)
{
	return 1;
}

void
Transpose::Execute(void)
{
	int height = imageIn1->getHeight();
	int width = imageIn1->getWidth();
	imageOut->setSize(height, width);
	Pixel *buffer = imageOut->getData();
	Pixel *buffer1 = imageIn1->getData();
	for (int h=0; h<height; h++)
		for (int w=0; w < width; w++)
			buffer[w*height+h] = buffer1[h*width+w];
}

int
Transpose::getNumInputs(void)
{
	return 1;
}

void
Invert::Execute(void)
{
	int height = imageIn1->getHeight();
	int width = imageIn1->getWidth();
	imageOut->setSize(width, height);
	Pixel *buffer = imageOut->getData();
	Pixel *buffer1 = imageIn1->getData();
	for (int w=0; w < width; w++)
		for (int h=0; h<height; h++)
		{
			buffer[h*width+w].red = 255 - buffer1[h*width+w].red;
			buffer[h*width+w].green = 255 - buffer1[h*width+w].green;
			buffer[h*width+w].blue = 255 - buffer1[h*width+w].blue;
		}


}

int
Invert::getNumInputs(void)
{
	return 1;
}

void
Checkerboard::Execute(void)
{
	if(imageIn1->getHeight()!=imageIn2->getHeight())
	{
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(imageIn1->getWidth()!=imageIn2->getWidth())
	{
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), imageIn1->getHeight(), imageIn2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	int w = imageIn1->getWidth();
	int h = imageIn1->getHeight();
	imageOut->setSize(w,h);
	Pixel *buffer = imageOut->getData();
	Pixel *imgA = imageIn1->getData();
	Pixel *imgB = imageIn2->getData();
	for (int i=0; i<h; i++)
		for (int j=0; j<w; j++)
		{
				if ((i/10+j/10)%2==0)
					buffer[i*w+j] = imgA[i*w+j];
				else buffer[i*w+j] = imgB[i*w+j];
		}
}


Color::Color(int width, int height, int red, int green, int blue)
{
	if (red < 0 || red > 255)
	{
		char msg[1024];
		sprintf(msg, "Color: invalid red channel");
		DataFlowException e("Color", msg);
		throw e;
	}

	if (green < 0 || green > 255)
	{
		char msg[1024];
		sprintf(msg, "Color: invalid green channel");
		DataFlowException e("Color", msg);
		throw e;
	}

	if (blue < 0 || blue > 255)
	{
		char msg[1024];
		sprintf(msg, "Color: invalid blue channel");
		DataFlowException e("Color", msg);
		throw e;
	}
	
	if (width < 0 || height < 0)
	{
		char msg[1024];
		sprintf(msg, "Color: invalid dimensions %d, %d", width, height);
		DataFlowException e("Color", msg);
		throw e;
	}

	imageOut->setSize(width, height);
	Pixel *buffer = imageOut->getData();
	for(int h=0; h<height; h++)
		for(int w=0; w<width; w++)
		{
			buffer[h*width+w].red = red;
			buffer[h*width+w].green = green;
			buffer[h*width+w].blue = blue;
		}
}

void
CheckSum::OutputCheckSum(const char *filename)
{

	int w = imageIn1->getWidth();
	int h = imageIn1->getHeight();
	Pixel *buffer = imageIn1->getData();
	int r = 0, g = 0, b = 0;
	for (int i=0; i<h; i++)
		for (int j=0; j<w; j++)
		{
			r += buffer[i*w+j].red;
			g += buffer[i*w+j].green;
			b += buffer[i*w+j].blue;
		}
	FILE *f_out = fopen(filename, "wb");
	fprintf(f_out, "CHECKSUM: %d, %d, %d\n", r%256, g%256, b%256);
	fclose(f_out);
}

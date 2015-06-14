#ifndef PIXEL_H
#define PIXEL_H

class Source;

struct Pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class Image
{
	protected:
		int 	*w;
		int 	*h;
		Pixel 	*data;
		Source 	*s;
	public:
					Image(void);
		virtual 	~Image(void);
		int 		getWidth() const {return *w;};
		int 		getHeight() const {return *h;};
		Pixel* 		getData() const {return data;};
		void 		setData(Pixel *pixelData);
		void 		Update(void) const;
		void 		setSource(Source *source);
		void		setSize(int w, int h);
};
#endif

#ifndef SINK_H
#define SINK_H
#include <image.h>
#include <stdio.h>

class Sink
{
	protected:
		const Image *imageIn1;
		const Image *imageIn2;
	public:
		virtual void 			SetInput(Image* i);
		virtual void 			SetInput2(Image* i);
		virtual const Image* 	GetInput(void);
		virtual const Image* 	GetInput2(void);
		virtual const char 		*SinkName(void)=0;
		virtual ~Sink(void){};
		Sink(void){ imageIn1 = NULL; imageIn2 = NULL;};
};

#endif

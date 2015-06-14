#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>
#include <stdio.h>

class Source
{
	friend Image;
	protected:
		Image 			*imageOut;
		virtual void 	Execute(void)=0;
		virtual void 	Update(void);
		bool			updating;
	public:
		virtual Image* 	GetOutput(void);
						Source(void)
						{imageOut = new Image(); imageOut->setSource(this); updating=false;};
		virtual const char 	*SourceName(void)=0;
		virtual int 	getNumInputs(void){return 1;};
};

#endif

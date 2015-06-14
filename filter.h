#ifndef FILTER_H
#define FILTER_H

#include <source.h>
#include <sink.h>
#include <image.h>

class Filter: public Sink, public Source
{
	protected:
		void 				Update(void);
		virtual const char 	*SinkName(void){return FilterName();};
		virtual const char 	*SourceName(void){return FilterName();};
		virtual const char 	*FilterName(void)=0;
		virtual int 		getNumInputs(void);
};


#endif

#ifndef WRITER_H
#define WRITER_H

#include <image.h>
#include <sink.h>

class PNMwriter: public Sink
{
	public:
		PNMwriter(void){};
		void Write(const char *filename);
		virtual const char *SinkName(void){return "PNMwriter";};
};

#endif

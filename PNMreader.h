#ifndef READER_H
#define READER_H

#include <string.h>
#include <source.h>
#include <stdio.h>

class PNMreader : public Source
{
	protected:
		char *s;
		void Update(void);
	public:	
		PNMreader(const char *str);
		~PNMreader(void){delete [] s;};
		void Execute(void);
		virtual const char *SourceName(void){return "PNMreader";};

};

#endif

#include <PNMwriter.h>
#include <stdio.h>

void
PNMwriter::Write(const char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "wb");
	/*write header*/
	fprintf(f_out, "P6\n%u %u\n255\n", imageIn1->getWidth(), imageIn1->getHeight());
	/*copy pixel data*/
	fwrite(imageIn1->getData(), 3 * imageIn1->getWidth(), imageIn1->getHeight(), f_out);
	fclose(f_out);
}


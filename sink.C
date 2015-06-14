#include <sink.h>
#include <stdio.h>

void 
Sink::SetInput(Image* i)
{
	imageIn1 = i;
}

void
Sink::SetInput2(Image* i)
{
	imageIn2 = i;
}

const Image*
Sink::GetInput(void)
{
	return imageIn1;
}

const Image*
Sink::GetInput2(void)
{
	return imageIn2;
}

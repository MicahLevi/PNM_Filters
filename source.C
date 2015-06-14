#include <image.h>
#include <source.h>
#include <logging.h>
#include <stdio.h>

Image*
Source::GetOutput(void)
{
	return imageOut;
}

void
Source:: Update(void)
{

	char msg[128];
	sprintf(msg,"%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg,"%s: done executing", SourceName());
	Logger::LogEvent(msg);
}


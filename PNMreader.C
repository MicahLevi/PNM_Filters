#include <stdio.h>
#include <PNMreader.h>
#include <logging.h>

void
PNMreader::Execute(void)
{
	FILE *f_in;
	int height, width, maxval;/*image dimensions*/
	char *magicNum = new char[4];/*holder for P6 check*/

	f_in = fopen(s, "r");

	/*get header information*/
	fscanf(f_in, "%s\n%d %d\n%u\n", magicNum, &width, &height, &maxval);
	
	/*check for right magic num P6*/
	if (magicNum[0] != 'P' || magicNum[1] != '6')
	{
		fprintf(stderr, "pnm file must be pf type P6, file may be corrupt");
	}
	delete [] magicNum;

	imageOut->setSize(width, height);
	//Pixel *buffer = imageOut->getData();
	/*put pixel information into data array*/
	fread(imageOut->getData(), 3 * width, height, f_in);
	fclose(f_in);
}

void
PNMreader::Update(void)
{
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	this->Execute();
	sprintf(msg,"%s: done executing", SourceName());
	Logger::LogEvent(msg);

	
}

PNMreader::PNMreader(const char *str)
{
	s = new char[100]();	
	strcpy(s, str);
}

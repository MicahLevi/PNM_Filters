#include <filter.h>
#include <stdio.h>
#include <logging.h>

int
Filter::getNumInputs(void)
{
	return 2;
}


void
Filter::Update(void)
{
	if (updating == true)
	{
		char msg[1024];
		sprintf(msg, "%s: input loop detected!", SourceName());
		DataFlowException e(SourceName(), msg);
		throw e;
	}
	updating = true;
	if(imageIn1==NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	char msg[128];
	sprintf(msg, "%s: about to update input1", SourceName());
	Logger::LogEvent(msg);
	
	this->imageIn1->Update();	

	if(imageIn1->getData()==NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	sprintf(msg,"%s: done updating input1", SourceName());
	Logger::LogEvent(msg);
	sprintf(msg, "%s: about to update input2", SourceName());
	Logger::LogEvent(msg);
	
	if (getNumInputs() == 2)
	{
		if(imageIn2==NULL)
		{
			char msg[1024];
			sprintf(msg, "%s: no input2!", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
		}
		this->imageIn2->Update();
		if(imageIn2->getData()==NULL)
		{
			char msg[1024];
			sprintf(msg, "%s: no input2!", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
		}
		sprintf(msg,"%s: done updating input2", SourceName());
		Logger::LogEvent(msg);
	}
	updating = false;
	Source::Update();
}




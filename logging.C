#include <logging.h>
#include <exception>
#include <fstream>

FILE *Logger::logger = NULL;

DataFlowException::DataFlowException(const char *type, const char *error)
{
	sprintf(msg, "Throwing exception: (%s): %s", type, error);
	Logger::LogEvent(msg);
}

void
Logger::LogEvent(const char *event)
{
	if (logger == NULL){
		 logger = fopen("logger", "w");
	}
	fprintf(logger, "%s\n", event);
	//logger << event << std::endl;
}

void
Logger::Finalize()
{
	fclose(logger);
}

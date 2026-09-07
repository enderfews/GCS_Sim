#pragma once

#include "domain/Logs/LogPrinter.h"
#include <string>

using namespace std;

/*
* @brief The default log printer implementation for the GCSLog manager.
* This implementation prints the incoming message into the console command
*/
class GCSLogPrinter: public ILogPrinter
{
public:
	/*
	* @brief Prints the received message from the GCSLog class
	* into the specific log implementation system.
	* @param LogLevel - An enum that determines the level of the message (INFO, WARNING, ERROR, FATAL)
	* @param Message - A message received to display it into the log implementation
	*/
	virtual void PrintLog(ELogLevel LogLevel, const string& Message) override;
};
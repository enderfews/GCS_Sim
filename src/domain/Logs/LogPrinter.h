
#pragma once

#include"LogTypes.h"
#include<string>

using namespace std;
/*
* @brief Interface (port) used to implement the specific Log printer adapter.
* IlogPrinters are the implementations used by GCSLog, the manager in charge 
* of logging. When the GCSLog logs a message, it will propagate to all the registered
* ILogPrinters. If you want to display logs into the different infraestructure 
* systems (Qt, console, OpenGL, SQL, etc), implement a ILogPrinter for each of them
* and then register it. More info about registering ILogPrinter in GCSLog class
*/
class ILogPrinter
{
public:
	virtual ~ILogPrinter() = default;
	/*
	* @brief Prints the received message from the GCSLog class 
	* into the specific log implementation system.
	* @param LogLevel - An enum that determines the level of the message (INFO, WARNING, ERROR, FATAL)
	* @param Message - A message received to display it into the log implementation
	*/
	virtual void PrintLog(ELogLevel LogLevel, const string& Message) = 0;
};
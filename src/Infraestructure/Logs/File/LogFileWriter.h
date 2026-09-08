#pragma once

#include "domain/Logs/LogPrinter.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
/*
* @brief This log printer keeps writing the data in a log file until the application
* ends or this is removed from the GCSLog manager
*/
class LogFileWriter : public ILogPrinter
{
public:
	virtual ~LogFileWriter();
	LogFileWriter();
	/*
	* @brief Prints the received message from the GCSLog class
	* into a file to get the logs registered in case of crash, shutdown, etc.
	* @param LogLevel - An enum that determines the level of the message (INFO, WARNING, ERROR, FATAL)
	* @param Message - A message received to display it into the log implementation
	*/
	virtual void PrintLog(ELogLevel LogLevel, const string& Message) override;

private:
	void InitializeFileName();
private:
	ofstream m_LogFile;
	string m_sFileName;
	static const string FileBaseName;
	static const string FileFormat;
};
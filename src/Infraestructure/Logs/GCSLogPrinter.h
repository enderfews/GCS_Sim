#pragma once

#include "domain/Logs/LogPrinter.h"
#include <string>

using namespace std;

/*
	Default adapter for logs
*/
class GCSLogPrinter: public ILogPrinter
{
public:
	virtual void PrintLog(ELogLevel LogLevel, const string& Message) override;
};
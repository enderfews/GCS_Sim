
#pragma once

#include"LogTypes.h"
#include<string>

using namespace std;
/*
	Interface (port) used to implement the specific Log adapter
*/
class ILogPrinter
{
public:
	virtual ~ILogPrinter() = default;
	virtual void PrintLog(ELogLevel LogLevel, const string& Message) = 0;
};
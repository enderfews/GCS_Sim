#include "GCSLogPrinter.h"
#include <iostream>
#include <ctime>
#include "Utils/GCSUtils.h"
#include "domain/Logs/LogUtils.h"

void GCSLogPrinter::PrintLog(ELogLevel LogLevel, const string& Message)
{
	string OutMessage;
	GCS::Time::GetDateAndTimeNow(OutMessage);
	GCS::Logs::GetLogLevelToString(LogLevel, OutMessage);
	OutMessage += Message;
	cout << OutMessage << endl;
}

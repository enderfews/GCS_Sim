#include "GCSLogPrinter.h"
#include <iostream>

void GCSLogPrinter::PrintLog(ELogLevel LogLevel, const string& Message)
{
	string OutMessage;
	switch (LogLevel)
	{
	case ELogLevel::Info:
		OutMessage = "[INFO]";
		break;
	case ELogLevel::Warning:
		OutMessage = "[WARNING]";
		break;
	case ELogLevel::Error:
		OutMessage = "[ERROR]";
		break;
	case ELogLevel::Fatal:
		OutMessage = "[FATAL]";
		break;
	default:
		OutMessage = "[UNSUPPORTED]";
		break;
	}
	OutMessage += Message;
	cout << OutMessage << endl;
}

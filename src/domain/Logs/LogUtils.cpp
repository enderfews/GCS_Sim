
#include "LogUtils.h"
#include "LogTypes.h"


void GCS::Logs::GetLogLevelToString(ELogLevel Level, std::string& OutStringLevel)
{
	switch (Level)
	{
	case ELogLevel::Info:
		OutStringLevel += "[INFO]: ";
		break;
	case ELogLevel::Warning:
		OutStringLevel += "[WARNING]: ";
		break;
	case ELogLevel::Error:
		OutStringLevel += "[ERROR]: ";
		break;
	case ELogLevel::Fatal:
		OutStringLevel += "[FATAL]: ";
		break;
	default:
		OutStringLevel += "[UNSUPPORTED]: ";
		break;
	}
}

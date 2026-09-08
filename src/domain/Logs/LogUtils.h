#pragma once

#include <string>

enum class ELogLevel;

namespace GCS
{
	namespace Logs
	{
		void GetLogLevelToString(ELogLevel Level, std::string& OutStringLevel);
	}
}
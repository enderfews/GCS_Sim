#pragma once

#define STRINGIFY_TOKEN(x) #x

#define FUNCTION_MSG(x) __FUNCTION__##" "##x

#if defined(_WIN16) | defined(_WIN32) | defined(_WIN64)
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif

#include <string>
using namespace std;

namespace GCS
{
	namespace Time
	{
		string unixTimeToHumanReadable(long long seconds);
		void GetDateAndTimeNow(string& OutDateTime, const string& format = "%Y-%m-%d %H:%M:%S");
	}
}
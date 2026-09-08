#pragma once

#define STRINGIFY_TOKEN(x) #x

#define FUNCTION_MSG(x) __FUNCTION__##" "##x

#include <string>
using namespace std;

namespace GCS
{
	namespace Time
	{
		string unixTimeToHumanReadable(long long seconds);
		void GetDateAndTimeNow(string& OutDateTime, bool bUseBrackets = true);
	}
}
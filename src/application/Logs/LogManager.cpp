#include "LogManager.h"

GCSLog& GCSLog::GetInstance()
{
	static GCSLog instance;
	return instance;
}

void GCSLog::Log(const ELogLevel Level, const string& Message)
{
#if defined(GCS_DEBUG) && GCS_DEBUG
	if (m_LogPrinters.size() == 0)
	{
		return;
	}

	for (auto It = m_LogPrinters.begin(); It != m_LogPrinters.end(); ++It)
	{
		if (!It->second)
		{
			continue;
		}

		It->second->PrintLog(Level, Message);
	}
#endif
}
#pragma once

#include "domain/Logs/LogPrinter.h"
#include "domain/Logs/LogTypes.h"
#include "Utils/GCSUtils.h"
#include <memory>
#include <string>
#include <map>
#include "Utils/GCSGlobals.h"

using namespace std;
/*
	Singleton class for the log system
*/

class GCSLog
{
public:
	static GCSLog& GetInstance();

	//Display log messages to all log adapters
	void Log(const ELogLevel Level, const string& Message);

	template<class LogClass>
	void AddPrinter()
	{
#if defined(GCS_DEBUG) && GCS_DEBUG
		static_assert(is_base_of_v<ILogPrinter, LogClass>, "GCSLog AddPrinter - LogClass must inherit from ILogPrinter");
		const string PrinterName = STRINGIFY_TOKEN(LogClass);
		const auto it = m_LogPrinters.find(PrinterName);
		if (it != m_LogPrinters.end())
		{
			//Already exists
			return;
		}

		m_LogPrinters.emplace(PrinterName, make_unique<LogClass>());
#endif
	}
	template<class LogClass>
	void RemovePrinter()
	{
#if defined(GCS_DEBUG) && GCS_DEBUG
		static_assert(is_base_of_v<ILogPrinter, LogClass>, "GCSLog RemovePrinter - LogClass must inherit from ILogPrinter");
		const string PrinterName = STRINGIFY_TOKEN(LogClass);
		const auto it = m_LogPrinters.find(PrinterName);
		if (it == m_LogPrinters.end())
		{
			//Already removed
			return;
		}

		m_LogPrinters.erase(PrinterName);
#endif
	}
private:
	GCSLog() = default;
	~GCSLog() = default;
	//Delete constructor and operators to avoid copy, assignment or movement of this singleton
	GCSLog(const GCSLog&) = delete;
	GCSLog(GCSLog&&) = delete;
	GCSLog& operator=(const GCSLog&) = delete;
	GCSLog& operator=(GCSLog&&) = delete;
	map<string, unique_ptr<ILogPrinter>> m_LogPrinters;

};
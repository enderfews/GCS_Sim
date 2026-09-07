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
	@brief Singleton class for the log system. This manager is in charge of
	printing all messages to the different logs systems (aka ILogPrinter).
	By default, there's a console log implemented and added at the beginning 
	of main() function. You can implement and add/remove these log systems on
	demand. Create a class that implements ILogPrinter and added it to the GCSLog
*/
class GCSLog
{
public:
	/*
		@brief Gets the instance of this singleton.NOTE: Do not try to save the
		reference into a variable, forbidden.
		@return - The instance of GCSLog
	*/
	static GCSLog& GetInstance();

	/*
		@brief Print the message to the different log systems
		@param Level - Determines the level of this log (info, warning, error, etc)
		@param Message - The log message to display to the different and registered logs
	*/
	void Log(const ELogLevel Level, const string& Message);

	/*
		@brief Adds a new log printer into the GCSLog. Log printers are the
		different implementations of the logs that allows you to propagate the
		message into the different areas (Ex: console command, QtWidget log, File log, etc).
		NOTE: This function is a templated function and receives the Log Printer class, if
		the class you provide doesn't inherit from ILogPrinter, It will throw compile errors
	*/
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

	/*
		@brief Removes an existing log printer from the GCSLog. Log printers are the
		different implementations of the logs that allows you to propagate the
		message into the different areas (Ex: console command, QtWidget log, File log, etc).
		NOTE: This function is a templated function and receives the Log Printer class, if
		the class you provide doesn't inherit from ILogPrinter, It will throw compile errors
	*/
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
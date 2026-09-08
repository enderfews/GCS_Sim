
#include "LogFileWriter.h"
#include "Utils/GCSUtils.h"
#include "domain/Logs/LogUtils.h"

const string LogFileWriter::FileBaseName = "Log_";
const string LogFileWriter::FileFormat = ".txt";
LogFileWriter::~LogFileWriter()
{
	m_LogFile.close();
}

LogFileWriter::LogFileWriter()
{
	InitializeFileName();
	m_LogFile.open(m_sFileName, ios::app);
}

void LogFileWriter::PrintLog(ELogLevel LogLevel, const string& Message)
{
	if (!m_LogFile.is_open())
	{
		//No file
		return;
	}
	string FileLine;
	GCS::Time::GetDateAndTimeNow(FileLine);
	GCS::Logs::GetLogLevelToString(LogLevel, FileLine);
	FileLine += Message;
	FileLine += "\n";

	m_LogFile << FileLine;
	m_LogFile.flush(); //Ensure immediate write to file
}

void LogFileWriter::InitializeFileName()
{
	m_sFileName = FileBaseName;
	GCS::Time::GetDateAndTimeNow(m_sFileName, false);
	m_sFileName += FileFormat;
}

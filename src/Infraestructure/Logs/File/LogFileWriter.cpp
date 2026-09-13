
#include "LogFileWriter.h"
#include "Utils/GCSUtils.h"
#include "Utils/GCSGlobals.h"
#include "domain/Logs/LogUtils.h"


const string LogFileWriter::g_sFileBaseName = "Log_";
const string LogFileWriter::g_sFileFormat = ".txt";
LogFileWriter::~LogFileWriter()
{
	m_LogFile.close();
}

LogFileWriter::LogFileWriter()
{
	InitializeFileName();
	m_LogFile.open(m_sFileName, ios::app);
	if (!m_LogFile.is_open())
	{
		cout << "Failed to create/open the file: " << m_sFileName << endl;
	}
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
	m_sFileName = g_sFileBaseName;
	GCS::Time::GetDateAndTimeNow(m_sFileName, "%Y_%m_%d_%H_%M_%S");
	m_sFileName += g_sFileFormat;
}

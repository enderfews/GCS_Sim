#include "QtTcpTelemetryInput.h"
#include "application/Logs/LogManager.h"
#include "Utils/GCSUtils.h"
#include <sstream>
#include <QThread>
#include <QMetaObject>
#include "Infraestructure/Qt/Workers/TelemetryInput/QtTcpTelemetryWorker.h"


QtTcpTelemetryInput::~QtTcpTelemetryInput()
{
	Stop();
}

void QtTcpTelemetryInput::Start()
{
	if (!m_bIsCallbcackSet)
	{
		GCSLog::GetInstance().Log(ELogLevel::Warning, FUNCTION_MSG("Callback is not set in telemetry input"));
	}

	if (m_pInputThread)
	{
		GCSLog::GetInstance().Log(ELogLevel::Warning, FUNCTION_MSG("Telemetry input already running"));
		return;
	}

	m_pInputThread = new QThread();
	m_pWorker = new QtTcpTelemetryWorker(Address, Port);
	m_pWorker->moveToThread(m_pInputThread);
	//The worker will start the moment the thread does
	QObject::connect(m_pInputThread, &QThread::started, m_pWorker, &QtTcpTelemetryWorker::Start);
	QObject::connect(m_pWorker, &QtTcpTelemetryWorker::Started, this, &QtTcpTelemetryInput::OnWorkerStarted, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtTcpTelemetryWorker::Stopped, this, &QtTcpTelemetryInput::OnWorkerStopped, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtTcpTelemetryWorker::Error, this, &QtTcpTelemetryInput::OnWorkerError, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtTcpTelemetryWorker::TelemetryReceived, this, &QtTcpTelemetryInput::OnTelemetryReceived, Qt::QueuedConnection);

	m_pInputThread->start();
}

void QtTcpTelemetryInput::Stop()
{
	if (!m_pInputThread || !m_pWorker)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Invalid worker and/or thread"));
		return;
	}

	/*
	* Since the worker is not in the main thread, we must not call Stop() directly 
	*/
	QMetaObject::invokeMethod(m_pWorker, &QtTcpTelemetryWorker::Stop, Qt::BlockingQueuedConnection);

	m_pInputThread->quit();
	m_pInputThread->wait();

	delete m_pWorker;
	m_pWorker = nullptr;

	delete m_pInputThread;
	m_pInputThread = nullptr;

	m_bIsCallbcackSet = false;
}

void QtTcpTelemetryInput::SetTelemetryCallback(OnTelemetryReceivedCallback Callback)
{
	m_Callback = Callback;
	m_bIsCallbcackSet = true;
}

void QtTcpTelemetryInput::OnTelemetryReceived(const QByteArray& Data)
{
	if (!m_bIsCallbcackSet)
	{
		return;
	}

	std::vector<uint8_t> TelemetryData(reinterpret_cast<const uint8_t*>(Data.constData()), reinterpret_cast<const uint8_t*>(Data.constData()) + Data.size());
	m_Callback(TelemetryData);
}

void QtTcpTelemetryInput::OnWorkerStarted()
{
	GCSLog::GetInstance().Log(ELogLevel::Info, "TCP telemetry server started");
}

void QtTcpTelemetryInput::OnWorkerStopped()
{
	GCSLog::GetInstance().Log(ELogLevel::Info, "TCP telemetry server stopped");
}

void QtTcpTelemetryInput::OnWorkerError(const QString& Message)
{
	GCSLog::GetInstance().Log(ELogLevel::Error, Message.toStdString());
}




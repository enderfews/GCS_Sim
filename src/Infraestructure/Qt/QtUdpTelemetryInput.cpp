
#include "QtUdpTelemetryInput.h"
#include "application/Logs/LogManager.h"
#include <QThread>
#include <QMetaObject>
#include "Infraestructure/Qt/Workers/TelemetryInput/QtUdpTelemetryWorker.h"

QtUdpTelemetryInput::~QtUdpTelemetryInput()
{
	/*Stop();*/
}

void QtUdpTelemetryInput::Start()
{
	if (!m_bIsCallbcackSet)
	{
		GCSLog::GetInstance().Log(ELogLevel::Warning, FUNCTION_MSG("Callback is not set in telemetry input"));
	}

	m_pInputThread = new QThread(this);
	m_pWorker = new QtUdpTelemetryWorker(Address, Port);
	m_pWorker->moveToThread(m_pInputThread);

	QObject::connect(m_pInputThread, &QThread::started, m_pWorker, &QtUdpTelemetryWorker::Start);
	QObject::connect(m_pWorker, &QtUdpTelemetryWorker::Started, this, &QtUdpTelemetryInput::OnWorkerStarted, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtUdpTelemetryWorker::Stopped, this, &QtUdpTelemetryInput::OnWorkerStopped, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtUdpTelemetryWorker::Error, this, &QtUdpTelemetryInput::OnWorkerError, Qt::QueuedConnection);
	QObject::connect(m_pWorker, &QtUdpTelemetryWorker::UdpDatagramReceived, this, &QtUdpTelemetryInput::OnDatagramReceived, Qt::QueuedConnection);

	m_pInputThread->start();
}

void QtUdpTelemetryInput::Stop()
{
	//QObject::disconnect(m_pUdpSocket, &QUdpSocket::readyRead, this, &QtUdpTelemetryInput::receiveUdpDatagram);
	if (!m_pInputThread || !m_pWorker)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Invalid worker and/or thread"));
		return;
	}

	/*
	* Since the worker is not in the main thread, we must not call Stop() directly
	*/
	QMetaObject::invokeMethod(m_pWorker, &QtUdpTelemetryWorker::Stop, Qt::BlockingQueuedConnection);

	m_pInputThread->quit();
	m_pInputThread->wait();

	delete m_pWorker;
	m_pWorker = nullptr;

	delete m_pInputThread;
	m_pInputThread = nullptr;

	m_bIsCallbcackSet = false;
	m_bIsCallbcackSet = false;
	//delete m_pUdpSocket;
}

void QtUdpTelemetryInput::SetTelemetryCallback(OnTelemetryReceivedCallback Callback)
{
	m_CachedCallback = Callback;
	m_bIsCallbcackSet = true;
}

void QtUdpTelemetryInput::OnDatagramReceived(const QByteArray& Data)
{
	if (!m_bIsCallbcackSet)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Callback has not set on receiving datagram"));
		return;
	}
	//We get the bytes in this format so it doesn't rely on Qt nor other implementations
	m_CachedRawData.clear();
	m_CachedRawData.insert(m_CachedRawData.end(), Data.begin(), Data.end());
	m_CachedCallback(m_CachedRawData);
}

void QtUdpTelemetryInput::OnWorkerStarted()
{
	GCSLog::GetInstance().Log(ELogLevel::Info, "UDP telemetry started");
}

void QtUdpTelemetryInput::OnWorkerStopped()
{
	GCSLog::GetInstance().Log(ELogLevel::Info, "UDP telemetry stopped");
}

void QtUdpTelemetryInput::OnWorkerError(const QString& Message)
{
	GCSLog::GetInstance().Log(ELogLevel::Error, Message.toStdString());
}

//void QtUdpTelemetryInput::receiveUdpDatagram()
//{
//	if (!m_bIsCallbcackSet)
//	{
//		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Callback has not set on receiving datagram"));
//		return;
//	}
//	// Fetch the full datagram: raw bytes and metadata
//	QNetworkDatagram datagram = m_pUdpSocket->receiveDatagram();
//
//	// Extract only the raw bytes from the datagram, ignoring metadata.
//	QByteArray QPayload = datagram.data();
//	//We get the bytes in this format so it doesn't rely on Qt nor other implementations
//	m_CachedRawData.clear();
//	m_CachedRawData.insert(m_CachedRawData.end(), QPayload.begin(), QPayload.end());
//	m_CachedCallback(m_CachedRawData);
//}
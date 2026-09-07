
#include "QtTcpTelemetryWorker.h"
#include "Utils/GCSUtils.h"


QtTcpTelemetryWorker::QtTcpTelemetryWorker(QHostAddress::SpecialAddress InAddress, uint16_t InPort)
	: m_pServer(nullptr)
	, m_pClientTcpSocket(nullptr)
	, m_CachedBuffer({})
	, m_eAddress(InAddress)
	, m_uPort(InPort)
{

}

void QtTcpTelemetryWorker::Start()
{
	if (m_pServer)
	{
		emit Error(FUNCTION_MSG("TCP server is already running"));
		return;
	}

	m_pServer = new QTcpServer(this);
	QObject::connect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryWorker::OnNewConnection);
	if (!m_pServer->listen(m_eAddress, m_uPort))
	{
		emit Error(FUNCTION_MSG("Failed to start TCP telemetry server"));
		QObject::disconnect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryWorker::OnNewConnection);
		m_pServer->deleteLater();
		m_pServer = nullptr;
		return;
	}

	emit Started();
}

void QtTcpTelemetryWorker::Stop()
{
	if (m_pClientTcpSocket)
	{
		m_pClientTcpSocket->disconnectFromHost();
		m_pClientTcpSocket->deleteLater();
		m_pClientTcpSocket = nullptr;
	}

	QObject::disconnect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryWorker::OnNewConnection);
	if (m_pServer)
	{
		m_pServer->close();
		m_pServer->deleteLater();
		m_pServer = nullptr;
	}

	m_CachedBuffer.clear();
	emit Stopped();
}

void QtTcpTelemetryWorker::OnNewConnection()
{
	if (!m_pServer)
	{
		emit Error(FUNCTION_MSG("Invalid TCP server"));
		return;
	}

	QTcpSocket* IncomingUAVSocket = m_pServer->nextPendingConnection();
	if (!IncomingUAVSocket)
	{
		emit Error(FUNCTION_MSG("Invalid TCP socket"));
		return;
	}

	//We only allow one telemetry client for now
	//Nice to have: handle multiple connections
	if (m_pClientTcpSocket)
	{
		emit Error(FUNCTION_MSG(" TCP Telemetry client already connected"));
		IncomingUAVSocket->disconnectFromHost();
		IncomingUAVSocket->deleteLater();
		return;
	}

	m_pClientTcpSocket = IncomingUAVSocket;
	QObject::connect(m_pClientTcpSocket, &QTcpSocket::readyRead, this, &QtTcpTelemetryWorker::OnReadyRead);
	QObject::connect(m_pClientTcpSocket, &QTcpSocket::disconnected, this, &QtTcpTelemetryWorker::OnDisconnected);
	QObject::connect(m_pClientTcpSocket, &QTcpSocket::errorOccurred, this, &QtTcpTelemetryWorker::OnTcpError);
}

void QtTcpTelemetryWorker::OnReadyRead()
{
	if (!m_pClientTcpSocket)
	{
		emit Error(FUNCTION_MSG("Invalid TCP socket"));
		return;
	}

	/*
		TCP is a stream, so readAll() does not necessarily contain
		one complete telemetry frame.

		Data is therefore accumulated in m_CachedBuffer.
	*/
	m_CachedBuffer.append(m_pClientTcpSocket->readAll());
	ProcessBuffer();
}

void QtTcpTelemetryWorker::OnDisconnected()
{
	if (m_pClientTcpSocket)
	{
		m_pClientTcpSocket->deleteLater();
		m_pClientTcpSocket = nullptr;
	}

	m_CachedBuffer.clear();
}

void QtTcpTelemetryWorker::OnTcpError(QAbstractSocket::SocketError SocketError)
{
	if (m_pClientTcpSocket)
	{
		emit Error(FUNCTION_MSG("Called"));
		emit Error(m_pClientTcpSocket->errorString());
	}
}

void QtTcpTelemetryWorker::ProcessBuffer()
{
	while (true)
	{
		// We need at least the header to know the payload size.
		if (m_CachedBuffer.size() < HeaderSize)
		{
			return;
		}

		QDataStream Stream(m_CachedBuffer);
		Stream.setByteOrder(QDataStream::BigEndian);

		uint32_t PayloadSize = 0;

		Stream >> PayloadSize;

		// Wait until the complete payload has arrived.
		if (m_CachedBuffer.size() < HeaderSize + static_cast<int>(PayloadSize))
		{
			return;
		}

		QByteArray Payload = m_CachedBuffer.mid(HeaderSize, PayloadSize);

		m_CachedBuffer.remove(0, HeaderSize + PayloadSize);
		emit TelemetryReceived(Payload);
	}
}
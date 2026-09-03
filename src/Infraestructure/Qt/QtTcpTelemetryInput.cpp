
#include "QtTcpTelemetryInput.h"
#include "application/Logs/LogManager.h"
#include "Utils/GCSUtils.h"
#include <sstream>


QtTcpTelemetryInput::~QtTcpTelemetryInput()
{
	/*Stop();*/
}

void QtTcpTelemetryInput::Start()
{
	if (!m_bIsCallbcackSet)
	{
		GCSLog::GetInstance().Log(ELogLevel::Warning, FUNCTION_MSG(" Callback is not set in telemetry input"));
	}

	m_pServer = new QTcpServer(this);

	QObject::connect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryInput::OnNewConnection);

	if (!m_pServer->listen(Address, Port))
	{
		stringstream WarningMessage; 
		WarningMessage << " Failed to start TCP telemetry server: " /*<< m_pServer->errorString()*/;
		GCSLog::GetInstance().Log(ELogLevel::Warning, WarningMessage.str());
		QObject::disconnect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryInput::OnNewConnection);
		return;
	}

	stringstream Message;
	Message << "TCP telemetry server listening on port " << Port;
	GCSLog::GetInstance().Log(ELogLevel::Info, Message.str());
}

void QtTcpTelemetryInput::Stop()
{
	if (m_pClientTcpSocket)
	{
		m_pClientTcpSocket->disconnectFromHost();
		m_pClientTcpSocket->deleteLater();
		m_pClientTcpSocket = nullptr;
	}

	if (m_pServer)
	{
		m_pServer->close();
		m_pServer->deleteLater();
		m_pServer = nullptr;
	}
	QObject::disconnect(m_pServer, &QTcpServer::newConnection, this, &QtTcpTelemetryInput::OnNewConnection);
	m_CachedBuffer.clear();
	m_bIsCallbcackSet = false;
}

void QtTcpTelemetryInput::SetTelemetryCallback(OnTelemetryReceivedCallback Callback)
{
	m_Callback = Callback;
	m_bIsCallbcackSet = true;
}

void QtTcpTelemetryInput::OnNewConnection()
{
	if (!m_pServer)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG(" Invalid TCP server"));
		return;
	}

	QTcpSocket* IncomingUAVSocket = m_pServer->nextPendingConnection();
	if (!IncomingUAVSocket)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG(" Invalid TCP socket"));
		return;
	}

	//We only allow one telemetry client for now
	//Nice to have: handle multiple connections
	if (m_pClientTcpSocket)
	{
		GCSLog::GetInstance().Log(ELogLevel::Warning, FUNCTION_MSG(" TCP Telemetry client already connected"));
		IncomingUAVSocket->disconnectFromHost();
		IncomingUAVSocket->deleteLater();
		return;
	}

	m_pClientTcpSocket = IncomingUAVSocket;
	QObject::connect(m_pClientTcpSocket, &QTcpSocket::readyRead, this, &QtTcpTelemetryInput::OnReadyRead);
	QObject::connect(m_pClientTcpSocket, &QTcpSocket::disconnected, this, &QtTcpTelemetryInput::OnDisconnected);

	stringstream Message;
	Message << " Telemetry client connected from" /*<< m_pClientTcpSocket->peerAddress().toString() << m_pClientTcpSocket->peerPort()*/;
	GCSLog::GetInstance().Log(ELogLevel::Info, Message.str());
}

void QtTcpTelemetryInput::OnReadyRead()
{
	if (m_pClientTcpSocket)
	{
		GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG(" Invalid TCP socket"));
		return;
	}

	//We can't assure readAll() has the entire and completed datagram
	//We cache the pieces and we'll call the callback when It's done
	m_CachedBuffer.append(m_pClientTcpSocket->readAll());
	ProcessBuffer();
}

void QtTcpTelemetryInput::OnDisconnected()
{
	GCSLog::GetInstance().Log(ELogLevel::Info, FUNCTION_MSG(" Telemetry client disconnected"));
	if (m_pClientTcpSocket)
	{
		m_pClientTcpSocket->deleteLater();
		m_pClientTcpSocket = nullptr;
	}

	m_CachedBuffer.clear();
}

void QtTcpTelemetryInput::ProcessBuffer()
{
	while (true)
	{
		// We need at least  bytes to know the payload size.
		if (m_CachedBuffer.size() < HeaderSize)
		{
			return;
		}

		QDataStream stream(m_CachedBuffer);
		stream.setByteOrder(QDataStream::BigEndian);

		uint32_t PayloadSize = 0;
		stream >> PayloadSize;

		// Wait until the complete payload has arrived.
		if (m_CachedBuffer.size() < HeaderSize + PayloadSize)
		{
			return;
		}

		QByteArray Payload = m_CachedBuffer.mid(HeaderSize, PayloadSize);
		m_CachedBuffer.remove(0, HeaderSize + PayloadSize);

		if (m_Callback)
		{
			std::vector<uint8_t> Data(
				reinterpret_cast<const uint8_t*>(Payload.constData()),
				reinterpret_cast<const uint8_t*>(Payload.constData())
				+ Payload.size());

			m_Callback(Data);
		}
	}
}



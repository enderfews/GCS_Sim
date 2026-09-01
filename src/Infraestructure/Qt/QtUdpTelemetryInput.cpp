
#include "QtUdpTelemetryInput.h"
#include <QUdpSocket>
#include <QNetworkDatagram>


void QtUdpTelemetryInput::Start()
{
	if (!m_bIsCallbcackSet)
	{
		//TODO: Display Warning Error
	}

	m_pUdpSocket = new QUdpSocket(this);
	const bool UdpOk = m_pUdpSocket->bind(QHostAddress::Any, 5000);

	if (!UdpOk)
	{
		//TODO: Display Errors
	}

	QObject::connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &QtUdpTelemetryInput::receiveUdpDatagram);
}

void QtUdpTelemetryInput::Stop()
{
	QObject::disconnect(m_pUdpSocket, &QUdpSocket::readyRead, this, &QtUdpTelemetryInput::receiveUdpDatagram);
	m_bIsCallbcackSet = false;
	delete m_pUdpSocket;
}

void QtUdpTelemetryInput::SetTelemetryCallback(OnTelemetryReceivedCallback Callback)
{
	m_CachedCallback = Callback;
	m_bIsCallbcackSet = true;
}

void QtUdpTelemetryInput::receiveUdpDatagram()
{
	if (!m_bIsCallbcackSet)
	{
		//TODO: Display Errors
		return;
	}
	// Fetch the full datagram: raw bytes and metadata
	QNetworkDatagram datagram = m_pUdpSocket->receiveDatagram();

	// Extract only the raw bytes from the datagram, ignoring metadata.
	QByteArray Payload = datagram.data();
	// Bytes are not text by themselves — explicitly decode them
	// as UTF-8 characters to get a readable QString.
}
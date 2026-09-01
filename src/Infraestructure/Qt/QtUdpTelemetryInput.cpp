
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

const vector<uint8_t>& QtUdpTelemetryInput::GetCachedRawTelemetryData() const
{
	return m_CachedRawData;
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
	QByteArray QPayload = datagram.data();
	//We get the bytes in this format so it doesn't rely on Qt nor other implementations
	m_CachedRawData.clear();
	m_CachedRawData.insert(m_CachedRawData.end(), QPayload.begin(), QPayload.end());
	m_CachedCallback(m_CachedRawData);


}
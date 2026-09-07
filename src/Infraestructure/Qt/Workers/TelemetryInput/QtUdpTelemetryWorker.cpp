
#include "QtUdpTelemetryWorker.h"
#include <QByteArray>
#include <QNetworkDatagram>

QtUdpTelemetryWorker::QtUdpTelemetryWorker(QHostAddress::SpecialAddress InAddress, uint16_t InPort)
	: m_pUdpSocket(nullptr)
	, m_eAddress(InAddress)
	, m_uPort(InPort)
{
}

void QtUdpTelemetryWorker::Start()
{
	m_pUdpSocket = new QUdpSocket(this);
	const bool UdpOk = m_pUdpSocket->bind(m_eAddress, m_uPort);
	if (!UdpOk)
	{
		emit Error("Binding to address and port failed");
		m_pUdpSocket->deleteLater();
		m_pUdpSocket = nullptr;
		return;
	}

	QObject::connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &QtUdpTelemetryWorker::receiveUdpDatagram);
	emit Started();
}

void QtUdpTelemetryWorker::Stop()
{
	QObject::disconnect(m_pUdpSocket, &QUdpSocket::readyRead, this, &QtUdpTelemetryWorker::receiveUdpDatagram);
	m_pUdpSocket->close();
	m_pUdpSocket->deleteLater();
	m_pUdpSocket = nullptr;
	emit Stopped();
}
void QtUdpTelemetryWorker::receiveUdpDatagram()
{
	// Fetch the full datagram: raw bytes and metadata
	QNetworkDatagram datagram = m_pUdpSocket->receiveDatagram();
	// Extract only the raw bytes from the datagram, ignoring metadata.
	QByteArray QPayload = datagram.data();
	emit UdpDatagramReceived(QPayload);
}


#pragma once

#include <QObject>
#include <QUdpSocket>
#include <cstdint>
#include <QHostAddress>
/*
    @brief Worker that handles UDP telemetry reception inside a dedicated thread.
*/
class QtUdpTelemetryWorker
    : public QObject
{
    Q_OBJECT

public:

	QtUdpTelemetryWorker(QHostAddress::SpecialAddress InAddress, uint16_t InPort);

public slots:
	//Slots to bind to start/stop thread signal
	void Start();
	void Stop();

signals:
	//Signal to send the datagram from the worker thread to 
	void UdpDatagramReceived(const QByteArray& Data);
	//Signal called inside Start()
	void Started();
	//Signal called inside Stop()
	void Stopped();
	//Send error messages from the thread to the main thread to print it to the GCSLog
	void Error(const QString& Message);

private:
	QUdpSocket* m_pUdpSocket = nullptr;
	uint16_t m_uPort;
	QHostAddress::SpecialAddress m_eAddress;
private slots:

	//Slot function to handle incoming UDP data from the socket
	void receiveUdpDatagram();
};
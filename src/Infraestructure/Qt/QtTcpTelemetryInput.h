
#pragma once

#include "domain/TelemetryInput.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <cstdint>
#include <vector>

class QByteArray;
/*
	@brief Telemetry input port implementation that uses Qt network (TCP)
*/
class QtTcpTelemetryInput
	: public QObject
	, public ITelemetryInput
{
	Q_OBJECT

public:

	virtual ~QtTcpTelemetryInput() override;

	void Start() override;
	void Stop() override;
	void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) override;

private slots:
	// Slot function to handle TCP server signal
	void OnNewConnection();
	//Slot functions to handle TCP socket signals
	void OnReadyRead();
	void OnDisconnected();
	void OnTcpError(QAbstractSocket::SocketError socketError);

private:

	void ProcessBuffer();

	QTcpServer* m_pServer = nullptr;
	QTcpSocket* m_pClientTcpSocket = nullptr;
	bool m_bIsCallbcackSet = false;
	OnTelemetryReceivedCallback m_Callback;
	QByteArray m_CachedBuffer;
	static constexpr int Port = 5000;
	static constexpr int HeaderSize = 4;
	static constexpr QHostAddress::SpecialAddress Address = QHostAddress::AnyIPv4;
};
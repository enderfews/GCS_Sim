
#pragma once

#include "domain/TelemetryInput.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <cstdint>
#include <vector>

class QThread;
class QByteArray;
class QtTcpTelemetryWorker;


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

	void OnTelemetryReceived(const QByteArray& Data);

	//Slots to bind into the worker
	void OnWorkerStarted();
	void OnWorkerStopped();
	void OnWorkerError(const QString& Message);

private:

	QTcpServer* m_pServer = nullptr;
	QTcpSocket* m_pClientTcpSocket = nullptr;
	QThread* m_pInputThread = nullptr;
	QtTcpTelemetryWorker* m_pWorker = nullptr;
	bool m_bIsCallbcackSet = false;
	OnTelemetryReceivedCallback m_Callback;
	static constexpr int Port = 5000;
	static constexpr QHostAddress::SpecialAddress Address = QHostAddress::AnyIPv4;
};

#pragma once

#include "domain/TelemetryInput.h"
#include <QObject>
#include <QUdpSocket>
#include <vector>

class QThread;
class QByteArray;
class QtUdpTelemetryWorker;

using namespace std;

class QtUdpTelemetryInput
	: public QObject
	, public ITelemetryInput
{
	Q_OBJECT
public:
	virtual ~QtUdpTelemetryInput() override;

	virtual void Start() override;
	virtual void Stop() override;
	virtual void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) override;

private slots:

	void OnDatagramReceived(const QByteArray& Data);

	//Slots to bind into the worker
	void OnWorkerStarted();
	void OnWorkerStopped();
	void OnWorkerError(const QString& Message);
private:
	bool m_bIsCallbcackSet = false;
	OnTelemetryReceivedCallback m_CachedCallback;
	QtUdpTelemetryWorker* m_pWorker = nullptr;
	QThread* m_pInputThread = nullptr;
	vector<uint8_t> m_CachedRawData;

	static const int Port = 5000;
	static const QHostAddress::SpecialAddress Address = QHostAddress::LocalHost;
};

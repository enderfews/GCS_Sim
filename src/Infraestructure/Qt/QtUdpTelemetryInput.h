
#pragma once

#include "domain/TelemetryInput.h"
#include <QObject>
class QUdpSocket;


class QtUdpTelemetryInput
	: public QObject
	, public ITelemetryInput
{
	Q_OBJECT
public:
	virtual void Start() override;
	virtual void Stop() override;
	virtual void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) override;

private:
	bool m_bIsCallbcackSet = false;
	OnTelemetryReceivedCallback m_CachedCallback;
	QUdpSocket* m_pUdpSocket = nullptr;

private slots:

	//Slot function to handle incoming UDP data 
	void receiveUdpDatagram();
};


#pragma once

#include "domain/TelemetryInput.h"
#include <QObject>
#include <QUdpSocket>
#include <vector>
class QUdpSocket;

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
	virtual const vector<uint8_t>& GetCachedRawTelemetryData() const override;

private:
	bool m_bIsCallbcackSet = false;
	OnTelemetryReceivedCallback m_CachedCallback;
	QUdpSocket* m_pUdpSocket = nullptr;
	vector<uint8_t> m_CachedRawData;

	static const int Port = 5000;
	static const QHostAddress::SpecialAddress Address = QHostAddress::LocalHost;
private slots:

	//Slot function to handle incoming UDP data 
	void receiveUdpDatagram();
};

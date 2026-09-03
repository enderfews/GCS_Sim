
#pragma once

#include "domain/TelemetryDecoder.h"
#include <QObject>
#include <vector>

struct UAVState;
using namespace std;

class QtTcpTelemetryDecoder
	: public QObject
	, public ITelemetryDecoder
{
	Q_OBJECT

public:

	virtual bool Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState) override;

private:
	static float ReadFloatBE(const uint8_t* Data);

	static constexpr size_t PacketSize = 61;
};
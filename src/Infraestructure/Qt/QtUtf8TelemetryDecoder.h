
#pragma once

#include "domain/TelemetryDecoder.h"
#include <QObject>
#include <vector>

struct UAVState;
using namespace std;

class QtUtf8TelemetryDecoder
	: public QObject
	, public ITelemetryDecoder
{
	Q_OBJECT

public:

	virtual bool Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState) override;
};
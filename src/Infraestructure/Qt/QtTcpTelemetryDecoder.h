
#pragma once

#include "domain/TelemetryDecoder.h"
#include <QObject>
#include <vector>

struct UAVState;
using namespace std;

/*
* @brief ITelemetryDecoder implementation of Qt for TCP
*/
class QtTcpTelemetryDecoder
	: public QObject
	, public ITelemetryDecoder
{
	Q_OBJECT

public:
	/*
	* @brief Decodes the incoming raw data and transforms it into UAVState data struct.
	* @param EncodedData - A vector reference of bytes that represents the received data
	* @param OutUAVState - an output reference that returns the decoded data into a struct format
	*/
	virtual bool Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState) override;

private:
	static float ReadFloatBE(const uint8_t* Data);

	static constexpr size_t PackageSize = 61;
};
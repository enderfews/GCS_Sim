#include "QtUtf8TelemetryDecoder.h"
#include "domain/UAV_Types.h"



bool QtUtf8TelemetryDecoder::Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState)
{
	QString ReceivedMessage = QString::fromUtf8(EncodedData);
	QStringList Data = ReceivedMessage.split(",");
	//TODO
	return false;
}

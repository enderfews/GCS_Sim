#include "QtUtf8TelemetryDecoder.h"
#include "domain/UAV_Types.h"



bool QtUtf8TelemetryDecoder::Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState)
{
	//QString ReceivedMessage = QString::fromUtf8(EncodedData);
	//QStringList Data = ReceivedMessage.split(",");
	
    constexpr size_t ExpectedSize = 57;

    if (EncodedData.size() != ExpectedSize)
    {
        return false;
    }

    size_t offset = 0;

    auto readFloat =
        [&EncodedData, &offset]() -> float
        {
            float value;

            std::memcpy(
                &value,
                EncodedData.data() + offset,
                sizeof(float));

            offset += sizeof(float);

            return value;
        };


    OutUAVState.position.latitude = readFloat();
    OutUAVState.position.longitude = readFloat();
    OutUAVState.position.altitude = readFloat();
    OutUAVState.attitude.roll = readFloat();
    OutUAVState.attitude.pitch = readFloat();
    OutUAVState.attitude.yaw = readFloat();
    OutUAVState.velocity.north = readFloat();
    OutUAVState.velocity.east = readFloat();
    OutUAVState.velocity.down = readFloat();
    OutUAVState.battery.voltage = readFloat();
    OutUAVState.battery.current = readFloat();
    OutUAVState.battery.percentage = readFloat();
    OutUAVState.groundSpeed = readFloat();
    OutUAVState.airSpeed = readFloat();
    OutUAVState.gpsValid = EncodedData[offset] != 0;

	return true;
}


#include "QtTcpTelemetryDecoder.h"

bool QtTcpTelemetryDecoder::Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState)
{
    if (Data.size() != PacketSize)
    {
        return false;
    }

    std::size_t Offset = 0;

    // -------------------------
    // Position
    // -------------------------

    OutUAVState.position.latitude =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.position.longitude =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.position.altitude =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);


    // -------------------------
    // Attitude
    // -------------------------

    OutUAVState.attitude.roll =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.attitude.pitch =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.attitude.yaw =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);


    // -------------------------
    // Velocity
    // -------------------------

    OutUAVState.velocity.north =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.velocity.east =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.velocity.down =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);


    // -------------------------
    // Battery
    // -------------------------

    OutUAVState.battery.voltage =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.battery.current =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.battery.percentage =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);


    // -------------------------
    // Speed
    // -------------------------

    OutUAVState.groundSpeed =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);

    OutUAVState.airSpeed =
        ReadFloatBE(EncodedData.data() + Offset);

    Offset += sizeof(float);


    // -------------------------
    // GPS
    // -------------------------

    OutUAVState.gpsValid = EncodedData[Offset] != 0;

    return true;
}

float QtTcpTelemetryDecoder::ReadFloatBE(const uint8_t* Data)
{
    uint32_t Value =
        (static_cast<uint32_t>(Data[0]) << 24) |
        (static_cast<uint32_t>(Data[1]) << 16) |
        (static_cast<uint32_t>(Data[2]) << 8) |
        static_cast<uint32_t>(Data[3]);

    float Result;

    std::memcpy(
        &Result,
        &Value,
        sizeof(float));

    return Result;
}

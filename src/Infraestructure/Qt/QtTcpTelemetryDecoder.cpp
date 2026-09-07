
#include "QtTcpTelemetryDecoder.h"
#include "domain/UAV_Types.h"
#include "application/Logs/LogManager.h"
#include "Utils/GCSUtils.h"

bool QtTcpTelemetryDecoder::Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState)
{
    /*
    * We are receiving 14 floats and 1 bool. Each float has a size of 4 bytes, so
    * we need to use its size as offset to process each 4 bytes and make the float.
    * ReadFloatBE is a helper function that process the next 4 bytes to return the 
    * given float.
    */
    std::size_t Offset = 0;

    // -------------------------
    // Position
    // -------------------------
    OutUAVState.position.latitude = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.position.longitude = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.position.altitude = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);


    // -------------------------
    // Attitude
    // -------------------------
    OutUAVState.attitude.roll = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.attitude.pitch = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.attitude.yaw = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);


    // -------------------------
    // Velocity
    // -------------------------
    OutUAVState.velocity.north = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.velocity.east = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.velocity.down = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);


    // -------------------------
    // Battery
    // -------------------------
    OutUAVState.battery.voltage = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.battery.current = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.battery.percentage = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);


    // -------------------------
    // Speed
    // -------------------------
    OutUAVState.groundSpeed = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);
    OutUAVState.airSpeed = ReadFloatBE(EncodedData.data() + Offset);
    Offset += sizeof(float);


    // -------------------------
    // GPS
    // -------------------------
    OutUAVState.gpsValid = EncodedData[Offset] != 0;

    return true;
}

float QtTcpTelemetryDecoder::ReadFloatBE(const uint8_t* Data)
{
    /*
    * Expecting an array, Data[0] Data[1] Data[2] Data[3] are
    * the bytes that compose the float. Left shift each byte
    * and then perform bitwise OR to combine all of them
    */
    uint32_t Value =
        (static_cast<uint32_t>(Data[0]) << 24) | // left shift 3 times. 24 = 8 bits (byte) * 3
        (static_cast<uint32_t>(Data[1]) << 16) | // left shift 2 times. 16 = 8 bits (byte) * 2
        (static_cast<uint32_t>(Data[2]) << 8) | // left shift 1 time. 8 = 8 bits (byte) * 1
        static_cast<uint32_t>(Data[3]); // No left shift

    float Result;
    std::memcpy(&Result, &Value,sizeof(float));
    return Result;
}

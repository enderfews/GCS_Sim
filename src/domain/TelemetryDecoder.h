
#pragma once

#include <functional>
#include <vector>
struct UAVState;

using namespace std;
/*
* @brief Interface (Port) to decode telemetry data. Used by the TelemetryService class
*/
class ITelemetryDecoder
{
public:
    virtual ~ITelemetryDecoder() = default;
    /*
    * @brief Decodes the incoming raw data and transforms it into UAVState data struct
    * @param EncodedData - A vector reference of bytes that represents the received data
    * @param OutUAVState - an output reference that returns the decoded data into a struct format
    */
    virtual bool Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState) = 0;

    
};

#pragma once

#include <functional>
#include <vector>
struct UAVState;

using namespace std;
/*
Interface (Port) to decode telemetry data
*/
class ITelemetryDecoder
{
public:
    virtual ~ITelemetryDecoder() = default;
    virtual bool Decode(const vector<uint8_t>& EncodedData, UAVState& OutUAVState) = 0;

    
};
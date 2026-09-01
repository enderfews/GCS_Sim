
#pragma once

#include <functional>
struct UAVState;

using namespace std;
/*
Interface (Port) to decode telemetry data
*/
class ITelemetryDecoder
{
public:
    virtual ~ITelemetryDecoder() = default;
    virtual bool Decode(char* EncodedData, UAVState& OutUAVState) = 0;

    
};
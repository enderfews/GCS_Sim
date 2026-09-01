
#pragma once

#include <functional>
struct UAVState;

using namespace std;
/*
Interface (Port) to receive telemetry data periodically
*/
class ITelemetryInput
{
public:
    using OnTelemetryReceivedCallback = function<void(char*)>;

    virtual ~ITelemetryInput() = default;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) = 0;

    
};
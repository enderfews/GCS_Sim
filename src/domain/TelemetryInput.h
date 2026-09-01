
#pragma once

#include <functional>
#include <vector>
struct UAVState;

using namespace std;
/*
Interface (Port) to receive telemetry data periodically
*/
class ITelemetryInput
{
public:
    using OnTelemetryReceivedCallback = function<void(const vector<uint8_t>&)>;

    virtual ~ITelemetryInput() = default;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) = 0;
    virtual const vector<uint8_t>& GetCachedRawTelemetryData() const = 0;

    
};
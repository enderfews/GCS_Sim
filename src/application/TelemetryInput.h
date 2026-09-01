
#pragma once

struct UAVState;


/*
Interface (Port) to receive telemetry data
*/
class ITelemetryInput
{
public:
    virtual ~ITelemetryInput() = default;

    virtual void OnTelemetryDataReceived(UAVState& outUAVState) = 0;
    virtual void OnTelemetryConnected() = 0;
    virtual void OnTelemetryError() = 0;
};
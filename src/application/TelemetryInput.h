
#pragma once

struct UAVState;


/*
Interface (Port) to receive telemetry data
*/
class ITelemetryInput
{
public:
    virtual ~ITelemetryInput() = default;

    virtual void onTelemetry(UAVState& outUAVState) = 0;
};
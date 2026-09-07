
#pragma once

#include <functional>
#include <vector>
struct UAVState;

using namespace std;
/*
* @brief Interface (Port) to receive telemetry data periodically. Used by
* TelemetryService class, it gather the telemetry and sends it as a
* vector<uint8_t> in the callback
*/
class ITelemetryInput
{
public:
    using OnTelemetryReceivedCallback = function<void(const vector<uint8_t>&)>;

    virtual ~ITelemetryInput() = default;
    /*
    * @brief Starts listening for datagrams, called by the TelemetryService
    */
    virtual void Start() = 0;
    /*
    * @brief Stops listening for datagrams, called by the TelemetryService
    */
    virtual void Stop() = 0;
    /*
    * @brief Sets the callback used to provided the received datagrams
    */
    virtual void SetTelemetryCallback(OnTelemetryReceivedCallback Callback) = 0;

    
};
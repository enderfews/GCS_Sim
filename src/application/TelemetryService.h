
#pragma once

#include "domain/TelemetryInput.h"
#include "domain/TelemetryDecoder.h"
#include "domain/UAV_Types.h"

//struct TelemetryServiceCallback
//{
//	using TelemetryServiceCallbackType = function<void(UAVState&)>;
//public:
//	TelemetryServiceCallback(TelemetryServiceCallbackType Callback)
//		m_Callback(Callback)
//	{
//	}
//	TelemetryServiceCallbackType m_Callback;
//private:
//	bool m_IsCallbackSet;
//};

/*
	Telemetry Service in charge of receiving and decoding data to display
*/
class TelemetryService
{
	using OnTelemetryGatheredCallback = function<void(UAVState&)>;
public:
	TelemetryService(ITelemetryInput& Input, ITelemetryDecoder& Decoder);

	void SetTelemetryServiceCallback(OnTelemetryGatheredCallback Callback);
	void Start();
	void Stop();
	const UAVState& GetCurrentUAVState() const;

private:

	void OnTelemetryReceived(char* EncodedData);

	ITelemetryInput& m_Input;
	ITelemetryDecoder& m_Decoder;
	UAVState m_CachedState;

	OnTelemetryGatheredCallback m_TelemetryServiceGatheredCallback;
};
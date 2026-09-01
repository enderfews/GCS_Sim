
#include "TelemetryService.h"

TelemetryService::TelemetryService(ITelemetryInput& Input, ITelemetryDecoder& Decoder)
	: m_Input(Input)
	, m_Decoder(Decoder)
	, m_CachedState({})
{
	m_Input.SetTelemetryCallback([this](char* EncodedData)
		{
			OnTelemetryReceived(EncodedData);
		});
}

void TelemetryService::SetTelemetryServiceCallback(OnTelemetryGatheredCallback Callback)
{
	m_TelemetryServiceGatheredCallback = Callback;
}

void TelemetryService::Start()
{
	m_Input.Start();
}

void TelemetryService::Stop()
{
	m_Input.Stop();
}

const UAVState& TelemetryService::GetCurrentUAVState() const
{
	return m_CachedState;
}

void TelemetryService::OnTelemetryReceived(char* EncodedData)
{
	if (!m_Decoder.Decode(EncodedData, m_CachedState))
	{
		//TODO: Display error log
		return;
	}

	if(!m_TelemetryServiceGatheredCallback)
	{
		//TODO: Display error log
		return;
	}

	m_TelemetryServiceGatheredCallback(m_CachedState);
}

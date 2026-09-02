
#pragma once

#include "domain/TelemetryInput.h"
#include "domain/TelemetryDecoder.h"
#include "domain/UAV_Types.h"
#include <vector>
#include <memory>
using namespace std;

/*
	Telemetry Service in charge of receiving and decoding data to display
*/
template<class InputClass, class DecoderClass>
class TelemetryService
{
	using OnTelemetryGatheredCallback = function<void(UAVState&)>;
	static_assert(is_base_of_v<ITelemetryInput, InputClass>, "TelemetryService::InitializeTelemetryInput - InputClass must inherit from ITelemetryInput");
	static_assert(is_base_of_v<ITelemetryDecoder, DecoderClass>, "TelemetryService::InitializeTelemetryDecoder - DecoderClass must inherit from ITelemetryDecoder");

public:
	TelemetryService()
		: m_Input(nullptr)
		, m_Decoder(nullptr)
		, m_CachedState({})
	{
		InitializeTelemetryInput<InputClass>();
		InitializeTelemetryDecoder<DecoderClass>();
	}
	~TelemetryService()
	{
		ShutdownTelemetryInput();
		ShutdownTelemetryDecoder();
	}
	void SetTelemetryServiceCallback(OnTelemetryGatheredCallback Callback)
	{
		m_TelemetryServiceGatheredCallback = Callback;
	}

	void Start()
	{
		if (m_bHasStarted)
		{
			return;
		}

		if (!m_Input)
		{
			//TODO: Display error message
			return;
		}
		m_Input->Start();
		m_bHasStarted = true;
	}

	void Stop()
	{
		if (!m_bHasStarted)
		{
			return;
		}

		if (!m_Input)
		{
			//TODO: Display error message
			return;
		}
		m_Input->Stop();
		m_bHasStarted = false;
	}

	const UAVState& GetCurrentUAVState() const
	{
		return m_CachedState;
	}

	template<class InClass>
	void InitializeTelemetryInput()
	{
		static_assert(is_base_of_v<ITelemetryInput, InClass>, "TelemetryService::InitializeTelemetryInput - InputClass must inherit from ITelemetryInput");
		if (m_Input)
		{
			m_Input->Stop();
			m_Input.reset();
		}

		m_Input = make_unique<InClass>();
		m_Input->SetTelemetryCallback([this](const vector<uint8_t>& EncodedData)
			{
				OnTelemetryReceived(EncodedData);
			});
		if (m_bHasStarted)
		{
			m_Input->Start();
		}
	}

	void ShutdownTelemetryInput()
	{
		Stop();
		m_Input.reset();
	}
	template<class DecClass>
	void InitializeTelemetryDecoder()
	{
		static_assert(is_base_of_v<ITelemetryDecoder, DecClass>, "TelemetryService::InitializeTelemetryDecoder - DecoderClass must inherit from ITelemetryDecoder");
		if (m_Decoder)
		{
			m_Decoder.reset();
		}

		m_Decoder = make_unique<DecClass>();
	}
	
	void ShutdownTelemetryDecoder()
	{
		m_Decoder.reset();
	}


private:

	void OnTelemetryReceived(const vector<uint8_t>& EncodedData)
	{
		if (!m_Decoder)
		{
			//TODO: Display error message
			return;
		}

		if (!m_Decoder->Decode(EncodedData, m_CachedState))
		{
			//TODO: Display error log
			return;
		}

		if (!m_TelemetryServiceGatheredCallback)
		{
			//TODO: Display error log
			return;
		}

		m_TelemetryServiceGatheredCallback(m_CachedState);
	}

	unique_ptr<ITelemetryInput> m_Input;
	unique_ptr<ITelemetryDecoder> m_Decoder;
	UAVState m_CachedState;
	bool m_bHasStarted = false;
	OnTelemetryGatheredCallback m_TelemetryServiceGatheredCallback;
};

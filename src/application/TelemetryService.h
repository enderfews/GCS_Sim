
#pragma once

#include "domain/TelemetryInput.h"
#include "domain/TelemetryDecoder.h"
#include "domain/UAV_Types.h"
#include <vector>
#include <memory>
#include "application/Logs/LogManager.h"
#include "Utils/GCSUtils.h"
using namespace std;

/*
	@brief Telemetry Service in charge of receiving and decoding data to display.
	This class uses 2 ports to work, ITelemetryInput and ITelemetryDecoder. The first
	one listens for telemetry data and the second one decodes the received one. 
	Example to use:

		TelemetryService pTelemetryService = new TelemetryService();
		pTelemetryService->InitializeTelemetryInput<QtMyTelemetryInputImplementation>();
		pTelemetryService->InitializeTelemetryDecoder<QtMyTelemetryImplementation>();
		pTelemetryService->SetTelemetryServiceCallback([this](UAVState& State)
			{
				OnTelemetryReceived(State);
			});
		pTelemetryService->Start();
*/
class TelemetryService
{
	using OnTelemetryGatheredCallback = function<void(UAVState&)>;

public:
	TelemetryService()
		: m_Input(nullptr)
		, m_Decoder(nullptr)
		, m_CachedState({})
	{
	}
	~TelemetryService()
	{
		ShutdownTelemetryInput();
		ShutdownTelemetryDecoder();
	}
	/*
		@brief Function to set the callback on the service when the telemetry
		has been received and decoded sucessfully
	*/
	void SetTelemetryServiceCallback(OnTelemetryGatheredCallback Callback)
	{
		m_TelemetryServiceGatheredCallback = Callback;
	}

	/*
		@Brief Starts the telemetry service to listen and decode data.
		NOTE: DO NOT FORGET TO call Initialize functions to initialize the ports with their adapters
	*/
	void Start()
	{
		if (m_bHasStarted)
		{
			return;
		}

		if (!m_Input)
		{
			GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Failed to start. Invalid telemetry input"));
			return;
		}
		m_Input->Start();
		m_bHasStarted = true;
	}

	/*
	@Brief Stops the telemetry service to listen and decode data.
	NOTE: DO NOT FORGET TO call Initialize functions to initialize the ports with their adapters
*/
	void Stop()
	{
		if (!m_bHasStarted)
		{
			return;
		}

		if (!m_Input)
		{
			GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Failed to stop. Invalid telemetry input"));
			return;
		}
		m_Input->Stop();
		m_bHasStarted = false;
	}

	/*
		@brief Get the last cached UAV state
		@return - A reference to the UAV state data
	*/
	const UAVState& GetCurrentUAVState() const
	{
		return m_CachedState;
	}

	/*
		@brief Initialize the telemetry input port. Provide the adapter or class
		that implements ITelemetryInput, if not, it will throw compile errors. You
		can initialize on runtime a different adapter, It will stop the previous adapter
		or implementation, destroy it and initialize the new one.
	*/
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

	/*
	@brief Shuts down and stops the telemetry input port
	*/
	void ShutdownTelemetryInput()
	{
		Stop();
		m_Input.reset();
	}

	/*
	@brief Initialize the telemetry decoder port. Provide the adapter or class
	that implements ITelemetryDecoder, if not, it will throw compile errors. You
	can initialize on runtime a different adapter, It will stop the previous adapter
	or implementation, destroy it and initialize the new one.
	*/
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
			GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Invalid telemetry decoder"));
			return;
		}

		if (!m_Decoder->Decode(EncodedData, m_CachedState))
		{
			GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("Failed to decode"));
			return;
		}

		if (!m_TelemetryServiceGatheredCallback)
		{
			GCSLog::GetInstance().Log(ELogLevel::Error, FUNCTION_MSG("No callback bound"));
			return;
		}

		GCSLog::GetInstance().Log(ELogLevel::Info, FUNCTION_MSG("Telemetry received and decoded successfully"));
		m_TelemetryServiceGatheredCallback(m_CachedState);
	}

	unique_ptr<ITelemetryInput> m_Input;
	unique_ptr<ITelemetryDecoder> m_Decoder;
	UAVState m_CachedState;
	bool m_bHasStarted = false;
	OnTelemetryGatheredCallback m_TelemetryServiceGatheredCallback;
};

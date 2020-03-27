#pragma once

#include "gcroot.h"
#include <tchar.h>
#include <windows.h>
#include <vcclr.h>
#include <string>
#include <list>
#include <vector>

using namespace std;
using namespace System;
using namespace LumX_NetFramework_API_Wrapper;

namespace LumXCPPCLIAPIWrapper
{
	ref class CallbacksHelperClass
	{
	public:
		CallbacksHelperClass(void (CALLBACK* updateStatusCallback)(int severity, int errorCode, wstring status),
			void (CALLBACK* deliverCommandFromCloudCallback)(wstring str, std::list<wstring> params))
		{
			m_updateStatusCallback = updateStatusCallback;
			m_deliverCommandFromCloudCallback = deliverCommandFromCloudCallback;
		}

		void UpdateStatus(int severity, int errorCode, String^ status)
		{
			pin_ptr<const _TCHAR> _tStatus = PtrToStringChars(status);

			m_updateStatusCallback(severity, errorCode, _tStatus);
		}

		void DeliverCommandFromCloud(String^ commandName, cli::array<String^>^ params)
		{
			pin_ptr<const _TCHAR> _tCommandName = PtrToStringChars(commandName);

			std::list<wstring> l;

			if (params != nullptr)
			{
				for each (String ^ var in params)
				{
					pin_ptr<const _TCHAR> s = PtrToStringChars(var);
					wstring ws(s);
					l.push_back(ws);
				}
			}

			m_deliverCommandFromCloudCallback(_tCommandName, l);
		}

	private:
		void (*m_updateStatusCallback)(int severity, int errorCode, wstring str);
		void (*m_deliverCommandFromCloudCallback)(wstring str, std::list<wstring> params);
	};

	class LumX_API_CLI_Wrapper
	{
		friend class LumX_API_Native_CLI_Wrapper;

	public:
		LumX_API_CLI_Wrapper(wstring keysDictionaryFileName,
			void (CALLBACK* updateStatusCallback)(int severity, int errorCode, wstring status),
			void (CALLBACK* deliverCommandFromCloudCallback)(wstring str, std::list<wstring> params),
			wstring applicationVersion, wstring customMessage);

		~LumX_API_CLI_Wrapper();

		void SendEvent(wstring key, wstring value);

		void SendCommand(wstring commandName, wstring commandParams[], int commandParamsLength);

		void SetStateIdle();

		void SetStateActive();

		int GetState();
		
		static void CleanUp();

		static vector<wstring> GeoHelper_GetRegions();

		static vector<wstring> GeoHelper_GetCountriesPerRegion(wstring region);

		static vector<wstring> GeoHelper_GetStatesOfUSA();

		static void SetDeviceSelfActivationPropertyValue(wstring value, int fieldID);

		static bool IsSelfActivationDataValid(int& deviceActivation);

		static void ExecuteDeviceSelfActivation();

	private:
		gcroot<LumXNetFrameworkWrapper^> m_lumX_API_Wrapper;

		gcroot<CallbacksHelperClass^> m_callbacksHelper;
	};
}

#pragma once

#include <string>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <list>
#include <vector>

using namespace std;

#ifdef LUMX_CPPCLI_API_WRAPPER_EXPORTS
#define LUMX_CPPCLI_API_WRAPPER_API __declspec(dllexport)
#else
#define LUMX_CPPCLI_API_WRAPPER_API __declspec(dllimport)
#endif

namespace LumXCPPCLIAPIWrapper
{
	class LumX_API_CLI_Wrapper;

	class LUMX_CPPCLI_API_WRAPPER_API LumX_API_Native_CLI_Wrapper
	{

	public:
		LumX_API_Native_CLI_Wrapper(wstring keysDictionaryFileName,
			void (CALLBACK* updateStatusCallback)(int severity, int errorCode, wstring status),
			void (CALLBACK* deliverCommandFromCloudCallback)(wstring str, std::list<wstring> params),
			wstring applicationVersion, wstring customMessage);

		~LumX_API_Native_CLI_Wrapper();

		void SendEvent(wstring key, wstring value);

		void SendCommand(wstring, wstring commandParams[], int commandParamsLength);

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
		LumX_API_CLI_Wrapper* m_lumxAPI_CLIWrapper;
	};
}

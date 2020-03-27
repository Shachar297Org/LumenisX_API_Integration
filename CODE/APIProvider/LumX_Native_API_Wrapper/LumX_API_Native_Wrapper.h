#pragma once

#ifdef LUMX_API_NATIVE_WRAPPER_EXPORTS
#define LUMX_API_NATIVE_WRAPPER_API __declspec(dllexport)
#else
#define LUMX_API_NATIVE_WRAPPER_API __declspec(dllimport)
#endif

#include <string>
#include "..\\LumX_CPP_CLI_API_Wrapper\LumX_API_Native_CLI_Wrapper.h"
#include "..\\..\\LumXPlatformCommon\\LumXCommon\\LumXPlatformCommon.h"
using namespace LumXCommon;
using namespace std;

namespace LumXNativeAPINamespace
{
    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_Initialize(wstring keysDictionaryFileName,
        void (CALLBACK* updateStatusCallback)(int severity, int errorCode, wstring status),
        void (CALLBACK* deliverCommandFromCloudCallback)(wstring str, std::list<wstring> params),
        wstring applicationVersion, wstring customMessage);

    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_SendEvent(wstring key, wstring value);

    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_SendCommand(wstring commandName, wstring commandParams[], int commandParamsLength);

    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_SetStateIdle();
    
    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_SetStateActive();

    LUMX_API_NATIVE_WRAPPER_API LumXCommon::LumXPlatformState LumX_APIProvider_GetState();

    LUMX_API_NATIVE_WRAPPER_API wstring LumX_APIProvider_GetStateAsString();
    
    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_CleanUp();

    LUMX_API_NATIVE_WRAPPER_API vector<wstring> LumX_APIProvider_GeoHelper_GetRegions();

    LUMX_API_NATIVE_WRAPPER_API vector<wstring> LumX_APIProvider_GetCountriesPerRegion(wstring region);

    LUMX_API_NATIVE_WRAPPER_API vector<wstring> LumX_APIProvider_GeoHelper_GetStatesOfUSA();

    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_SetDeviceSelfActivationPropertyValue(wstring value,
        LumXCommon::DeviceActivationPropertyEnum fieldID);

    LUMX_API_NATIVE_WRAPPER_API bool LumX_APIProvider_IsSelfActivationDataValid(LumXCommon::DeviceActivationPropertyEnum& deviceActivation);

    LUMX_API_NATIVE_WRAPPER_API wstring LumX_APIProvider_GetSelfActivationValidityAsString(LumXCommon::DeviceActivationPropertyEnum deviceActivation);

    LUMX_API_NATIVE_WRAPPER_API void LumX_APIProvider_ExecuteDeviceSelfActivation();
}


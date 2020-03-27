// NativeWindows_API_Tester.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "NativeWindows_API_Tester.h"
#include "..\..\..\APIProvider\LumX_Native_API_Wrapper\LumX_API_Native_Wrapper.h"
#include "..\..\..\LumXPlatformCommon\LumXCommon\LumXPlatformCommon.h"

using namespace std;
using namespace LumXNativeAPINamespace;

#define MAX_LOADSTRING 100
#define MAX_STATUSSTRING 400

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWndMain;

TCHAR textStatus[MAX_STATUSSTRING];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SendEvent(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SendCommand(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NATIVEWINDOWSAPITESTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NATIVEWINDOWSAPITESTER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NATIVEWINDOWSAPITESTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NATIVEWINDOWSAPITESTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void UpdateStatusCallback(int severity, int errorCode, wstring status)
{
    LumXCommon::LumXStateUpdateSeverity sev = (LumXCommon::LumXStateUpdateSeverity)severity;
    wstring severityStr;
    switch (sev)
    {
    case LumXCommon::LumXStateUpdateSeverity::Information:
        severityStr = L"Information";
        break;
    case LumXCommon::LumXStateUpdateSeverity::Warning:
        severityStr = L"Warning";
        break;
    case LumXCommon::LumXStateUpdateSeverity::Error:
        severityStr = L"Error";
        break;
    case LumXCommon::LumXStateUpdateSeverity::Critical:
        severityStr = L"Critical";
        LumX_APIProvider_CleanUp();
        MessageBox(NULL, L"", L"Critical Error", MB_OK);
        DestroyWindow(hWndMain);
        break;
    }

    LumXCommon::LumXErrorCode eCode = (LumXCommon::LumXErrorCode)errorCode;
    wstring errorStr;
    switch (eCode)
    {
    case LumXCommon::LumXErrorCode::UNKNOWN:
        break;
    }

    wsprintf(textStatus, L"%s - %s", severityStr.c_str(), status.c_str());
    InvalidateRect(NULL, NULL, false);
}

void IncomingCommand(wstring commandName, std::list<wstring> paramsList)
{
    wstring commadDescr = commandName + L": ";

    for (wstring ws : paramsList)
    {
        commadDescr += ws + L" ";
    }

    if (paramsList.empty())
        commadDescr += L"No Parameters";

    wsprintf(textStatus, L"%s", commadDescr.c_str());
    InvalidateRect(NULL, NULL, false);
}

void SetStateIdle()
{
    LumX_APIProvider_SetStateIdle();
}

void SetStateActive()
{
    LumX_APIProvider_SetStateActive();
}

void TestGeo()
{
    vector<wstring> regions = LumX_APIProvider_GeoHelper_GetRegions();

    vector<wstring> USA_States = LumX_APIProvider_GeoHelper_GetStatesOfUSA();

    vector<wstring> countries = LumX_APIProvider_GetCountriesPerRegion(regions[0]);

    countries = LumX_APIProvider_GetCountriesPerRegion(regions[1]);
    countries = LumX_APIProvider_GetCountriesPerRegion(L"APAC");
}

void TestSA1()
{
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"fname",
        LumXCommon::DeviceActivationPropertyEnum::FirstName);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"lname",
        LumXCommon::DeviceActivationPropertyEnum::LastName);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"street",
        LumXCommon::DeviceActivationPropertyEnum::AddressStreet);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"123",
        LumXCommon::DeviceActivationPropertyEnum::AddressNumber);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"city",
        LumXCommon::DeviceActivationPropertyEnum::AddressCity);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"devicetype",
        LumXCommon::DeviceActivationPropertyEnum::DeviceType);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"NNN:NNN:NNN",
        LumXCommon::DeviceActivationPropertyEnum::DeviceSerialNumber);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"123456",
        LumXCommon::DeviceActivationPropertyEnum::PhoneNumber);
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"Americas",
        LumXCommon::DeviceActivationPropertyEnum::AddressRegion);
}

void TestSelfActivation()
{
    TestSA1();
    LumXCommon::DeviceActivationPropertyEnum deviceActivation = LumXCommon::DeviceActivationPropertyEnum::AllPropertiesOK;
    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"aa",
        LumXCommon::DeviceActivationPropertyEnum::EmailAddress);
    bool b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    wstring err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"aa@bb",
        LumXCommon::DeviceActivationPropertyEnum::EmailAddress);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"123456789012345",
        LumXCommon::DeviceActivationPropertyEnum::AddressZip);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"123456789012",
        LumXCommon::DeviceActivationPropertyEnum::AddressZip);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"Kanada",
        LumXCommon::DeviceActivationPropertyEnum::AddressCountry);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"Canada",
        LumXCommon::DeviceActivationPropertyEnum::AddressCountry);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"USA",
        LumXCommon::DeviceActivationPropertyEnum::AddressCountry);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"Balabama",
        LumXCommon::DeviceActivationPropertyEnum::AddressState);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    LumX_APIProvider_SetDeviceSelfActivationPropertyValue(L"Alabama",
        LumXCommon::DeviceActivationPropertyEnum::AddressState);
    b = LumX_APIProvider_IsSelfActivationDataValid(deviceActivation);
    err = LumX_APIProvider_GetSelfActivationValidityAsString(deviceActivation);

    int t = 0;

    //LumX_APIProvider_ExecuteDeviceSelfActivation();
}

void GetState()
{
    LumXCommon::LumXPlatformState state = LumX_APIProvider_GetState();

    int t = (int)state;
    switch (state)
    {
    case LumXCommon::LumXPlatformState::PlatformStateUNKNOWN:
        break;
    case LumXCommon::LumXPlatformState::Active:
        break;
    case LumXCommon::LumXPlatformState::ActiveSendingData:
        break;
    case LumXCommon::LumXPlatformState::ActiveUploading:
        break;
    case LumXCommon::LumXPlatformState::ActiveDownloading:
        break;
    case LumXCommon::LumXPlatformState::Idle:
        break;
    default:
        break;
    }

    wstring stateStr = LumX_APIProvider_GetStateAsString();
    wsprintf(textStatus, L"%d - %s", t, stateStr.c_str());
    InvalidateRect(NULL, NULL, false);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWndMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWndMain)
   {
      return FALSE;
   }

   wsprintf(textStatus, _T("Hello Desktop Application"));

   try
   {
       LumX_APIProvider_Initialize(L"LumXEventsDictionary.xml", 
           UpdateStatusCallback, 
           IncomingCommand, 
           L"MainVer:1.0.123;SecondaryVer:1.1.234", 
           L"Hello from Lumenis Application");
   }
   catch (...)
   {
       LumX_APIProvider_CleanUp();
   }

   ShowWindow(hWndMain, nCmdShow);
   UpdateWindow(hWndMain);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_SEND_EVENT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SENDEVENT), hWnd, SendEvent);
                break;
            case ID_SEND_COMMAND:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SENDCOMMAND), hWnd, SendCommand);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_SETSTATE_ACTIVE:
                SetStateActive();
                break;
            case ID_SETSTATE_IDLE:
                SetStateIdle();
                break;
            case ID_SETSTATE_GETSTATE:
                GetState();
                break;
            case ID_TEST_TESTGEOHELPERS:
                TestGeo();
                break;
            case ID_TEST_TESTSELFACTIVATION:
                TestSelfActivation();
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 5, rcClient.bottom - 30, textStatus, _tcslen(textStatus));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK SendEvent(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            if (LOWORD(wParam) == IDOK)
            {
                WCHAR textKey[MAX_LOADSTRING];
                GetDlgItemText(hDlg, IDC_EDIT_KEY, textKey, MAX_LOADSTRING);
                WCHAR textValue[MAX_LOADSTRING];
                GetDlgItemText(hDlg, IDC_EDIT_VALUE, textValue, MAX_LOADSTRING);

                LumX_APIProvider_SendEvent(textKey, textValue);
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int cnt = 0;

wstring comName1(L"Command1");
wstring comParams1[] = { L"123.4", L"some command", L"true" };

wstring comName2(L"Command2");
wstring comParams2[] = { L"1.234", L"567", L"January 08 2020 18:21", L"890", L"false" };

wstring comName3(L"Command3");
wstring * comParams3 = NULL;

wstring comName4(L"Command4");
wstring comParams4[] = { L"1234", L"some command", L"true" };

wstring comName5(L"Command1");
wstring comParams5[] = { L"kjhasdkj", L"some command", L"true" };

INT_PTR CALLBACK SendCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            if (LOWORD(wParam) == IDOK)
            {
                WCHAR textCommandName[MAX_LOADSTRING];
                GetDlgItemText(hDlg, IDC_EDIT_COMMANDNAME, textCommandName, MAX_LOADSTRING);
                WCHAR textCommandParams[MAX_LOADSTRING];
                GetDlgItemText(hDlg, IDC_EDIT_COMMANDPARAMS, textCommandParams, MAX_LOADSTRING);

                /*switch (cnt)
                {
                case 0:
                    LumX_APIProvider_SendCommand(comName1, comParams1, 3);
                    break;
                case 1:
                    LumX_APIProvider_SendCommand(comName2, comParams2, 5);
                    break;
                case 2:
                    LumX_APIProvider_SendCommand(comName3, comParams3, 0);
                    break;
                case 3:
                    LumX_APIProvider_SendCommand(comName4, comParams4, 3);
                    break;
                case 4:
                    LumX_APIProvider_SendCommand(comName5, comParams5, 3);
                    break;
                }

                cnt++;
                cnt %= 5;*/
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

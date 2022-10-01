// PCRepairTechShell.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PCRepairTechShell.h"
#include <CommCtrl.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 1000

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szComputerName[MAX_LOADSTRING];
DWORD test = MAX_LOADSTRING;
TCHAR szUserName[256];
    unsigned long nSize = 256;
    HWND hwndButton;
    HWND hwndButton2;
    HWND hwndButton3;
    HWND hwndButton4;
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

        EnablePriv(SE_SHUTDOWN_NAME);

#pragma region Shutdown Dialog
        // Shutdown Dialog.
        const wchar_t CLASS_NAME[] = L"Shell_TrayWnd";

        WNDCLASS wc = { };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        RECT rect;
        GetClientRect(GetDesktopWindow(), &rect);

        HWND hwnd = CreateWindowEx(
            WS_EX_TOPMOST,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Advanced Options",    // Window text
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_DLGFRAME,            // Window style

            // Size and position
            rect.right - 300, 0, 300, 300,

            NULL,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );

        if (hwnd == NULL)
        {
            return (int)1;
        }

        hwndButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Open Command Prompt",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
            10,         // x position 
            10,         // y position 
            260,        // Button width
            50,        // Button height
            hwnd,     // Parent window
            (HMENU) 1001,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton2 = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Shut Down",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
            10,         // x position 
            60,         // y position 
            260,        // Button width
            50,        // Button height
            hwnd,     // Parent window
            (HMENU) 1002,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton3 = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Restart",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
            10,         // x position 
            110,         // y position 
            260,        // Button width
            50,        // Button height
            hwnd,     // Parent window
            (HMENU)1003,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        hwndButton4 = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Open File Explorer",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
            10,         // x position 
            160,         // y position 
            260,        // Button width
            50,        // Button height
            hwnd,     // Parent window
            (HMENU)1004,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        SendMessage(hwndButton, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(hwndButton2, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(hwndButton3, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(hwndButton4, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);

        ShowWindow(hwnd, nCmdShow);
#pragma endregion





        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

                  


    return (int) 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    DWORD err;
    std::wstring wos;
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    switch (uMsg)
    {
    case WM_MOVE:

        GetClientRect(GetDesktopWindow(), &rect);
        SetWindowPos(hwnd, HWND_TOPMOST, rect.right - 300, 0, 300, 300, NULL);
        return FALSE;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);  // Macro to get the low-order word.
        int height = HIWORD(lParam); // Macro to get the high-order word.

        // Handle resizing here.
    }
    break;
    case WM_CLOSE: 
        if (MessageBox(hwnd, L"Are you sure you want to log off?", L"Logoff", MB_YESNO + MB_ICONEXCLAMATION) == IDYES) {
            ExitWindows(0, 0);
        }
        return FALSE;
    case WM_DESTROY:
        break;
    case WM_COMMAND: 
        switch (wParam) {
        case 1001:
            GetComputerName(szComputerName, &test);

            GetUserName(szUserName, &nSize);
             err = GetLastError();
            /*if (err != ERROR_SUCCESS) {
                std::wstring err1(L"Error! Error Code: " + err);
                MessageBox(GetDesktopWindow(), err1.c_str(), L"Error", MB_ICONERROR + MB_OK);
                ExitProcess(err);
            }*/

             wos.clear();
            wos.append(L"/k title Command Prompt - Computer Name: " + std::wstring(szComputerName) + L", User Name: " + szUserName);

            ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            ShExecInfo.fMask = NULL;
            ShExecInfo.hwnd = NULL;
            ShExecInfo.lpVerb = NULL;
            ShExecInfo.lpFile = L"C:\\Windows\\System32\\cmd.exe";
            ShExecInfo.lpParameters = wos.c_str();
            ShExecInfo.lpDirectory = NULL;
            ShExecInfo.nShow = SW_SHOW;
            ShExecInfo.hInstApp = NULL;
            ShellExecuteEx(&ShExecInfo);
            CloseHandle(ShExecInfo.hProcess);
            break;
        case 1002:
            if (MessageBox(hwnd, L"Are you sure you want to shut down?", L"Shut Down", MB_YESNO + MB_ICONEXCLAMATION) == IDYES)
            {
                ExitWindowsEx(EWX_SHUTDOWN, NULL);
            }
            break;
        case 1003:
            if (MessageBox(hwnd, L"Are you sure you want to restart?", L"Restart", MB_YESNO + MB_ICONEXCLAMATION) == IDYES)
            {
                ExitWindowsEx(EWX_REBOOT, NULL);
            }
            break;
        case 1004:
            ShellExecute(GetDesktopWindow(), L"open", L"C:\\Windows\\explorer.exe", L"C:\\", NULL, SW_SHOW);
            break;
        }
    }
    if (uMsg == WM_CREATE) {
        GetComputerName(szComputerName, &test);

        GetUserName(szUserName, &nSize);
        DWORD err = GetLastError();
        /*if (err != ERROR_SUCCESS) {
            std::wstring err1(L"Error! Error Code: " + err);
            MessageBox(GetDesktopWindow(), err1.c_str(), L"Error", MB_ICONERROR + MB_OK);
            ExitProcess(err);
        }*/

        wos.clear();
        wos.append(L"/k title Command Prompt - Computer Name: " + std::wstring(szComputerName) + L", User Name: " + szUserName);

        ShellExecute(GetDesktopWindow(), L"open", L"C:\\Windows\\System32\\WallpaperHost.exe", L"", NULL, SW_SHOW);

        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = NULL;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = L"C:\\Windows\\System32\\cmd.exe";
        ShExecInfo.lpParameters = wos.c_str();
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
        CloseHandle(ShExecInfo.hProcess);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
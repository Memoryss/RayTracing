#include <iostream>
#include <windows.h>
#include "TestApp.h"

RayTracing::TestApp *gApp = nullptr;
static const LPCSTR WIN32_CLASS_NAME = "Raytracing_Depth";
const int S_WIDTH = 400, S_HEIGHT = 400;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (NULL == gApp)
    {
        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }

    switch (uiMsg)
    {
    case WM_CREATE:
        break;
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            int w = rc.right - rc.left;
            int h = rc.bottom - rc.top;

            gApp->Resize(w, h);
        }
        break;
    case WM_LBUTTONDBLCLK:
        //gApp->OnMouseDown(0);
        break;
    case WM_LBUTTONUP:
        //gApp->OnKeyUp(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
        gApp->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
        break;
    default:
        break;
    }

    return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    //当前线程以最高优先权 运行
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

    // 创建窗口
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = NULL;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = WIN32_CLASS_NAME;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;//WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX;
    RECT rc = { 0, 0, S_WIDTH, S_HEIGHT };

    AdjustWindowRect(&rc, style, FALSE);

    int width = rc.right - rc.left;
    int	height = rc.bottom - rc.top;
    int xpos = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int ypos = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    HWND hWnd = CreateWindow(WIN32_CLASS_NAME, WIN32_CLASS_NAME, style,
        xpos, ypos, width, height,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    GetClientRect(hWnd, &rc);
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;

    gApp = new RayTracing::TestApp(hWnd, width, height);
    gApp->Init(width, height);

//     if (AllocConsole())
//     {
//         freopen("out.txt", "w+", stdout);
//     }
    
    MSG msg;
    memset(&msg, 0, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            gApp->Update();
        }
    }

    gApp->Stop();
    delete gApp;

    UnregisterClass(WIN32_CLASS_NAME, hInstance);

    return 0;

}
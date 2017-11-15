#include <iostream>
#include <windows.h>

#include "Ray.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{

}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    //当前线程以最高优先权 运行
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
}
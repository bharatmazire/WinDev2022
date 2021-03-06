/*
* Execution Steps : 
* cl.exe /c /EHsc ColorfullWindow.cpp
* rc.exe window.rc
* link.exe ColorfullWindow.obj window.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS /MACHINE:X64
*/

// header file
#include<windows.h>
#include "window.h"

#define ID_TIMER 501

// functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WindowApp");

	// code
	// initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register wndclass 
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("BSM - Colorfull Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int siPressedKey;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hBrush;

	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, ID_TIMER);

		if (siPressedKey < 10)
			siPressedKey++;
		else
			siPressedKey = 0;

		InvalidateRect(hwnd, NULL, TRUE);

		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		break;
	
	/*
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'R':
			siPressedKey = 1;
			break;
		case 'G':
			siPressedKey = 2;
			break;
		case 'B':
			siPressedKey = 3;
			break;
		case 'C':
			siPressedKey = 4;
			break;
		case 'M':
			siPressedKey = 5;
			break;
		case 'Y':
			siPressedKey = 6;
			break;
		case 'K':
			siPressedKey = 7;
			break;
		case 'W':
			siPressedKey = 8;
			break;
		//case VK_ESCAPE:
		//	SendMessage(hwnd, WM_DESTROY, 0, 0L);
		//	break;
		default:
			siPressedKey = 0;
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	*/
	
	/*
	case WM_LBUTTONDOWN:
		if (siPressedKey < 10)
			siPressedKey++;
		else
			siPressedKey = 0;

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	*/

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		switch (siPressedKey)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		case 10:
			hBrush = CreateSolidBrush(RGB(12, 12, 128));
			break;
		default:
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			break;
		}

		FillRect(hdc, &rc, hBrush);
		// You can comment above line and remove comment of following 2 lines

		//SelectObject(hdc, hBrush);
		//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

/*
* Execution Steps : 
* cl.exe /c /EHsc MessageBox-WM_CREATE.cpp
* link.exe FirstEvent.obj user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS /MACHINE:X64
*/

// header file
#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register wndclass
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("BSM - First Window Event"),
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
	// local variable declaration
	TCHAR str[255];
	int num1 = 10;
	int num2 = 20;
	int num3 = num1 + num2;
	// code
	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(str, TEXT("Evaluation :: %d + %d = %d"),num1,num2,num3);
		MessageBox(hwnd, str, TEXT("Equation Evaluation"), MB_OK);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		break;
	/*
	case WM_SETFOCUS:
		wsprintf(str, TEXT("WM_SETFOCUS"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		break;
	case WM_KILLFOCUS:
		wsprintf(str, TEXT("WM_KILLFOCUS"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		break;
	*/
	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY"));
		MessageBox(hwnd, str, TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

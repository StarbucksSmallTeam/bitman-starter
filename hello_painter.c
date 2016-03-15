#include <stdio.h>
#include <windows.h>

static TCHAR szClassName[] = TEXT("szHelloPainterWindow");

BOOL bMouseDown = FALSE;
int left = 0, top = 0, right = 0, bottom = 0;

LRESULT CALLBACK DefaultWndProc(
								HWND hWnd,
								UINT uMsg,
								WPARAM wParam,
								LPARAM lParam
								);
int main(){

	MSG msg;
	HWND hWnd;
	WNDCLASS wcx;

	HANDLE hInstance = GetModuleHandle(NULL);

	ZeroMemory(&wcx, sizeof(wcx));

	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.lpfnWndProc = DefaultWndProc;
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = szClassName;
	wcx.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClass(&wcx)){
		return -1;
	}

	hWnd = CreateWindow(
		szClassName,
		TEXT("Hello Painter"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, hWnd, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

VOID ClearWindow(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
}

LRESULT CALLBACK DefaultWndProc(
								HWND hWnd,
								UINT uMsg,
								WPARAM wParam,
								LPARAM lParam
								)
{
	PAINTSTRUCT ps;
	switch(uMsg){
		case WM_CREATE:
			return 0;
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			Rectangle(ps.hdc, left, top, right, bottom);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_LBUTTONDOWN:
			bMouseDown = TRUE;
			left = LOWORD(lParam);
			top = HIWORD(lParam);
			return 0;
		case WM_LBUTTONUP:
			bMouseDown = FALSE;
			return 0;
		case WM_MOUSEMOVE:
			if(bMouseDown){
				right = LOWORD(lParam);
				bottom = HIWORD(lParam);
				ClearWindow(hWnd);
			}
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

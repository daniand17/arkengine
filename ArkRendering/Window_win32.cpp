#include <assert.h>

#include "ArkWindow.h"
#include "BuildOptions.h"

#if USE_VULKAN
LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ArkWindow * window = reinterpret_cast<ArkWindow *>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	switch ( uMsg )
	{
	case WM_CLOSE:
		window->Close();
		return 0;
	case WM_SIZE:
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void ArkWindow::initOSWindow()
{
	WNDCLASSEX winClass{};
	assert(mSizeX > 0);
	assert(mSizeY > 0);

	_win32_instance = GetModuleHandle(nullptr);
	_win32_class_name = mWindowName.toStdString() + "_" + std::to_string(_win32_class_id_counter);

	_win32_class_id_counter++;

	// Initialize window class struct and register
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowsEventHandler;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = _win32_instance;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = _win32_class_name.c_str();
	winClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if ( !RegisterClassEx(&winClass) )
	{
		assert(0 && "Cannot create a window in which to draw!\n");
		fflush(stdout);
		std::exit(-1);
	}

	// The default style
	DWORD exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// Creating the window
	RECT wr = {0, 0, LONG(mSizeX), LONG(mSizeY)};
	AdjustWindowRectEx(&wr, style, FALSE, exStyle);	// convert size of window (increase a bit) to get the surface size we want
	_win32_window = CreateWindow(
		0,
		_win32_class_name.c_str(),		// Class name
		style,							// window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// xy coords
		wr.right - wr.left,				// width
		wr.bottom - wr.top,				// height
		NULL,							// handle to parent
		NULL,							// handle to menu
		_win32_instance,				// hInstance
		NULL							// no extra parameters
	);

	if ( !_win32_window )
	{
		assert(1 && "Cannot create a window in which to draw!\n");
		fflush(stdout);
		std::exit(-1);
	}

	SetWindowLongPtr(_win32_window, GWLP_USERDATA, (LONG_PTR) this);
	ShowWindow(_win32_window, SW_SHOW);
	SetForegroundWindow(_win32_window);
	SetFocus(_win32_window);
}

void ArkWindow::deInitOSWindow()
{
	DestroyWindow(_win32_window);
	UnregisterClass(_win32_class_name.c_str(), _win32_instance);
}

void ArkWindow::updateOSWindow()
{
	MSG msg;
	if ( PeekMessage(&msg, _win32_window, 0, 0, PM_REMOVE) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

#endif	// VK_USE_PLATFORM_WIN32_KHR

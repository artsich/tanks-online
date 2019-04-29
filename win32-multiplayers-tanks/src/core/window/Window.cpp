#include "window.h"
#include "WindowManager.h"

namespace core { namespace window {

	Window::Window(const setting_window* setting) : 
		setting(setting), 
		keyListener(NULL)
	{
		InitWindow(setting);
		ResizeSection(setting->width, setting->height);
	}

	Window::~Window() 
	{
		close();
	}

	void Window::clear() 
	{
		if (screenBuffer.Memory)
		{
			int size = screenBuffer.Width * screenBuffer.Height * screenBuffer.BytesPerPixel;
			memset(screenBuffer.Memory, 0, size);
		}
	}

	void Window::close()
	{
		Running = false;

		if (screenBuffer.Memory != NULL)
		{
			VirtualFree(screenBuffer.Memory, 0, MEM_RELEASE);
			screenBuffer.Memory = NULL;
		}
	}

	void Window::set_key_listener(core::input::IKeyListener* keyListener)
	{
		this->keyListener = keyListener;
	}

	void Window::InitWindow(const setting_window* setting)
	{
		WindowManager::getInstance().add_window(this);

		WindowClass = { 0 };
		WindowClass.hInstance = setting->hInstance;
		WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		WindowClass.lpszClassName = setting->windowClassName;
		WindowClass.lpfnWndProc = Win32WindowCallback;
		Running = false;

		if (RegisterClass(&WindowClass)) 
		{
			HandleWindow = CreateWindowEx(
				0,
				WindowClass.lpszClassName,
				setting->title,
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				setting->windowWidth,
				setting->windowHeight,
				0,
				0,
				setting->hInstance,
				0);
			if (HandleWindow) 
			{
				Running = true;
			}
		}
	}

	void Window::render() {
		HDC DeviceContext = GetDC(HandleWindow);

		StretchDIBits(DeviceContext,
			0, 0,
			screenBuffer.Width,
			screenBuffer.Height,
			0, 0,
			screenBuffer.Width,
			screenBuffer.Height,
			screenBuffer.Memory,
			&bitmapInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
		ReleaseDC(HandleWindow, DeviceContext);
	}

	void Window::ResizeSection(int width, int height) 
	{
		if (screenBuffer.Memory != NULL)
		{
			VirtualFree(screenBuffer.Memory, 0, MEM_RELEASE);
		}

		int BytesPerPixel = 4;
		screenBuffer.BytesPerPixel = BytesPerPixel;
		screenBuffer.Width = width;
		screenBuffer.Height = height;
		screenBuffer.Pitch = screenBuffer.Width * BytesPerPixel;

		bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
		bitmapInfo.bmiHeader.biWidth = screenBuffer.Width;
		bitmapInfo.bmiHeader.biHeight = screenBuffer.Height;
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;

		int BitmapMemorySize = (width * height) * BytesPerPixel;
		screenBuffer.Memory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}

	void Window::processMessage() {
		MSG Message;
		while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)) 
		{
			switch (Message.message) 
			{
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_KEYUP:
				case WM_KEYDOWN: 
				{
					int VKCode = Message.wParam;
					bool WasDown = ((Message.lParam & (1 << 30)) != 0);
					bool IsDown = ((Message.lParam & (1 << 31)) == 0);
				
					if (WasDown) 
					{
#if !INPUT_DEBUG
						char buf[20] = "WasDown ";
						buf[8] = (char)VKCode;
						buf[9] = '\n';
						OutputDebugString(buf);
#endif
						if (keyListener)
						{
							keyListener->releaseKey(VKCode);
						}
					}
					if (IsDown) 
					{
#if !INPUT_DEBUG
						char buf[20] = "IsDown ";
						buf[7] = (char)VKCode;
						buf[8] = '\n';
						OutputDebugString(buf);
#endif
						if (keyListener)
						{
							keyListener->pressedKey(VKCode);
						}
					}

					bool AltKeyWasDown = (Message.lParam & (1 << 29));
					if ((VKCode == VK_F4) && AltKeyWasDown)
					{
						Running = false;
					}
				} break;

				default: 
				{
					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				} break;
			}
		}
	}

	LRESULT Window::Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
		LRESULT Result = 0;

		switch (Message) 
		{
			case WM_CREATE: {
				OutputDebugString("Window Create");
			} break;

			case WM_DESTROY: 
			{
				WindowManager::getInstance().close_window(Window);
				OutputDebugString("Window Destroy");
			}break;
			case WM_PAINT: 
			{
				PAINTSTRUCT Paint;
				HDC DeviceContext = BeginPaint(Window, &Paint);
				EndPaint(Window, &Paint);
			} break;
			default: 
			{
				Result = DefWindowProc(Window, Message, WParam, LParam);
			} break;
		}
		return Result;
	}

	window_dimension Window::GetClientRectangle()
	{
		RECT ClientRect;
		GetClientRect(HandleWindow, &ClientRect);
		window_dimension result;
		result.widht = ClientRect.right - ClientRect.left;
		result.height = ClientRect.bottom - ClientRect.top;
		return result;
	}

}}
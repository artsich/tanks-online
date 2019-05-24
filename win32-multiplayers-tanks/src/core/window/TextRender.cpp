
#include "TextRender.h"

void TextRender::Init()
{
	HRESULT hResult = WriteFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.0f,
		L"en-us",
		&textFormat);

	RECT rc;
	GetClientRect(window, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	hResult = D2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(window, size),
		&renderTarget);

	if (SUCCEEDED(hResult))
	{
		hResult = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&colorBrush);
	}

	layoutRect = D2D1::RectF(
		static_cast<FLOAT>(rc.left),
		static_cast<FLOAT>(rc.top),
		static_cast<FLOAT>(rc.right - rc.left),
		static_cast<FLOAT>(rc.bottom - rc.top));
}

TextRender::TextRender(HWND window, INT x, INT y) :
	window(window), x(x), y(y)
{
	Init();
}

TextRender::~TextRender()
{
	renderTarget->Release();
	colorBrush->Release();
}

void TextRender::Add(std::string buffer)
{
	ss << buffer;
}

void TextRender::Flush()
{
	renderTarget->BeginDraw();
//	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	auto str = ss.str();
	wchar_t* text = L"Just Text";
	int len = 10;

	renderTarget->DrawText(text, len,
		textFormat,
		layoutRect,
		colorBrush);
	
	renderTarget->EndDraw();
	ss.str("");
}


void InitD2D1Factories()
{
	HRESULT hResult;
	if (D2D1Factory == nullptr)
	{
		hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2D1Factory);
	}

	if (WriteFactory == nullptr)
	{
		hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
			(IUnknown**)(&WriteFactory));
	}
}

void ReleaseD2D1Factories()
{
	if (D2D1Factory != nullptr)
	{
		D2D1Factory->Release();
	}

	if (WriteFactory != nullptr)
	{
		WriteFactory->Release();
	}
}


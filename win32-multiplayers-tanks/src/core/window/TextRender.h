#pragma once
#include <Windows.h>
#include <dwrite.h>
#include <d2d1.h>
#include <sstream>
#include <string>

static IDWriteFactory* WriteFactory;
static ID2D1Factory* D2D1Factory;

class TextRender
{
private:
	std::stringstream ss;
	
	HWND window;
	INT x, y;

	IDWriteTextFormat* textFormat;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* colorBrush;
	D2D1_RECT_F layoutRect;

	void Init();

public:
	TextRender(HWND window, INT x, INT y);
	~TextRender();

	void Add(std::string buffer);
	void Flush();
};

void InitD2D1Factories();
void ReleaseD2D1Factories();
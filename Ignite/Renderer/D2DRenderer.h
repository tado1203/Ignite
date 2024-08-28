#pragma once
#include <d2d1_1.h>

namespace D2DRenderer
{
	extern ID2D1DeviceContext* Context;

	void Init(IDXGISurface* dxgiSurface);

	void UpdateBlur();

	void RenderBlurRect(D2D1_ROUNDED_RECT rect);
}
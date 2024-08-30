#pragma once
#include <d2d1_1.h>

namespace D2DRenderer
{
	extern ID2D1DeviceContext* Context;
	extern ID2D1Factory* Factory;
	extern ID2D1Bitmap1* Bitmap;

	void Init(IDXGISurface* dxgiSurface);

	void CopyBitmap(ID2D1Bitmap1* src, ID2D1Bitmap** dst);
}
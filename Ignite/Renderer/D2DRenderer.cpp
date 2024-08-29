#include "imgui/imgui.h"

#include "D2DRenderer.h"
#include "Effect/Blur.h"

namespace D2DRenderer
{
	ID2D1DeviceContext* Context;
	ID2D1Factory* Factory;
	ID2D1Bitmap1* Bitmap;

	void CopyBitmap(ID2D1Bitmap1* src, ID2D1Bitmap** dst)
	{
		if (*dst == nullptr)
		{
			D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(src->GetPixelFormat());
			Context->CreateBitmap(src->GetPixelSize(), properties, dst);
		}

		D2D1_POINT_2U origin = { 0, 0 };
		D2D1_SIZE_U size = src->GetPixelSize();
		D2D1_RECT_U rect = { 0, 0, size.width, size.height };
		(*dst)->CopyFromBitmap(&origin, src, &rect);
	}

	void Init(IDXGISurface* dxgiSurface)
	{
		D2D1_CREATION_PROPERTIES properties = {};
		properties.threadingMode = D2D1_THREADING_MODE_MULTI_THREADED;
		properties.debugLevel = D2D1_DEBUG_LEVEL_NONE;
		properties.options = D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS;
		D2D1CreateDeviceContext(dxgiSurface, properties, &Context);

		D2D1_BITMAP_PROPERTIES1 properties1 = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
		Context->CreateBitmapFromDxgiSurface(dxgiSurface, properties1, &Bitmap);

		Context->GetFactory(&Factory);

		InitBlur();
	}
}


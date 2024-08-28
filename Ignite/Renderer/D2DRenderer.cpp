#include "imgui/imgui.h"

#include "D2DRenderer.h"

ID2D1DeviceContext* D2DRenderer::Context;
ID2D1Factory* Factory;
ID2D1Bitmap1* Bitmap;

ID2D1Effect* BlurEffect;
ID2D1ImageBrush* BlurBrush;

void CopyBitmap(ID2D1Bitmap1* src, ID2D1Bitmap** dst)
{
	if (*dst == nullptr)
	{
		D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(src->GetPixelFormat());
		D2DRenderer::Context->CreateBitmap(src->GetPixelSize(), properties, dst);
	}

	D2D1_POINT_2U origin = {0, 0};
	D2D1_SIZE_U size = src->GetPixelSize();
	D2D1_RECT_U rect = { 0, 0, size.width, size.height };
	(*dst)->CopyFromBitmap(&origin, src, &rect);
}

void InitBlur()
{
	D2DRenderer::Context->CreateEffect(CLSID_D2D1GaussianBlur, &BlurEffect);

	BlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_DIRECTIONALBLUR_OPTIMIZATION_QUALITY);
	BlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
}

void D2DRenderer::UpdateBlur()
{
	ID2D1Bitmap* bitmap = nullptr;
	CopyBitmap(Bitmap, &bitmap);
	BlurEffect->SetInput(0, bitmap);
	bitmap->Release();

	BlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 10.f);

	ID2D1Image* image;
	BlurEffect->GetOutput(&image);
	ImGuiIO& io = ImGui::GetIO();
	D2D1_IMAGE_BRUSH_PROPERTIES properties = D2D1::ImageBrushProperties(
		D2D1::RectF(0, 0, io.DisplaySize.x, io.DisplaySize.y)
	);
	Context->CreateImageBrush(image, properties, &BlurBrush);

	image->Release();
}

void D2DRenderer::Init(IDXGISurface* dxgiSurface)
{
	D2D1_CREATION_PROPERTIES properties = {};
	properties.threadingMode = D2D1_THREADING_MODE_MULTI_THREADED;
	properties.debugLevel    = D2D1_DEBUG_LEVEL_NONE;
	properties.options       = D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS;
	D2D1CreateDeviceContext(dxgiSurface, properties, &Context);

	D2D1_BITMAP_PROPERTIES1 properties1 = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	Context->CreateBitmapFromDxgiSurface(dxgiSurface, properties1, &Bitmap);

	Context->GetFactory(&Factory);

	InitBlur();
}

void D2DRenderer::RenderBlurRect(D2D1_ROUNDED_RECT rect)
{
	ID2D1RoundedRectangleGeometry* geometry;
	Factory->CreateRoundedRectangleGeometry(rect, &geometry);

	Context->FillGeometry(geometry, BlurBrush);
}
#include "imgui/imgui.h"

#include "../D2DRenderer.h"
#include "Blur.h"

ID2D1Effect* BlurEffect;
ID2D1ImageBrush* BlurBrush;

namespace D2DRenderer
{
	void InitBlur()
	{
		Context->CreateEffect(CLSID_D2D1GaussianBlur, &BlurEffect);

		BlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_DIRECTIONALBLUR_OPTIMIZATION_QUALITY);
		BlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
	}

	void UpdateBlur()
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

	void RenderBlurRect(D2D1_ROUNDED_RECT rect)
	{
		ID2D1RoundedRectangleGeometry* geometry;
		Factory->CreateRoundedRectangleGeometry(rect, &geometry);

		Context->FillGeometry(geometry, BlurBrush);

		geometry->Release();
		BlurBrush->Release();
	}
}
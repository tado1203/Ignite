#pragma once
#include <d2d1_1.h>

namespace D2DRenderer
{
	void InitBlur();

	void UpdateBlur();

	void RenderBlurRect(D2D1_ROUNDED_RECT rect, float amount);
}
#include <dxgi.h>
#include <d3d11.h>
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/imgui.h"
#include "kiero/kiero.h"
#include <cstdio>

#include "D3D11Hook.h"
#include "../Win32/WndProcHook.h"
#include "../../Renderer/D2DRenderer.h"

typedef HRESULT(__stdcall* Present)(IDXGISwapChain*, UINT, UINT);
Present oPresent;

ID3D11Device* Device;
ID3D11DeviceContext* Context;
ID3D11RenderTargetView* MainRenderTargetView;

bool init = false;

HRESULT __stdcall hkPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Device)))
		{
			Device->GetImmediateContext(&Context);

			DXGI_SWAP_CHAIN_DESC desc;
			SwapChain->GetDesc(&desc);

			ID3D11Texture2D* backBuffer;
			SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

			Device->CreateRenderTargetView(backBuffer, NULL, &MainRenderTargetView);
			backBuffer->Release();

			WndProcHook::Init(desc.OutputWindow);

			ImGui::CreateContext();
			ImGui_ImplWin32_Init(desc.OutputWindow);
			ImGui_ImplDX11_Init(Device, Context);

			IDXGISurface* backBuffer1;
			SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&backBuffer1);
			D2DRenderer::Init(backBuffer1);
			backBuffer1->Release();
			
			init = true;
		}
		else
		{
			return oPresent(SwapChain, SyncInterval, Flags);
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	D2DRenderer::UpdateBlur();

	D2DRenderer::Context->BeginDraw();

	//render d2d here

	D2DRenderer::Context->EndDraw();

	//render imgui here

	ImGui::Render();

	Context->OMSetRenderTargets(1, &MainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(SwapChain, SyncInterval, Flags);
}

void D3D11Hook::Init()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		if (kiero::bind(8, (void**)&oPresent, hkPresent) == kiero::Status::Success)
		{
			printf("Hooked D3D11\n");
		}
	}
}
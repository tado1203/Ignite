#pragma once
#include <cstdint>

namespace Offsets
{
	extern uintptr_t GameAssembly;

	namespace Networking
	{
		extern uintptr_t GetLocalPlayer;
	}
	
	namespace VRCPlayerApi
	{
		extern uintptr_t GetAllPlayers;
	}

	void Init();
}
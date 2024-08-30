#include <Windows.h>
#include <iostream>
#include <iomanip>

#include "Offsets.h"

namespace Offsets
{
	uintptr_t GameAssembly;

	namespace Networking
	{
		uintptr_t GetLocalPlayer = 0x75A4F80;
	}

	namespace VRCPlayerApi
	{
		uintptr_t GetAllPlayers = 0x757AAC0;
	}

	void Init()
	{
		GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
		std::cout << std::hex << "GameAssembly Address: 0x" << GameAssembly << std::endl;
	}
}
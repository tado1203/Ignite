#include <vector>
#include <chrono>
#include <string>

#include "SDK.h"
#include "../Offsets.h"
#include "../../Module/ModuleManager.h"
#include "Player/Player.h"

namespace SDK
{

	bool IsInWorld()
	{
		typedef void* (*getlocalplayer)();
		getlocalplayer func = reinterpret_cast<getlocalplayer>(Offsets::GameAssembly + Offsets::Networking::GetLocalPlayer);
		return func() != nullptr;
	}

	void OnUpdate()
	{
		for (auto module : ModuleManager::ModuleList)
		{
			module.OnUpdate();
		}
	}

	void Init()
	{

	}
}
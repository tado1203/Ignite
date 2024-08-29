#pragma once
#include <vector>

#include "Module.h"

namespace ModuleManager
{
	extern std::vector<Module> ModuleList;

	void Init();
}
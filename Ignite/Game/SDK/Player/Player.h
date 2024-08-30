#pragma once
#include <string>
#include <vector>

#include "../../../Utils/Math.h"

class PlayerClass
{
public:
	std::string Name;
	Vector3 Position;

	PlayerClass(std::string name, Vector3 position);
};

namespace SDK
{
	namespace Player
	{
		extern std::vector<PlayerClass*> PlayerList;
		extern int PlayerCount;
	}
}
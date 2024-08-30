#include "Player.h"

PlayerClass::PlayerClass(std::string name, Vector3 position) : Name(name), Position(position) {}

namespace SDK
{
	namespace Player
	{
		std::vector<PlayerClass*> PlayerList;
		int PlayerCount = 0;
	}
}
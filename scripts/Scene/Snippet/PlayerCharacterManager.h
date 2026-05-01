#pragma once
#include <vector>
#include "PlayerCharacter.h"


class PlayerCharacterManager
{
public :
	PlayerCharacterManager() ;
	~PlayerCharacterManager() = default;
	PlayerCharacter* getPlayerById(int id);
	void AddPlayer(PlayerCharacter* character);
private :
	std::vector<PlayerCharacter*> players;
};


#include "PlayerCharacterManager.h"

PlayerCharacterManager::PlayerCharacterManager() {

}

PlayerCharacter* PlayerCharacterManager::getPlayerById(int id) {
	
	if (id < players.size()) {
		return players[id];
	}
	return nullptr;
}

void PlayerCharacterManager::AddPlayer(PlayerCharacter* character) {
	players.push_back(character);
}
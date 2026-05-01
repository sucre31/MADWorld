#pragma once
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/Enemy.h"

class EnemyDefeatAction : public IEventAction
{
private:
	Enemy* enemy;
	bool finalBossflag;
	int nextEnemyId;
	std::shared_ptr<SnippetSound> snippetSound;

public:
	EnemyDefeatAction(Enemy* e, bool bossFlag, int id, std::shared_ptr<SnippetSound> sound)
		:enemy(e), finalBossflag(bossFlag), nextEnemyId(id), snippetSound(sound){
	}

	void execute() override;
};


#pragma once
#include <string>
#include <memory>
#include "Common/Event/IEventAction.h"

class BeatManager;

class EndingAction : public IEventAction
{
private:
	int musicNo;
	std::shared_ptr<BeatManager> beatManager;
public:
	EndingAction(int music, std::shared_ptr<BeatManager> bManager)
		:  musicNo(music), beatManager(bManager){
	}

	void execute() override;

};


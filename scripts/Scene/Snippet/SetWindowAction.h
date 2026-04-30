#pragma once
#include <string>
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/PlayerCharacter.h"

class SetWindowAction : public IEventAction
{
private:
	MessageWindow* window;
	std::string msg;
	std::shared_ptr<SnippetSound> snippetSound;
public:
	SetWindowAction(MessageWindow* w, std::string  m, std::shared_ptr<SnippetSound> s) 
		: window(w), msg(m) ,snippetSound(s) {
	}

	void execute() override {
		PlaySoundMem(snippetSound->getBattleSE()[1], DX_PLAYTYPE_BACK);
		window->setMessage(msg);
	}

};


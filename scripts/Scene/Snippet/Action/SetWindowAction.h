#pragma once
#include <string>
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/PlayerCharacter.h"

class Enemy;

class SetWindowAction : public IEventAction
{
private:
	MessageWindow* window;
	int soundType = 0;
	std::string msg;
	std::shared_ptr<SnippetSound> snippetSound;
public:

	SetWindowAction(MessageWindow* w, std::string  m, int st, std::shared_ptr<SnippetSound> s)
		: window(w), msg(m), soundType(st), snippetSound(s){
	}

	SetWindowAction(MessageWindow* w, std::string  m, std::shared_ptr<SnippetSound> s)
		: window(w), msg(m), snippetSound(s) {
	}

	void execute() override;

};


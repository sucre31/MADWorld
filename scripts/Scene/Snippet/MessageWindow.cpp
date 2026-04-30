#include <Dxlib.h>
#include <string>
#include "MessageWindow.h"
#include "Common/Image.h"
#include "SnippetGameManager.h"

using namespace std;

MessageWindow::MessageWindow(std::shared_ptr<SnippetGameManager> managerIns, std::shared_ptr<SnippetImage> image) {
	myX = 47;
	myY = 2;
	currentTurn = 0;
	messageCounter = 32;
	messageFlag = false;
	snippetGameManager = managerIns;
	snippetImage = image;
	//stringImage = make_shared<StringImage>();
	//stringImage->setPos(myX + 4, myY + 4);
	//strBattleMessage[0] = "ああ";
}

bool MessageWindow::update() {
	if (snippetGameManager->getFpsIns()->isFrameChanged()) messageCounter++;
	if (currentTurn != snippetGameManager->getTurn()) {
		currentTurn = snippetGameManager->getTurn();
		messageCounter = 0;
		messageFlag = true;
		currentMessageID = currentTurn % 4;
		switch (currentTurn % 4) {
		case 0:
			currentMessageID = 0;
			break;
		case 1:
			currentMessageID = 2;
			break;
		case 2:
			currentMessageID = 3;
			break;
		case 3:
			currentMessageID = 1;
			break;
		}
	}
	if (messageCounter > 30) messageFlag = false;
	return true;
}

void MessageWindow::draw() const {
	if (!messageFlag) return;

	DrawGraph(myX, myY, snippetImage->getMessageWindow(), TRUE);

	if (useCustomMessage) {
		DrawString(myX + 6, myY + 9, customMessage.c_str(), GetColor(0, 0, 0));
		return;
	}

	switch (currentMessageID) {
	case 0:
		DrawString(myX + 6, myY + 9, "リュカの こうげき!", GetColor(0, 0, 0));
		break;
	case 1:
		DrawString(myX + 6, myY + 9, "クマトラの こうげき!", GetColor(0, 0, 0));
		break;
	case 2:
		DrawString(myX + 6, myY + 9, "ダスターの こうげき!", GetColor(0, 0, 0));
		break;
	case 3:
		DrawString(myX + 6, myY + 9, "ボニーの こうげき!", GetColor(0, 0, 0));
		break;
	}
}

void MessageWindow::setMessage(const std::string& msg) {
	customMessage = msg;
	useCustomMessage = true;
	messageCounter = 0;
	messageFlag = true;
}

void MessageWindow::setMessage(int ID) {
	currentMessageID = ID;
	useCustomMessage = false; 
	messageCounter = 0;
	messageFlag = true;
}
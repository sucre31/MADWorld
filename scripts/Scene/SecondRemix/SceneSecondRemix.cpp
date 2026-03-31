#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	int back = sozaiManager.makeSozai("", "Assets/Sprites/images/secondRemix/back.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager.setSozaiLayer(back, 0);

	objectionManager.setSozaiManager(&sozaiManager);
	objectionManager.initSozai();
	objectionManager.setActive(true);

	donesiaManager.setSozaiManager(&sozaiManager);
	donesiaManager.initSozai();
	donesiaManager.setActive(false);

	dontacoManager.setSozaiManager(&sozaiManager);
	dontacoManager.initSozai();
	dontacoManager.setActive(false);

	sonyaManager.setSozaiManager(&sozaiManager);
	sonyaManager.initSozai();
	sonyaManager.setActive(false);

	musicManager.LoadMusic("tutorial", "Assets/Sounds/dontaco/BGM/tutorialBeat.wav");
	musicManager.LoadMusic("backBeat", "Assets/Sounds/dontaco/BGM/backBeat.wav");
	musicManager.LoadMusic("remix2", "Assets/Sounds/Remix2/remix2.wav");

	bgmName = "remix2";
	musicManager.Play(bgmName, true);

	activeManagerIndex = 0;
}

void SceneSecondRemix::update() {
	int prevMangerIndex = activeManagerIndex;


	if (Pad::getIns()->get(ePad::change) >= 1 && Pad::getIns()->get(ePad::L) == 1) {
		activeManagerIndex--;
		if (activeManagerIndex < 0) {
			activeManagerIndex = 0;
		}
	}

	if (Pad::getIns()->get(ePad::change) >= 1 && Pad::getIns()->get(ePad::A) == 1) {
		if (musicManager.IsPlaying()) {
			musicManager.Stop();
		}
		else {
			musicManager.Play(bgmName, true);
		}
	}

	if (Pad::getIns()->get(ePad::change) >= 1 && Pad::getIns()->get(ePad::R) == 1) {
		activeManagerIndex++;
		if (activeManagerIndex >= sozaiManagerCount) {
			activeManagerIndex = sozaiManagerCount - 1;
		}
	}

	if (Pad::getIns()->get(ePad::start) >= 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
		return;
	}

	if (prevMangerIndex != activeManagerIndex) {
		switch (activeManagerIndex) {
		case 0:
			objectionManager.setActive(true);
			donesiaManager.setActive(false);
			dontacoManager.setActive(false);
			break;
		case 1:
			objectionManager.setActive(false);
			donesiaManager.setActive(true);
			dontacoManager.setActive(false);
			break;
		case 2:
			objectionManager.setActive(false);
			donesiaManager.setActive(false);
			dontacoManager.setActive(true);
			break;
		}
	}

	objectionManager.update();
	donesiaManager.update();
	dontacoManager.update();
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
}
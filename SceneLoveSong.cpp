#include <DxLib.h>
#include "Sound.h"
#include "Image.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "SceneLoveSong.h"


SceneLoveSong::SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	// �t�H���g�ݒ�
	ChangeFont("DragonQuestFC");
	SetFontSpace(3);
	SetFontSize(48);
	SetFontThickness(1);

	isMusicPlay = false;
	currentSoundIndex = 0;
	currentMovieIndex = 0;
	movieTurnFlag = false;
	musicIndex = 0;
	strIndex = 1;
	stringRevive = "��";
	Sound::getIns()->loadLoveSongSamples();
	Image::getIns()->loadLoveSongResources();
}

void SceneLoveSong::update()
{
	if (Pad::getIns()->get(ePad::L) == 1) {
		// ���y�Đ�
		if (!isMusicPlay) {
			PlaySoundMem(Sound::getIns()->getLoveSong()[0], DX_PLAYTYPE_LOOP, TRUE);
			musicIndex = 0;
			isMusicPlay = true;
			resetString();
		}
		else if (musicIndex == 0){
			StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
			isMusicPlay = false;
		}
		else {
			StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
			PlaySoundMem(Sound::getIns()->getLoveSong()[0], DX_PLAYTYPE_LOOP, TRUE);
			musicIndex = 0;
			isMusicPlay = true;
		}
	}
	if (Pad::getIns()->get(ePad::R) == 1) {
		// ���y�Đ�
		if (!isMusicPlay) {
			PlaySoundMem(Sound::getIns()->getLoveSong()[1], DX_PLAYTYPE_LOOP, TRUE);
			musicIndex = 1;
			isMusicPlay = true;
		}
		else if (musicIndex == 1){
			StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
			isMusicPlay = false;
		}
		else {
			StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
			PlaySoundMem(Sound::getIns()->getLoveSong()[1], DX_PLAYTYPE_LOOP, TRUE);
			musicIndex = 1;
			isMusicPlay = true;
		}
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		playSampleSound(0);
		addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		playSampleSound(1);
		addReviveChar("��");
		//addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		playSampleSound(2);
		addReviveChar("��");
		addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		playSampleSound(3);
		addReviveChar("��");
		addReviveChar("��");
		//addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::Y) == 1) {
		playSampleSound(4);
		addReviveChar("��");
		//addReviveChar("��");
		///addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		playSampleSound(5);
		addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		playSampleSound(6);
		addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::X) == 1) {
		playSampleSound(7);
		addReviveChar("��");
		addReviveChar("��");
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// ���j���[�ɖ߂�
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
		// �����ɒ��ڏ����񂶂�Ȃ��Ċ֐��p�ӂ��ׂ�����
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneLoveSong::playSampleSound(int num) {
	StopSoundMem(Sound::getIns()->getLoveSongSamples()[currentSoundIndex]);
	currentSoundIndex = num;
	PlaySoundMem(Sound::getIns()->getLoveSongSamples()[currentSoundIndex], DX_PLAYTYPE_BACK);
	// �Ή�����f���̍Đ�
	currentMovieIndex = num;
	//currentMovieIndex = 4; // �e�X�g�p
	movieTurnFlag = !movieTurnFlag;
	if (isMusicPlay) {
		SeekMovieToGraph(Image::getIns()->getLoveSongMovie()[currentMovieIndex], 0);
		PlayMovieToGraph(Image::getIns()->getLoveSongMovie()[currentMovieIndex]);
	}
	else {
		SeekMovieToGraph(Image::getIns()->getLoveSongLMovie()[currentMovieIndex], 0);
		PlayMovieToGraph(Image::getIns()->getLoveSongLMovie()[currentMovieIndex]);
	}
}

/*
@brief ���C�h�����i�Ђ炪�ȁj���󂯎���Ė����̕����ɒǉ�
*/
void SceneLoveSong::addReviveChar(std::string mes) {
	if (strIndex <= strSize - 1) {
		// �Ђ炪�ȂȂ̂�2byte������ �s��N����\�����邩��
		// ���ƈꕶ��(2byte)���������Ɏ��Ȃ��悤�ɂ��ׂ�
		if (strIndex % 14 == 3 || strIndex % 14 == 8) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "�@�@��";
			strIndex+=3;
		}
		else if (strIndex == 70) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "�@��";
			strIndex += 2;
		}
		else if (strIndex == 74) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes;
			strIndex += 2;
		}
		else {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "��";
			strIndex++;
		}
	}
	else {
		stringRevive.erase(0);
		strIndex = 1;
		stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes +"��";
		strIndex++;
	}
}

void SceneLoveSong::resetString() {
	stringRevive.erase(0);
	strIndex = 1;
	stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + "��";
}


void SceneLoveSong::draw() const
{
	if (isMusicPlay) {
		DrawGraph(0, 0, Image::getIns()->getLoveSongBack(), FALSE);
		DrawRotaGraph(400 + 240, 400 + 135, 1.0, 0, Image::getIns()->getLoveSongMovie()[currentMovieIndex], FALSE, movieTurnFlag);
		DrawString(400, 30, "�ӂ����̂������� ����Ă�������", GetColor(255, 255, 255));

		// �������`��
		int strLength = strIndex * 2;
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				if (strLength > i * 28) {
					DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 36).c_str(), GetColor(255, 255, 255));
					if (strLength < (i + 1) * 28) {
						// �����������Ă���Ō�̍s
						break;
					}
				}
			}
			else {
				if (strLength > i * 28) {
					DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 28).c_str(), GetColor(255, 255, 255));
					if (strLength < (i + 1) * 28) {
						// �����������Ă���Ō�̍s
						break;
					}
				}
			}
		}
	}
	else {
		DrawRotaGraph(640, 360, 1.0, 0, Image::getIns()->getLoveSongLMovie()[currentMovieIndex], FALSE, movieTurnFlag);
	}
}
#pragma once
#include <vector>
#include "GameObject.h"
#include "Pad.h"

class Sozai : public GameObject
{
public:
	Sozai();
	~Sozai() {};
	void setMyId(int id) { myId = id; }
	bool update() override;
	void draw() const override;
	void setPosX(double xVal) { x = xVal; }
	void setPosY(double yVal) { y = yVal; }
	void setExRate(double val) { exRate = val; }
	void addSprite(const char* fileName);
	void setSampleSound(const char * fileName);
	void playSample(int, bool);
	void playWithSoundIndex(int);
	void setTriggerPad(int padEnum, int indexNum);
	void setTriggerMidi(int midiEnum, int indexNum);
	int getTriggerPad(int num) { return triggerPad[num]; };
	int getTriggerMidi(int num) { return triggerMidi[num]; };
	int getValidPadNum() { return validPadNum; }
	int getValidMidiNum() { return validMidiNum; }
	int getPadSoundIndex(int num) { return padSoundIndex[num]; }
	int getMidiSoundIndex(int num) { return midiSoundIndex[num]; }
	double getPosX() { return x; }
	double getPosY() { return y; }
	void setMultiSound(bool flag) { enableMultiSound = flag; }
	void setMultiGraph(bool flag) { enableMultiGraph = flag; }
	void setIsDrum(bool flag) { isDrum = flag; }
	void setPadReleaseStop(bool flag) { enablePadPlayStop = flag; }
	void setUseMovie(bool flag) { isMovie = flag; }
	void setUseTurn(bool flag) { enableTurn = flag; }
	void setPlayRate(int rate) { playRate = rate; }
	void setEnableMultiMovie(bool flag) { enableMultiSprite = flag; }
private:
	static const int maxSozai = 88;
	static const int maxPadSozai = 16;
	static const int maxMidiSozai = 88;
	static const int maxSpriteNum = 30;
	int myId;								// manager�N���X�̊Ǘ��ԍ�
	double x;
	double y;
	int transX;
	int transY;
	double exRate;
	int myGrapghHandle[maxSpriteNum];				
	int validGraphNum;
	std::vector<int> curGraphNum;
	int mySoundHandle[maxSozai];
	bool enableTurn;
	bool turnFlag;
	int validSoundNum;
	int curSoundIndex;						// �Đ����̉��n���h��
	int numOfPlayingSound;					// �Đ����̉��̐�
	int triggerPad[maxPadSozai];			// ���I�ɍ���������ǂ��� ���ƃN���X������ׂ�����
	int padSoundIndex[maxPadSozai];
	bool isPadSoundPlay[maxMidiSozai];
	int validPadNum;
	int triggerMidi[maxMidiSozai];
	int midiSoundIndex[maxMidiSozai];
	bool isMidiSoundPlay[maxMidiSozai];
	int validMidiNum;
	bool enableMultiSound;
	bool enableMultiGraph;
	int prevTime;
	bool isDrum;							// �Đ����~�߂Ȃ�����
	bool enablePadPlayStop;					// �L�[����w�𗣂��Ă��Đ���~
	bool isMovie;
	std::vector<int> timeForAnime;
	int playRate;							// �f���Đ����x(�~���b�H)
	bool enableMultiSprite;					// ���g�̉f�����I���܂ŕ`��
};


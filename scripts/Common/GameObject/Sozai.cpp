#include <Dxlib.h>
#include "Common/Image.h"
#include "Sozai.h"
#include "Common/Sound.h"
#include "System/Pad.h"
#include "System/MIDI.h"

Sozai::Sozai() :enablePadPlayStop(false)
{
	x = 0;
	y = 0;

	movieWrapper = nullptr;

	myId = -1;

	transX = 198;
	transY = 0;

	exRate = 1.0;

	enableTurn = true;
	turnFlag = false;

	for (int i = 0; i < maxSozai; i++)
	{
		soundHandles[i] = -1;
		midiSoundIndex[i] = 0;
		isPadSoundPlay[i] = false;
		isMidiSoundPlay[i] = false;
	}

	for (int i = 0; i < maxMidiSozai; i++)
	{
		triggerMidiNote[i] = 0;
		triggerMidiChannel[0] = 0;
	}

	validSoundNum = 0;
	validMidiNum = 0;

	curSoundIndex = -1;

	enableMultiSound = false;

	prevTime = GetNowCount();

	numOfPlayingSound = 0;

	isDrum = false;

	playRate = 88;

	enableMultiGraph = false;
	enableMultiSprite = false;
}

Sozai::~Sozai()
{
	// sound解放
	for (int i = 0; i < validSoundNum; i++)
	{
		if (soundHandles[i] != -1)
		{
			DeleteSoundMem(soundHandles[i]);
			soundHandles[i] = -1;
		}
	}

	// sprite解放
	for (auto& frames : graphHandles)
	{
		for (auto& handle : frames)
		{
			if (handle != -1)
			{
				DeleteGraph(handle);
			}
		}
	}

	// movie解放
	if (movieWrapper)
	{
		delete movieWrapper;
		movieWrapper = nullptr;
	}
}

bool Sozai::update()
{
	updatePlayingSoundCount();
	if (timeForAnime.size() != 0)
	{
		for (int i = 0; i < (int)timeForAnime.size(); i++)
		{
			int soundIndex = 0;

			if (i < animeSoundIndex.size())
				soundIndex = animeSoundIndex[i];
			
			int drawIndex = soundIndex;

			if (drawIndex < 0 || drawIndex >= graphHandles.size() || graphHandles[drawIndex].empty())
			{
				drawIndex = 0;
			}

			if (drawIndex >= graphHandles.size() || graphHandles[drawIndex].empty())
			{
				continue;
			}

			int frame = (GetNowCount() - timeForAnime[i]) / playRate;

			if (frame < 0) frame = 0;

			if (frame >= graphHandles[drawIndex].size())
			{
				curGraphNum[i] = (int)graphHandles[drawIndex].size() - 1;
				timeForAnime.erase(timeForAnime.begin() + i);
				animeSoundIndex.erase(animeSoundIndex.begin() + i);
				i--;
				continue;
			}
			else
			{
				curGraphNum[i] = frame;
			}
		}
	}

	for (int i = 0; i < triggerPad.size(); i++)
	{
		int tmpPadKey = triggerPad[i];

		if (isPadSoundPlay[i] == true &&
			Pad::getIns()->get(ePad(tmpPadKey)) == 0 &&
			enablePadPlayStop)
		{
			StopSoundMem(soundHandles[padSoundIndex[i]]);
			isPadSoundPlay[i] = false;
		}
	}

	for (int i = 0; i < validMidiNum; i++)
	{
		int note = triggerMidiNote[i];
		int channel = triggerMidiChannel[i];

		if (isMidiSoundPlay[i] == true &&
			MIDI::getIns()->get(note, channel) == 0)
		{
			if (!isDrum)
			{
				StopSoundMem(soundHandles[midiSoundIndex[i]]);
			}

			isMidiSoundPlay[i] = false;
		}
	}

	return true;
}

void Sozai::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	if (enableMultiGraph)
	{
		if (graphHandles.empty() || graphHandles[0].empty())
			return;

		for (int i = 0; i < numOfPlayingSound; i++)
		{
			DrawRotaGraph(
				(int)(x + transX * (numOfPlayingSound - 1 - i)),
				(int)(y + transY * (numOfPlayingSound - 1 - i)),
				exRate,
				0,
				graphHandles[0][0],
				TRUE,
				(enableTurn && turnFlag)
			);
		}
	}

	else if (enableMultiSprite)
	{
		if (curGraphNum.size() != 0)
		{
			for (int i = 0; i < curGraphNum.size(); i++)
			{
				int soundIndex = 0;

				if (i < animeSoundIndex.size())
					soundIndex = animeSoundIndex[i];

				int drawIndex = soundIndex;

				if (drawIndex < 0 || drawIndex >= graphHandles.size() || graphHandles[drawIndex].empty())
				{
					drawIndex = 0;
				}

				if (drawIndex >= graphHandles.size() || graphHandles[drawIndex].empty())
				{
					continue;
				}

				int frame = curGraphNum[i];

				if (frame >= graphHandles[drawIndex].size())
					frame = (int)graphHandles[drawIndex].size() - 1;

				DrawRotaGraph(
					static_cast<int>(x),
					static_cast<int>(y),
					exRate,
					0,
					graphHandles[drawIndex][frame],
					TRUE,
					(enableTurn && turnFlag)
				);
			}
		}
		else if (!graphHandles.empty() && !graphHandles[0].empty())
		{
			DrawRotaGraph(
				static_cast<int>(x),
				static_cast<int>(y),
				exRate,
				0,
				graphHandles[0][0],
				TRUE,
				(enableTurn && turnFlag)
			);
		}
	}

	else
	{
		if (curGraphNum.size() != 0)
		{
			int idx = (int)curGraphNum.size() - 1;

			int soundIndex = 0;

			if (idx < animeSoundIndex.size())
				soundIndex = animeSoundIndex[idx];

			int drawIndex = soundIndex;

			if (drawIndex < 0 || drawIndex >= graphHandles.size() || graphHandles[drawIndex].empty())
			{
				drawIndex = 0;
			}

			if (drawIndex < graphHandles.size() && !graphHandles[drawIndex].empty())
			{
				int frame = curGraphNum[idx];

				if (frame >= graphHandles[drawIndex].size())
					frame = (int)graphHandles[drawIndex].size() - 1;

				DrawRotaGraph(
					static_cast<int>(x),
					static_cast<int>(y),
					exRate,
					0,
					graphHandles[drawIndex][frame],
					TRUE,
					(enableTurn && turnFlag)
				);
			}
		}
		else if (!graphHandles.empty() && !graphHandles[0].empty())
		{
			DrawRotaGraph(
				static_cast<int>(x),
				static_cast<int>(y),
				exRate,
				0,
				graphHandles[0][0],
				TRUE,
				(enableTurn && turnFlag)
			);
		}
	}
}

void Sozai::setLayer(int val)
{
	layer = val;
}

int Sozai::getLayer() const
{
	return layer;
}

void Sozai::updatePlayingSoundCount()
{
	int count = 0;

	for (int i = 0; i < validSoundNum; i++)
	{
		if (CheckSoundMem(soundHandles[i]) == 1)
		{
			count++;
		}
	}

	numOfPlayingSound = count;
}
void Sozai::setTriggerPad(int padEnum, int soundIndexNum)
{
	triggerPad.push_back(padEnum);
	padSoundIndex.push_back(soundIndexNum);
}

void Sozai::resetTriggerPad()
{
	triggerPad.clear();
	padSoundIndex.clear();
}

void Sozai::resetTriggerMidi()
{
	for (int i = 0; i < validMidiNum; i++) {
		triggerMidiNote[i] = 0;
		triggerMidiChannel[i] = 0;
		midiSoundIndex[i] = 0;
	}
	validMidiNum = 0;
}

void Sozai::setTriggerMidi(int midiEnum, int soundIndexNum)
{
	if (validMidiNum < maxMidiSozai)
	{
		triggerMidiNote[validMidiNum] = midiEnum;
		triggerMidiChannel[validMidiNum] = 0;
		midiSoundIndex[validMidiNum] = soundIndexNum;
		validMidiNum++;
	}
}

void Sozai::setTriggerMidi(int midiEnum, int soundIndexNum, int channel)
{
	if (validMidiNum < maxMidiSozai)
	{
		triggerMidiNote[validMidiNum] = midiEnum;
		triggerMidiChannel[validMidiNum] = channel;
		midiSoundIndex[validMidiNum] = soundIndexNum;
		validMidiNum++;
	}
}

void Sozai::playSample(int sampleNum, bool isMidi)
{
	int soundIndex;

	if (isMidi)
		soundIndex = getMidiSoundIndex(sampleNum);
	else
		soundIndex = getPadSoundIndex(sampleNum);

	int tmpTime = GetNowCount();

	if (tmpTime - prevTime > 30)
		turnFlag = (!turnFlag);

	prevTime = tmpTime;

	if (curSoundIndex != -1 && !enableMultiSound)
	{
		StopSoundMem(soundHandles[curSoundIndex]);
	}

	if (soundIndex >= 0 && soundIndex < maxSozai)
	{
		if (soundHandles[soundIndex] != -1)
		{
			curSoundIndex = soundIndex;

			PlaySoundMem(soundHandles[curSoundIndex], DX_PLAYTYPE_BACK);


			if (isMidi)
				isMidiSoundPlay[sampleNum] = true;
			else
				isPadSoundPlay[sampleNum] = true;
		}
	}

	int startTime = GetNowCount();

	timeForAnime.clear();
	curGraphNum.clear();
	animeSoundIndex.clear();

	timeForAnime.push_back(startTime);
	curGraphNum.push_back(0);
	animeSoundIndex.push_back(soundIndex);
}

void Sozai::playWithSoundIndex(int soundIndex)
{
	int tmpTime = GetNowCount();

	if (tmpTime - prevTime > 30)
		turnFlag = (!turnFlag);

	prevTime = tmpTime;

	if (curSoundIndex != -1 && !enableMultiSound)
	{
		StopSoundMem(soundHandles[curSoundIndex]);
	}

	if (soundIndex >= 0 && soundIndex < maxSozai)
	{
		if (soundHandles[soundIndex] != -1)
		{
			curSoundIndex = soundIndex;

			PlaySoundMem(soundHandles[curSoundIndex], DX_PLAYTYPE_BACK);

		}
	}

	int startTime = GetNowCount();

	timeForAnime.clear();
	curGraphNum.clear();
	animeSoundIndex.clear();

	timeForAnime.push_back(startTime);
	curGraphNum.push_back(0);
	animeSoundIndex.push_back(soundIndex);
}

void Sozai::stopSound()
{
	if (curSoundIndex != -1 && !enableMultiSound)
	{
		StopSoundMem(soundHandles[curSoundIndex]);
	}
}

void Sozai::addSprite(const char* fileName)
{
	addSprite(0, fileName);
}

void Sozai::addSprite(int soundIndex, const char* fileName)
{
	if (graphHandles.size() <= soundIndex)
		graphHandles.resize(soundIndex + 1);

	std::string path(fileName);
	std::string ext;

	size_t dotPos = path.find_last_of(".");

	if (dotPos != std::string::npos)
	{
		ext = path.substr(dotPos + 1);

		for (auto& c : ext)
			c = tolower(c);
	}

	if (ext == "mp4" || ext == "avi" || ext == "webm")
	{
		MovieData movie = MovieImageWrapper::load(path);

		graphHandles[soundIndex].insert(
			graphHandles[soundIndex].end(),
			movie.handles.begin(),
			movie.handles.end()
		);

		if (!movie.handles.empty())
			playRate = movie.msPerFrame;
	}
	else
	{
		// 静止画・連番画像処理
		std::string baseStr = fileName;
		size_t extPos = baseStr.find_last_of('.');

		bool isSequential = false;
		std::string prefix = "";
		std::string extStr = "";
		int startNum = 0;
		int digitCount = 0;

		if (extPos != std::string::npos)
		{
			size_t numEnd = extPos;
			size_t numStart = numEnd;

			// 拡張子の直前から数字をカウント
			while (numStart > 0 && std::isdigit(static_cast<unsigned char>(baseStr[numStart - 1])))
			{
				numStart--;
			}

			// 数字が見つかった場合
			if (numStart < numEnd)
			{
				std::string numStr = baseStr.substr(numStart, numEnd - numStart);
				isSequential = true;
				prefix = baseStr.substr(0, numStart); // 例: ".../kick"
				extStr = baseStr.substr(extPos);      // 例: ".png"
				startNum = std::stoi(numStr);
				digitCount = numStr.length();
			}
		}

		if (isSequential)
		{
			// 連番画像の自動ロードループ
			int currentNum = startNum;
			while (true)
			{
				char numBuf[16];
				snprintf(numBuf, sizeof(numBuf), "%0*d", digitCount, currentNum);
				std::string targetFile = prefix + numBuf + extStr;

				int handle = LoadGraph(targetFile.c_str());
				if (handle == -1)
				{
					break; // ファイルが見つからなくなったら終了
				}

				graphHandles[soundIndex].push_back(handle);
				currentNum++;
			}

			if (!graphHandles[soundIndex].empty())
			{
				playRate = 33; // デフォルトは30fps
			}
		}
		else
		{
			// 単一画像読み込みフォールバック
			graphHandles[soundIndex].push_back(
				Image::getIns()->loadSamples(fileName)
			);
		}
	}
}

void Sozai::setSampleSound(const char* fileName)
{
	if (validSoundNum < maxSozai)
	{
		soundHandles[validSoundNum] =
			Sound::getIns()->loadSamples(fileName);

		validSoundNum++;
	}
}
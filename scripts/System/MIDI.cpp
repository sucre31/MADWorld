#pragma once
#include<Dxlib.h>
#include <mutex>
#include <string>
#include "System/MIDI.h"

std::queue<MidiMessage> MIDI::midiQueue;
std::mutex midiMutex;

MIDI::MIDI()
	: isGetInfoSucces(false)
{
	for (int i = 0; i < midiDeviceMax; i++) {
		midiHandle[i] = nullptr;
	}

	for (int note = 0; note < 128; note++) {
		for (int ch = 0; ch < 16; ch++) {
			_hold[note][ch] = 0;
			_trigger[note][ch] = false;
		}
	}
}

/*
@brief MIDIデバイスを開いて登録する
@param devid デバイスのid
@param midiIndex 配列に登録する番号
*/
void MIDI::openMidi(UINT devid, int midiIndex) {
	for (UINT i = 0; i < midiInGetNumDevs(); i++) {
		MIDIINCAPS caps;
		if (midiInGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
			//printfDx("ID %d : %s\n", i, caps.szPname);
		}
	}

	if (midiIndex < midiDeviceMax) {
		isGetInfoSucces = false;
		res = midiInOpen(&midiHandle[midiIndex], devid, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
		if (res != MMSYSERR_NOERROR) {
			printfDx("Cannot open MIDI input device %d\n", devid);
			printfDx("Error code: %d\n", res);
		}
		else {
			// MIDI入力の開始
			midiInStart(midiHandle[midiIndex]);
		}
	}
	else {
		printfDx("Cannot regist MIDI input device %d\n", midiIndex);
	}
	//MIDI Inputデバイスの情報
	midiresult = midiInGetDevCaps(devid, &midiininformation, sizeof(MIDIINCAPS));
	if (midiresult != MMSYSERR_NOERROR) {
		isGetInfoSucces = false;
	}
	else {
		isGetInfoSucces = true;
	}
}

void MIDI::closeMidi(int midiIndex){
	midiInStop(midiHandle[midiIndex]);
	midiInReset(midiHandle[midiIndex]);
	midiInClose(midiHandle[midiIndex]);
}

void MIDI::update()
{
	// ---- トリガー初期化（毎フレーム）----
	for (int note = 0; note < 128; note++) {
		for (int ch = 0; ch < 16; ch++) {
			_trigger[note][ch] = false;

			// 押され続けフレーム加算
			if (_hold[note][ch] > 0) {
				if (_hold[note][ch] < 255)
					_hold[note][ch]++;
			}
		}
	}

	// ---- メッセージ処理 ----
	while (true)
	{
		MidiMessage tmp;

		{
			std::lock_guard<std::mutex> lock(midiMutex);
			if (midiQueue.empty())
				break;

			tmp = midiQueue.front();
			midiQueue.pop();
		}

		unsigned char status = tmp.para1 & 0xFF;
		unsigned char type = status & 0xF0;
		unsigned char channel = status & 0x0F;
		unsigned char note = (tmp.para1 >> 8) & 0xFF;
		unsigned char velocity = (tmp.para1 >> 16) & 0xFF;

		if (note >= 128 || channel >= 16)
			continue;

		// NOTE ON
		if (type == 0x90 && velocity > 0) {
			_hold[note][channel] = 1;
			_trigger[note][channel] = true;   // ★これが重要
		}
		// NOTE OFF
		else if (type == 0x80 ||
			(type == 0x90 && velocity == 0)) {
			_hold[note][channel] = 0;
		}
	}
}

void MIDI::draw() {
	unsigned int Color;
	Color = GetColor(255, 255, 255);
	if (isGetInfoSucces) {
		//DrawFormatString(0, 700, Color, "%s", midiininformation.szPname);
	}
	//DrawFormatString(0, 0, Color, "note = %u\n", tmpNote);
}

/*
@brief 最後に開いたmidiデバイスの名前を取得
*/
TCHAR* MIDI::getMidiInfo() {
	return midiininformation.szPname;
}


void CALLBACK MIDI::MidiInProc(
	HMIDIIN,
	UINT MidiMsg,
	DWORD,
	DWORD dwPara1,
	DWORD dwPara2)
{
	if (MidiMsg == MIM_DATA) {
		std::lock_guard<std::mutex> lock(midiMutex);
		midiQueue.push({ MidiMsg, dwPara1, dwPara2 });
	}
}

/*!
@brief 渡されたMIDIキー番号の入力フレーム数を返す
*/
int MIDI::get(int note, int channel) const
{
	if (note < 0 || note >= 128) return 0;
	if (channel < 0 || channel >= 16) return 0;
	return _hold[note][channel];
}

int MIDI::get(int note) const
{
	if (note < 0 || note >= 128) return 0;
	return _hold[note][0];
}

// 押された瞬間（1フレームだけ true）
bool MIDI::isTrigger(int note, int channel) const
{
	if (note < 0 || note >= 128) return false;
	if (channel < 0 || channel >= 16) return false;
	return _trigger[note][channel];
}
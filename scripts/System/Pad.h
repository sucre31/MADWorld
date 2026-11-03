#pragma once

#include <array>
#include "System/Singleton.h"

enum ePad {
	down, left, right, up, A, B, Y, X, L, R, ZR, ZL, start, change, MAX
};

class Pad final : public Singleton<Pad> {

public:
	Pad();
	~Pad() = default;
	void update();
	int get(ePad eID) const;  //eIDのボタンの入力状態を取得

	void SetPadJoint(ePad padId, int num); // ゲーム側の入力番号とpadのキー番号を対応させる
	int GetPadJoint(ePad padId);

private:
	void merge();

	const static int PAD_KEY_NUM = 20;
	std::array<int, PAD_KEY_NUM> _idArray;  //どのボタンがどのボタンに割り当たっているかを示す
	std::array<int, PAD_KEY_NUM> _pad;      //16ボタンのpad入力状態格納

};
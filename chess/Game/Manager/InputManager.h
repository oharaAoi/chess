#pragma once
#include "MyVector2.h"
#include <Novice.h>

class InputManager final{

private:
	// キーの入力状況
	char keys_[256] = {0};
	char preKeys_[256] = { 0 };

	// mouseのpos
	static Vec2 mousePos_;
	static Vec2f mousePosf_;

	// コントローラーの入力
	Vec2 analogInputLeft_ = { 0,0 };
	Vec2 analogInputRight_ = { 0,0 };

	// パッドのボタン
	bool preButton_[20];

public:

	InputManager();
	~InputManager();

	void Update();

	// キーボードの入力
	bool IsTriggerKey(int DIK_key) const;
	bool IsPressKeys(int DIK_key) const;
	bool IsReleseKeys(int DIK_Key)const;

	// マウスの入力と座標
	bool IsTriggerMouse(int buttonNum) const;
	bool IsPressMouse(int buttomNum) const;
	static Vec2 GetMousePos() { return mousePos_; }
	static Vec2f GetMousePosf() { return mousePosf_; }

	// コントローラーの入力
	bool IsTriggerButton(PadButton button);
	bool IsPressButton(PadButton button);
	bool IsReleseButton(PadButton button);

	Vec2f GetAngleInputLeft() const {
		return Vec2f{ static_cast<float>(analogInputLeft_.x),static_cast<float>(analogInputLeft_.y) };
	}

	Vec2f GetAngleInputRight() const {
		return Vec2f{ static_cast<float>(analogInputRight_.x),static_cast<float>(analogInputRight_.y) };
	}

};


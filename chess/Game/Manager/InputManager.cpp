#include "InputManager.h"

Vec2 InputManager::mousePos_ = { 0,0 };
Vec2f InputManager::mousePosf_ = { 0,0 };

InputManager::InputManager(){
	for (int oi = 0; oi < 20; oi++) {
		preButton_[oi] = false;
	}
}

InputManager::~InputManager(){}

void InputManager::Update(){
	// キーボード入力
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
	mousePosf_ = { static_cast<float>(mousePos_.x) , static_cast<float>(mousePos_.y) };

	Novice::GetAnalogInputLeft(0, &analogInputLeft_.x, &analogInputLeft_.y);
	Novice::GetAnalogInputRight(0, &analogInputRight_.x, &analogInputRight_.y);

}

// キーボード
bool InputManager::IsTriggerKey(int DIK_key) const{
	return keys_[DIK_key] && !preKeys_[DIK_key];
}

bool InputManager::IsPressKeys(int DIK_key) const{
	return keys_[DIK_key];
}

bool InputManager::IsReleseKeys(int DIK_key) const {
	return  !keys_[DIK_key] && preKeys_[DIK_key];
}

// マウス
bool InputManager::IsTriggerMouse(int buttonNum) const{
	return Novice::IsTriggerMouse(buttonNum);
}

bool InputManager::IsPressMouse(int buttomNum) const{
	return Novice::IsPressMouse(buttomNum);
}

// コントローラー
bool InputManager::IsTriggerButton(PadButton button) {
	if (Novice::IsTriggerButton(0, button)) {
		preButton_[button] = true;
		return true;
	} else {
		preButton_[button] = false;
		return false;
	}

	/*return Novice::IsTriggerButton(0, button);*/
}

bool InputManager::IsPressButton(PadButton button){
	if (Novice::IsPressButton(0, button)) {
		preButton_[button] = true;
		return true;
	} else {
		preButton_[button] = false;
		return false;
	}

	/*return Novice::IsPressButton(0, button);*/
}

bool InputManager::IsReleseButton(PadButton button) {
	if (preButton_[button] == true && IsPressButton(button) == false) {
		return true;
	} else {
		return false;
	}
}

#include "PieceMovePlace.h"

PieceMovePlace::PieceMovePlace(const Vec2& address) {
	Init(address);
}

PieceMovePlace::~PieceMovePlace() {
}

void PieceMovePlace::Init(const Vec2& address) {
	pos_ = { address.x * 64.0f - 32.0f, address.y * 64.0f - 32.0f };
	size_ = { 64.0f, 64.0f };
	leftTop_ = { 0,0 };
	scale_ = { 1.0f, 1.0f };

	theta_ = 0;

	ScreenRectVertex(localVertex_, size_);
	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);

	color_ = 0xAA0000BB;

	GH_ = Novice::LoadTexture("white1x1.png");

	address_ = address;

	isMove_ = false;
}

void PieceMovePlace::Update() {
	// カーソルがあっているか判断
	CheackOnCursor(MyNovice::GetMousePosf());

	if (isCursorOn_) {
		IsClick();
	}

	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
}

void PieceMovePlace::Draw() {
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);
}

void PieceMovePlace::IsClick() {
	if (MyNovice::IsTriggerMouse(0)) {
		isMove_ = true;
	}
}


#include "BaseEntity.h"

void BaseEntity::CheackOnCursor(const Vec2f& mousePos) {
	Vec2 mouseAddress = { int(mousePos.y) / 64, int(mousePos.x) / 64 };

	if (address_.y == mouseAddress.x + 1 && address_.x == mouseAddress.y + 1) {
		isCursorOn_ = true;
	} else {
		isCursorOn_ = false;
	}
}

void BaseEntity::MoveAI(const Moved& move) {
	if (address_.x == move.fromMove.x && address_.y == move.fromMove.y) {
		address_ = move.toMove;
		pos_ = { address_.x * 64.0f - 32.0f, address_.y * 64.0f - 32.0f };

		isFirstMove_ = false;
	}
}

void BaseEntity::IsClicked() {
	if (isIdle_) {
		if (MyNovice::IsTriggerMouse(0)) {
			isIdle_ = false;
		}
	}

	if (isCursorOn_) {
		if (MyNovice::IsTriggerMouse(0)) {
			isIdle_ = true;
		}
	}
}

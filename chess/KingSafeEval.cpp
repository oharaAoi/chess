#include "KingSafeEval.h"

KingSafeEval::KingSafeEval() {
}

KingSafeEval::~KingSafeEval() {
}

void KingSafeEval::Init() {
}

int KingSafeEval::Eval(std::vector<std::vector<int>> boardArray, const Vec2& address) {
	boardArray_ = boardArray;
	int maxLine = static_cast<int>(boardArray_.size()) - 1;

	for (int oi = 0; oi < 8; oi++) {
		Vec2 checkAddress = address;
		checkAddress.x += movedX_[oi];
		checkAddress.y += movedY_[oi];

		bool isOver = false;

		// 値が範囲を超えているかをまず調べる
		if (checkAddress.x <= 0 || checkAddress.x >= maxLine) {
			isOver = true;
		}

		if (checkAddress.y <= 0 || checkAddress.y >= maxLine) {
			isOver = true;
		}

		if (!isOver) {
			if (boardArray_[checkAddress.y][checkAddress.x] / 10 == kPlayer) {
				return -1000;
			}
		}
	}

	return 0;
}

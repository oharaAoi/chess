#include "KingSafeEval.h"

KingSafeEval::KingSafeEval() {
}

KingSafeEval::~KingSafeEval() {
}

void KingSafeEval::Init() {
}

int KingSafeEval::Eval(std::vector<std::vector<int>> boardArray, const Vec2& address) {
	int result = 0;
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

		// 超えていなかったら
		if (!isOver) {
			if (boardArray_[checkAddress.y][checkAddress.x] / 10 == (kPlayer + 1)) {
				result+= -1000000000;
			}
		}
	}

	return result;
}

int KingSafeEval::ProtectEval(const std::vector<Vec2>& address, const std::vector<PlayerType>& playerType, const Vec2& kingAddress) {
	int result = 0;

	// キングの周りに移動する局面だったら
	for (size_t oi = 0; oi < address.size(); oi++) {
		for (int index = 0; index < 8; index++) {
			Vec2 addresses = { kingAddress.x + movedX_[index], kingAddress.y + movedY_[index] };
			
			if (playerType[oi] == kCPU) {
				if (addresses.x == address[oi].x && addresses.y == address[oi].y) {
					result += 1000000;
				}
			}
		}
	}

	return result;
}

//int KingSafeEval::ProtectToAttackPieceEval(const std::vector<Vec2>& address, const std::vector<PlayerType>& playerType, const std::vector<Vec2>& attackAddress) {
//	int result = 0;
//
//	for (size_t oi = 0; oi < address.size(); oi++) {
//		if (playerType[oi] == kCPU) {
//
//		}
//	}
//
//	return 0;
//}

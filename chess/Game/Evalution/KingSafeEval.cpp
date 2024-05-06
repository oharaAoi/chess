#include "KingSafeEval.h"

KingSafeEval::KingSafeEval(const int& maxRow, const int& maxCol) {
	maxRow_ = maxRow;
	maxCol_ = maxCol;
}

KingSafeEval::~KingSafeEval() {
}

void KingSafeEval::Init() {
}

int KingSafeEval::Eval(std::vector<std::vector<int>> boardArray) {
	int result = 0;
	kingAttackAddress_.clear();

	for (int row = 0; row < maxRow_; row++) {
		for (int col = 0; col < maxCol_; col++) {
			if (boardArray[row][col] / 10 == static_cast<int>(2)) {
				if (boardArray[row][col] % 10 == KingType) {
					kingAddress_ = { col, row };
				}
			}
		}
	}

	for (int oi = 0; oi < 8; oi++) {
		Vec2 checkAddress = kingAddress_;
		checkAddress.x += movedX_[oi];
		checkAddress.y += movedY_[oi];

		bool isOver = false;

		// 値が範囲を超えているかをまず調べる
		if (checkAddress.x <= 0 || checkAddress.x >= maxRow_) {
			isOver = true;
		}

		if (checkAddress.y <= 0 || checkAddress.y >= maxRow_) {
			isOver = true;
		}

		// 超えていなかったら
		if (!isOver) {
			if (boardArray[checkAddress.y][checkAddress.x] / 10 == (kPlayer + 1)) {
				result += -10000;
				kingAttackAddress_.push_back(checkAddress);
			} 
		}
	}

	return result;
}

int KingSafeEval::ProtectEval(std::vector<std::vector<int>> boardArray) {
	int result = 0;
	
	for (int oi = 0; oi < 8; oi++) {
		Vec2 checkAddress = kingAddress_;
		checkAddress.x += movedX_[oi];
		checkAddress.y += movedY_[oi];

		bool isOver = false;

		// 値が範囲を超えているかをまず調べる
		if (checkAddress.x <= 0 || checkAddress.x >= maxRow_) {
			isOver = true;
		}

		if (checkAddress.y <= 0 || checkAddress.y >= maxRow_) {
			isOver = true;
		}

		// 超えていなかったら
		if (!isOver) {
			for (int index = 0; index < kingAttackAddress_.size(); index++) {
				if (kingAttackAddress_[index].x == checkAddress.x && kingAttackAddress_[index].y == checkAddress.y) {
					result += 10000;
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

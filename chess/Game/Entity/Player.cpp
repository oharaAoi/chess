#include "Player.h"

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

Player::Player() {
	Init();
}

Player::~Player() {
}

void Player::Init() {
	// 初期位置の設定
	LoadFile::LoadPiceSetData("./Resources/json/piceSet.json");
	std::vector<std::vector<int>> setArry;
	setArry = LoadFile::GetPiceSetArr();

	// 行と列の数を取得
	int rows = static_cast<int>(setArry.size());
	int cols = 0;
	for (const auto& row : setArry) {
		if (row.size() > cols) {
			cols = static_cast<int>(row.size());
		}
	}

	//// piceの初期化
	//for (int row = 0; row < rows; row++) {
	//	for (int col = 0; col < cols; col++) {
	//		// アドレス
	//		Vec2 address = { row, col };

	//		switch (setArry[row][col]) {
	//		case PawnType:
	//			pawn_.push_back(std::make_unique<Pawn>(address));
	//			break;

	//		case KnightType:
	//			knight_.push_back(std::make_unique<Knight>(address));
	//			break;

	//		case BishopType:
	//			bishop_.push_back(std::make_unique<Bishop>(address));
	//			break;

	//		case RookType:
	//			rook_.push_back(std::make_unique<Rook>(address));
	//			break;

	//		case QueenType:
	//			queen_ = std::make_unique<Queen>(address);
	//			break;

	//		case KingType:
	//			king_ = std::make_unique<King>(address);
	//			break;
	//		}
	//	}
	//}

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			// アドレス
			Vec2 address = { col, row };

			switch (setArry[row][col]) {
			case PawnType:
				pices_.push_back(std::make_unique<Pawn>(address, kPlayer));
				break;

			case KnightType:
				pices_.push_back(std::make_unique<Knight>(address, kPlayer));
				break;

			case BishopType:
				pices_.push_back(std::make_unique<Bishop>(address, kPlayer));
				break;

			case RookType:
				pices_.push_back(std::make_unique<Rook>(address, kPlayer));
				break;

			case QueenType:
				pices_.push_back(std::make_unique<Queen>(address, kPlayer));
				break;

			case KingType:
				pices_.push_back(std::make_unique<King>(address, kPlayer));
				break;
			}
		}
	}

	isPoint_ = false;

	isLose_ = false;
}

void Player::Update() {
	// 駒の削除
	for (int oi = 0; oi < pices_.size(); oi++) {
		if (!pices_[oi]->GetIsAlive()) {
			// 勝敗の判定
			if (pices_[oi]->GetPieceType() == KingType) {
				isLose_ = true;
			}
			pices_.erase(pices_.begin() + oi);
		}
	}

	// 駒のupdate
	for (int oi = 0; oi < pices_.size(); oi++) {
		pices_[oi]->Update();

		if (pices_[oi]->GetPieceType() == KingType) {
			kingAddress_ = pices_[oi]->GetAddress();
		}

		// ピースのアップデート中に指されたらbreak
		if (pices_[oi]->GetIsPoint()) {
			isPoint_ = true;
			break;
		}
	}
}

void Player::Draw() {
	// 駒の描画
	for (int oi = 0; oi < pices_.size(); oi++) {
		pices_[oi]->Draw();
	}
}

void Player::BoardSetting() {
	for (int oi = 0; oi < pices_.size(); oi++) {
		Board::SetCurrentArray(pices_[oi]->GetAddress(), kPlayer, pices_[oi]->GetPieceType());
	}
}


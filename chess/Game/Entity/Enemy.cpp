#include "Enemy.h"

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

Enemy::Enemy() {
	Init();
}

Enemy::~Enemy() {
}

void Enemy::Init() {
	// 初期位置の設定
	LoadFile::LoadPiceSetData("./Resources/json/EnemyPiceSet.json");
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

	// 初期化
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			// アドレス
			Vec2 address = { col, row };

			switch (setArry[row][col]) {
			case PawnType:
				pices_.push_back(std::make_unique<Pawn>(address, kCPU));
				break;

			case KnightType:
				pices_.push_back(std::make_unique<Knight>(address, kCPU));
				break;

			case BishopType:
				pices_.push_back(std::make_unique<Bishop>(address, kCPU));
				break;

			case RookType:
				pices_.push_back(std::make_unique<Rook>(address, kCPU));
				break;

			case QueenType:
				pices_.push_back(std::make_unique<Queen>(address, kCPU));
				break;

			case KingType:
				pices_.push_back(std::make_unique<King>(address, kCPU));
				break;
			}
		}
	}

	isPoint_ = false;
	isLose_ = false;
}

void Enemy::Update() {
	// 駒のupdate
	for (int oi = 0; oi < pices_.size(); oi++) {
		pices_[oi]->Update();
	}
}

void Enemy::Draw() {
	// 駒の描画
	for (int oi = 0; oi < pices_.size(); oi++) {
		pices_[oi]->Draw();
	}
}

void Enemy::BoardSetting() {
	for (int oi = 0; oi < pices_.size(); oi++) {
		Board::SetCurrentArray(pices_[oi]->GetAddress(), kCPU, pices_[oi]->GetPieceType());
	}
}

void Enemy::AiPoint(const Moved& move) {
	for (int oi = 0; oi < pices_.size(); oi++) {
		pices_[oi]->MoveAI(move);
		pices_[oi]->SetIsPoint(false);
	}

	isPoint_ = true;
}

void Enemy::CheckIsAlive() {
	// 駒の削除
	for (int oi = 0; oi < pices_.size(); oi++) {
		if (!pices_[oi]->GetIsAlive()) {
			// 勝敗の判定
			if (pices_[oi]->GetPieceType() == KingType) {
				isLose_ = true;;
			}

			pices_.erase(pices_.begin() + oi);
		}
	}
}

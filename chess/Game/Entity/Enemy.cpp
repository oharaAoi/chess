﻿#include "Enemy.h"

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
				pices_.push_back(std::make_unique<Pawn>(address));
				break;

			case KnightType:
				pices_.push_back(std::make_unique<Knight>(address));
				break;

			case BishopType:
				pices_.push_back(std::make_unique<Bishop>(address));
				break;

			case RookType:
				pices_.push_back(std::make_unique<Rook>(address));
				break;

			case QueenType:
				pices_.push_back(std::make_unique<Queen>(address));
				break;

			case KingType:
				pices_.push_back(std::make_unique<King>(address));
				break;
			}
		}
	}
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
﻿#include "Board.h"

#include "Enemy.h"
#include "Player.h"
#include "BaseEntity.h"

std::vector<std::vector<int>> Board::currentArray_{};
std::vector<std::vector<int>> Board::keepArray_{};

Vec2 Board::kingAttackAddress_{};

Board::Board() {
	Init();
}

Board::~Board() {
}

//=================================================================================================================
//	↓　初期化
//=================================================================================================================
void Board::Init() {

	block_.clear();

	LoadFile::LoadMapData("./Resources/json/board.json");

	std::vector<std::vector<int>> mapArry;
	mapArry = LoadFile::GetMapArr();

	int rows = static_cast<int>(mapArry.size());
	int cols = 0;
	for (const auto& row : mapArry) {
		if (row.size() > cols) {
			cols = static_cast<int>(row.size());
		}
	}

	currentArray_.resize(rows);
	for (int i = 0; i < rows; ++i) {
		currentArray_[i].resize(cols);
	}

	// 行と列の上限値を決める
	maxRow_ = rows;
	maxCol_ = cols;

	isGameSet_ = false;

	int index = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			block_.push_back(std::make_unique<Block>());
			
			// 描画する左上座標を変更する
			switch (mapArry[row][col]) {
			case kBlockType::kNorn:
				block_[index]->SetType(kNorn);
				break;

			case kBlockType::kWhite:
				block_[index]->SetDrawLt({ 0,0 });
				block_[index]->SetType(kWhite);
				break;

			case kBlockType::kBlock:
				block_[index]->SetDrawLt({ 64,0 });
				block_[index]->SetType(kBlock);
				break;
			}

			//block_[index]->SetPos({ (col * 64.0f) - 256, (row * 64.0f) - 256 });
			block_[index]->SetPos({ (col * 64.0f) - 32.0f, (row * 64.0f) - 32.0f });

			index++;
		}
	}

	eval_ = 0;

	// 評価をするクラス
	pieceValueEval_ = std::make_unique<PieceValueEval>(maxRow_, maxCol_);
	piecePlaceEval_ = std::make_unique<PiecePlaceEval>(maxRow_, maxCol_);
	kingSafeEval_ = std::make_unique<KingSafeEval>(maxRow_, maxCol_);

	kingsAddress_ = std::make_unique<KingsAddress>();
}

//=================================================================================================================
//	↓　更新
//=================================================================================================================
void Board::Updata() {
	for (int oi = 0; oi < block_.size() - 1; oi++) {
		block_[oi]->Update();
	}

	int rows = static_cast<int>(currentArray_.size());
	int cols = 0;
	for (const auto& row : currentArray_) {
		if (row.size() > cols) {
			cols = static_cast<int>(row.size());
		}
	}
	// 一旦0でを代入しておく
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			currentArray_[row][col] = 0;
		}
	}

}

//=================================================================================================================
//	↓　描画
//=================================================================================================================
void Board::Draw() {
	for (int oi = 0; oi < block_.size() - 1; oi++) {
		if (block_[oi]->GetType() != kNorn) {
			block_[oi]->Draw();
		}
	}
}

void Board::SetCurrentArray(const Vec2& address, const PlayerType& playerType, const PieceType& pieceType) {
	// 今の盤面乗にある駒の種類を設定する
	int currentAddress = 0;

	if (playerType == kPlayer) {
		currentAddress += 10;
	} else {
		currentAddress += 20;
	}

	currentAddress += (int)pieceType;

	currentArray_[address.y][address.x] = currentAddress;
}


void Board::SetKingsAddress(const Vec2& player, const Vec2& cpu) {
	kingsAddress_->Update(player, cpu);
}

bool Board::GetingPlayerKing(const Vec2& cpuMoveAddress) {

	if (kingsAddress_->GetPlayerKingAddress().x == cpuMoveAddress.x && kingsAddress_->GetPlayerKingAddress().y == cpuMoveAddress.y) {
		return true;
	}

	return false;
}

/// <summary>
/// 今の盤面から動ける手をすべて生成する
/// </summary>
/// <returns></returns>
std::vector<Moved> Board::CreateCanMove(const std::vector<std::vector<int>>& board, const PlayerType& playerType) {
	std::vector<Moved> result{};

	if (playerType == kCPU) {
		for (const auto& entity : enemy_->GetPices()) {
			// 移動できる方向を駒ごとに取得
			std::vector<Moved> piceMove = entity->GetCanMove(board);
			// 取得した値を結果に格納
			for (int oi = 0; oi < piceMove.size(); oi++) {
				result.push_back(piceMove[oi]);
			}
		}
	} else {
		for (const auto& entity : player_->GetPices()) {
			// 移動できる方向を駒ごとに取得
			std::vector<Moved> piceMove = entity->GetCanMove(board);
			// 取得した値を結果に格納
			for (int oi = 0; oi < piceMove.size(); oi++) {
				result.push_back(piceMove[oi]);
			}
		}
	}

	return result;
}

/// <summary>
/// 引数の移動の情報を適用した配列を生成
/// </summary>
/// <param name="move"></param>
/// <returns></returns>
void Board::CreateMovedArray(const Moved& move) {
	// 移動する前の番号を保存して置く
	movePieceStack_.push(currentArray_[move.toMove.y][move.toMove.x]);

	if (currentArray_[move.toMove.y][move.toMove.x] != 0) {
		if (currentArray_[move.toMove.y][move.toMove.x] / 10 == kPlayer + 1) {
			for (const auto& entity : player_->GetPices()) {
				if (entity->GetAddress().x == move.toMove.x && entity->GetAddress().y == move.toMove.y) {
					entity->SetIsAlive(false);
					entityPtrStack_.push(entity.get());

				} 
			}
		} else {
			for (const auto& entity : enemy_->GetPices()) {
				if (entity->GetAddress().x == move.toMove.x && entity->GetAddress().y == move.toMove.y) {
					entity->SetIsAlive(false);
					entityPtrStack_.push(entity.get());
				}
			}
		}
	}

	// from(今の場所)の情報をto(移動する場所)に代入する
	currentArray_[move.toMove.y][move.toMove.x] = currentArray_[move.fromMove.y][move.fromMove.x];
	
	currentArray_[move.fromMove.y][move.fromMove.x] = 0;
	
}

/// <summary>
/// 移動を適用した配列を戻すための関数
/// </summary>
/// <param name="move"></param>
void Board::CreateUndoMovedArray(const Moved& move) {
	// toをfromに戻す
	currentArray_[move.fromMove.y][move.fromMove.x] = currentArray_[move.toMove.y][move.toMove.x];

	// toの場所には駒がなくなる
	currentArray_[move.toMove.y][move.toMove.x] = movePieceStack_.top();
	movePieceStack_.pop();

	if (!entityPtrStack_.empty()) {
		entityPtrStack_.top()->SetIsAlive(true);
		entityPtrStack_.pop();
	}
}

/// <summary>
/// 評価関数
/// </summary>
/// <returns></returns>
int Board::Evaluation() {
	// kingへ攻撃できる駒のアドレスを保存する配列
	std::vector<Vec2> canKingAttackAddress;
	kingAttackAddress_ = { 0,0 };
	// 結果の評価値
	int eval = 0;

	/* --------------------- 駒の価値で評価 --------------------- */
	eval = pieceValueEval_->Eval();

	/* --------------------- 駒の位置で評価 --------------------- */
	// アドレスト駒の対応を保存
	for (const auto& entity : player_->GetPices()) {
		if (entity->GetIsAlive()) {
			eval -= piecePlaceEval_->WhiteEval(currentArray_, entity->GetAddress(), entity->GetPieceType());
		}
	}

	for (const auto& entity : enemy_->GetPices()) {
		if (entity->GetIsAlive()) {
			eval += piecePlaceEval_->Eval(currentArray_, entity->GetAddress(), entity->GetPieceType());
		}
	}

	///* --------------------- 駒の可動性で評価をする --------------------- */
	for (const auto& entity : player_->GetPices()) {
		if (entity->GetIsAlive()) {
			int mobilityEval = entity->PieceMobility(currentArray_);
			eval -= mobilityEval;

			// 評価値からキングに攻撃できるアドレスを取得
			if (mobilityEval >= 10000) {
				kingAttackAddress_ = entity->GetAddress();
			}
		}
	}

	for (const auto& entity : enemy_->GetPices()) {
		if (entity->GetIsAlive()) {
			eval += entity->PieceMobility(currentArray_);
		}
	}

	/* --------------------- キングの安全性で評価する --------------------- */
	eval += kingSafeEval_->Eval(currentArray_);

	for (const auto& entity : player_->GetPices()) {
		if (entity->GetIsCheck() == isCPU) {
			eval -= 10000;
		}
	}

	return  eval;
}

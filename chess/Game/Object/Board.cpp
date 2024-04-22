#include "Board.h"

std::vector<std::vector<int>> Board::currentArray_{};

Board::Board() {
	Init();
}

Board::~Board() {
}

//=================================================================================================================
//	↓　初期化
//=================================================================================================================
void Board::Init() {
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

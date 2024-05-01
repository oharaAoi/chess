#include "Rook.h"

Rook::Rook(const Vec2& address, const PlayerType& type) {
	Init(address, type);
}

Rook::~Rook() {
}

void Rook::Init(const Vec2& address, const PlayerType& type) {
	LoadFile::LoadEntityData("./Resources/json/rook.json");
	// ファイルから読み取る
	scale_ = LoadFile::GetEntityState().scale;
	size_ = LoadFile::GetEntityState().size;
	leftTop_ = LoadFile::GetEntityState().leftTop;
	theta_ = LoadFile::GetEntityState().theta;

	pos_ = { address.x * 64.0f - 32.0f, address.y * 64.0f - 32.0f };
	velocity_ = { 0.0f, 0.0f };
	acceleration_ = { 0.0f, 0.0f };

	ScreenRectVertex(localVertex_, size_);
	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);

	color_ = 0xffffffff;

	address_ = address;

	isIdle_ = false;
	isPoint_ = false;
	isAlive_ = true;

	pieceType_ = RookType;

	if (type == kPlayer) {
		checkType_ = kCPU;
		coefficient_ = 1;
		GH_ = Novice::LoadTexture("./Resources/whitePiece.png");

	} else {
		checkType_ = kPlayer;
		coefficient_ = -1;
		GH_ = Novice::LoadTexture("./Resources/blackPiece.png");
	}
}

void Rook::Update() {
	isPoint_ = false;
	isPreIdle_ = isIdle_;
	// カーソルがあっているか判断
	CheackOnCursor(MyNovice::GetMousePosf());
	// クリックされたかを判断
	if (!isMoveCursolOn_) {
		IsClicked();
	}

	// 前のフレームで待機状態でないかつ今動けるなら動ける範囲の表示を生成する
	if (isPreIdle_ != isIdle_) {
		MovePlaceInit();
	}

	// 動ける状態の時に範囲を更新
	MovePlaceUpdate();

	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
}

void Rook::Draw() {
	CheackOnCursor(MyNovice::GetMousePosf());
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);

	MovePlaceDraw();
}

void Rook::Move(const Vec2& moveToAddress) {
	pos_ = { moveToAddress.x * 64.0f - 32.0f, moveToAddress.y * 64.0f - 32.0f };
	address_ = moveToAddress;
}

void Rook::MovedInit() {
	movePlaces_.clear();

	isPoint_ = true;
	isIdle_ = false;
	isCursorOn_ = false;
}

void Rook::MovePlaceInit() {
	std::vector<std::vector<int>> nowArray = Board::GetCurrentArray();
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	// 上方向を確認(味方か敵がいるアドレスまでの数を計算する)
	for (int row = address_.y + 1; row < maxLine; row++) {
		// 0だったら生成
		if (nowArray[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
		} else if (nowArray[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵がいた場合
			Vec2 address = { address_.x , row };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 下方向を確認
	for (int row = address_.y - 1; row >= 1; row--) {
		// 0だったら生成
		if (nowArray[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
		} else if (nowArray[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵がいた場合
			Vec2 address = { address_.x , row };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 右方向を確認
	for (int col = address_.x + 1; col < maxLine; col++) {
		// 0だったら生成
		if (nowArray[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
		} else if (nowArray[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵がいた場合
			Vec2 address = { col, address_.y };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 左方向を確認
	for (int col = address_.x - 1; col >= 1; col--) {
		// 0だったら生成
		if (nowArray[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
		} else if (nowArray[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵がいた場合
			Vec2 address = { col, address_.y };
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}
	}
}

void Rook::MovePlaceUpdate() {
	int onNum = 0;

	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Update();

			if (movePlaces_[oi]->GetIsCursorOn()) {
				onNum++;
			}

			// 範囲内にマウスがあってクリックされたら移動
			if (movePlaces_[oi]->GetIsMove()) {
				Move(movePlaces_[oi]->GetAddress());
				// 移動したら配列をクリアする
				movePlaces_.clear();

				isPoint_ = true;
				// フラグもfalseにする
				isIdle_ = false;
				isCursorOn_ = false;
			}
		}
	}

	if (onNum != 0) {
		isMoveCursolOn_ = true;
	} else {
		isMoveCursolOn_ = false;
	}
}

void Rook::MovePlaceDraw() {
	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Draw();
		}
	}
}

std::vector<Moved> Rook::GetCanMove(const std::vector<std::vector<int>>& board) {
	std::vector<Moved> result{};
	std::vector<std::vector<int>> nowArray = board;
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	// 上方向を確認(味方か敵がいるアドレスまでの数を計算する)
	for (int row = address_.y + 1; row < maxLine; row++) {
		// 0だったら生成
		if (nowArray[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			result.push_back({ address, address_ });
		} else if (nowArray[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { address_.x , row };
			result.push_back({ address, address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 下方向を確認
	for (int row = address_.y - 1; row >= 1; row--) {
		// 0だったら生成
		if (nowArray[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			result.push_back({ address, address_ });
		} else if (nowArray[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { address_.x , row };
			result.push_back({ address, address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 右方向を確認
	for (int col = address_.x + 1; col < maxLine; col++) {
		// 0だったら生成
		if (nowArray[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			result.push_back({ address, address_ });
		} else if (nowArray[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { col, address_.y };
			result.push_back({ address, address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 左方向を確認
	for (int col = address_.x - 1; col >= 1; col--) {
		// 0だったら生成
		if (nowArray[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			result.push_back({ address, address_ });
		} else if (nowArray[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { col, address_.y };
			result.push_back({ address, address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	return result;
}

int Rook::PieceMobility(const std::vector<std::vector<int>>& board) {
	int moveCount = 0;
	// 駒の配列と行列数
	int maxLine = static_cast<int>(board.size()) - 1;

	// 上方向を確認(味方か敵がいるアドレスまでの数を計算する)
	for (int row = address_.y + 1; row < maxLine; row++) {
		// 0だったら生成
		if (board[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			moveCount++;
		} else if (board[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { address_.x , row };
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[address.y][address.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 下方向を確認
	for (int row = address_.y - 1; row >= 1; row--) {
		// 0だったら生成
		if (board[row][address_.x] == 0) {
			Vec2 address = { address_.x , row };
			moveCount++;
		} else if (board[row][address_.x] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { address_.x , row };
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[address.y][address.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 右方向を確認
	for (int col = address_.x + 1; col < maxLine; col++) {
		// 0だったら生成
		if (board[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			moveCount++;
		} else if (board[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { col, address_.y };
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[address.y][address.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}

	// 左方向を確認
	for (int col = address_.x - 1; col >= 1; col--) {
		// 0だったら生成
		if (board[address_.y][col] == 0) {
			Vec2 address = { col, address_.y };
			moveCount++;
		} else if (board[address_.y][col] / 10 == static_cast<int>(checkType_ + 1)) {
			Vec2 address = { col, address_.y };
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[address.y][address.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}
	}
	return  mobility_[moveCount];
}

int Rook::PieceGetting(const PieceType& type) {
	switch (type) {
	case PawnType:
		return 10;

	case KnightType:
		return 40;

	case BishopType:
		return 40;

	case RookType:
		return 60;

	case QueenType:
		return 100;

	case KingType:
		return 1000;
	}

	return 0;
}

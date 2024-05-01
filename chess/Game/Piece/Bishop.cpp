#include "Bishop.h"

Bishop::Bishop(const Vec2& address, const PlayerType& type) {
	Init(address, type);
}

Bishop::~Bishop() {
}

void Bishop::Init(const Vec2& address, const PlayerType& type) {
	LoadFile::LoadEntityData("./Resources/json/bishop.json");
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

	pieceType_ = BishopType;

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

void Bishop::Update() {
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

void Bishop::Draw() {
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);

	MovePlaceDraw();
}

void Bishop::Move(const Vec2& moveToAddress) {
	pos_ = { moveToAddress.x * 64.0f - 32.0f, moveToAddress.y * 64.0f - 32.0f };
	address_ = moveToAddress;
}

void Bishop::MovedInit() {
	movePlaces_.clear();

	isPoint_ = true;
	isIdle_ = false;
	isCursorOn_ = false;
}

void Bishop::MovePlaceInit() {
	std::vector<std::vector<int>> nowArray = Board::GetCurrentArray();
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	Vec2 checkAddress = { address_.x + 1, address_.y + 1 };
	// 右上方向を確認する
	while (checkAddress.x != maxLine && checkAddress.y != maxLine) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));

		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵の駒があったら
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y + 1 };
	}

	// 左上を確認
	checkAddress = { address_.x - 1, address_.y + 1 };
	while (checkAddress.x != 0 && checkAddress.y != maxLine) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵の駒があったら
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y + 1 };
	}

	// 右下を確認
	checkAddress = { address_.x + 1, address_.y - 1 };
	while (checkAddress.x != maxLine && checkAddress.y != 0) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵の駒があったら
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y - 1 };
	}

	// 左下を確認
	checkAddress = { address_.x - 1, address_.y - 1 };
	while (checkAddress.x != 0 && checkAddress.y != 0) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 敵の駒があったら
			movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
			break;

		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y - 1 };
	}
}

void Bishop::MovePlaceUpdate() {
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

	// 移動マスをクリックした時に待機状態が解除されないように
	if (onNum != 0) {
		isMoveCursolOn_ = true;
	} else {
		isMoveCursolOn_ = false;
	}
}

void Bishop::MovePlaceDraw() {
	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Draw();
		}
	}
}

std::vector<Moved> Bishop::GetCanMove(const std::vector<std::vector<int>>& board) {
	std::vector<Moved> result{};
	std::vector<std::vector<int>> nowArray = board;
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	Vec2 checkAddress = { address_.x + 1, address_.y + 1 };
	// 右上方向を確認する
	while (checkAddress.x != maxLine && checkAddress.y != maxLine) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			result.push_back({ checkAddress , address_});
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			result.push_back({ checkAddress , address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y + 1 };
	}

	// 左上を確認
	checkAddress = { address_.x - 1, address_.y + 1 };
	while (checkAddress.x != 0 && checkAddress.y != maxLine) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			result.push_back({ checkAddress , address_ });

		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			result.push_back({ checkAddress , address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y + 1 };
	}

	// 右下を確認
	checkAddress = { address_.x + 1, address_.y - 1 };
	while (checkAddress.x != maxLine && checkAddress.y != 0) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			result.push_back({ checkAddress , address_ });
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			result.push_back({ checkAddress , address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y - 1 };
	}

	// 左下を確認
	checkAddress = { address_.x - 1, address_.y - 1 };
	while (checkAddress.x != 0 && checkAddress.y != 0) {
		// 0だったら生成
		if (nowArray[checkAddress.y][checkAddress.x] == 0) {
			result.push_back({ checkAddress , address_ });
		} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			result.push_back({ checkAddress , address_ });
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y - 1 };
	}

	return result;
}

int Bishop::PieceMobility(const std::vector<std::vector<int>>& board) {
	int moveCount = 0;

	int maxLine = static_cast<int>(board.size()) - 1;

	Vec2 checkAddress = { address_.x + 1, address_.y + 1 };
	// 右上方向を確認する
	while (checkAddress.x != maxLine && checkAddress.y != maxLine) {
		// 0だったら生成
		if (board[checkAddress.y][checkAddress.x] == 0) {
			moveCount++;
		} else if (board[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[checkAddress.y][checkAddress.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y + 1 };
	}

	// 左上を確認
	checkAddress = { address_.x - 1, address_.y + 1 };
	while (checkAddress.x != 0 && checkAddress.y != maxLine) {
		// 0だったら生成
		if (board[checkAddress.y][checkAddress.x] == 0) {
			moveCount++;

		} else if (board[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[checkAddress.y][checkAddress.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y + 1 };
	}

	// 右下を確認
	checkAddress = { address_.x + 1, address_.y - 1 };
	while (checkAddress.x != maxLine && checkAddress.y != 0) {
		// 0だったら生成
		if (board[checkAddress.y][checkAddress.x] == 0) {
			moveCount++;
		} else if (board[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[checkAddress.y][checkAddress.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x + 1, checkAddress.y - 1 };
	}

	// 左下を確認
	checkAddress = { address_.x - 1, address_.y - 1 };
	while (checkAddress.x != 0 && checkAddress.y != 0) {
		// 0だったら生成
		if (board[checkAddress.y][checkAddress.x] == 0) {
			moveCount++;
		} else if (board[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
			// 1(敵がいたら)だったら
			moveCount++;
			moveCount += PieceGetting(static_cast<PieceType>(board[checkAddress.y][checkAddress.x] % 10));
			break;
		} else {
			// 0以外があったらループを出る
			break;
		}

		checkAddress = { checkAddress.x - 1, checkAddress.y - 1 };
	}

	return mobility_[moveCount];
}

int Bishop::PieceGetting(const PieceType& type) {
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

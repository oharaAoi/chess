#include "Queen.h"

Queen::Queen(const Vec2& address, const PlayerType& type) {
	Init(address, type);
}

Queen::~Queen() {
}

void Queen::Init(const Vec2& address, const PlayerType& type) {
	LoadFile::LoadEntityData("./Resources/json/queen.json");
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

	pieceType_ = QueenType;

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

void Queen::Update() {
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

void Queen::Draw() {
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);

	MovePlaceDraw();
}


void Queen::Move(const Vec2& moveToAddress) {
	pos_ = { moveToAddress.x * 64.0f - 32.0f, moveToAddress.y * 64.0f - 32.0f };
	address_ = moveToAddress;
}

void Queen::MovedInit() {
	movePlaces_.clear();

	isPoint_ = true;
	isIdle_ = false;
	isCursorOn_ = false;
}

void Queen::MovePlaceInit() {
	std::vector<std::vector<int>> nowArray = Board::GetCurrentArray();
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	int movedX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int oi = 0; oi < 8; oi++) {
		for (int ai = 1; ai < 9; ai++) {
			Vec2 checkAddress = address_;
			checkAddress.x += ai * movedX[oi];
			checkAddress.y += ai * movedY[oi];

			bool isOver = false;

			// 値が範囲を超えているかをまず調べる
			if (checkAddress.x <= 0 || checkAddress.x >= maxLine) {
				isOver = true;
			}

			if (checkAddress.y <= 0 || checkAddress.y >= maxLine) {
				isOver = true;
			}


			if (!isOver) {
				if (nowArray[checkAddress.y][checkAddress.x] == 0) {
					movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
				} else if(nowArray[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
					// 敵がいたらbreak
					movePlaces_.push_back(std::make_unique<PieceMovePlace>(checkAddress));
					break;
				} else {
					break;
				}
			}
		}
	}
}

void Queen::MovePlaceUpdate() {
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

void Queen::MovePlaceDraw() {
	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Draw();
		}
	}
}

std::vector<Moved> Queen::GetCanMove(const std::vector<std::vector<int>>& board) {
	std::vector<Moved> result{};
	std::vector<std::vector<int>> nowArray = board;
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	int movedX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int oi = 0; oi < 8; oi++) {
		for (int ai = 1; ai < 9; ai++) {
			Vec2 checkAddress = address_;
			checkAddress.x += ai * movedX[oi];
			checkAddress.y += ai * movedY[oi];

			bool isOver = false;

			// 値が範囲を超えているかをまず調べる
			if (checkAddress.x <= 0 || checkAddress.x >= maxLine) {
				isOver = true;
			}

			if (checkAddress.y <= 0 || checkAddress.y >= maxLine) {
				isOver = true;
			}

			if (!isOver) {
				if (nowArray[checkAddress.y][checkAddress.x] == 0) {
					result.push_back({ checkAddress , address_ });
				} else if (nowArray[checkAddress.y][checkAddress.x] / 2 == static_cast<int>(checkType_ + 1)) {
					// 敵がいたらbreak
					result.push_back({ checkAddress , address_ });
					break;
				} else {
					break;
				}
			}
		}
	}

	return result;
}

int Queen::PieceMobility(const std::vector<std::vector<int>>& board) {
	int result = 0;
	int moveCount = 0;
	int gettenCount = 0;

	// 駒の配列と行列数
	int maxLine = static_cast<int>(board.size()) - 1;
	
	int movedX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int oi = 0; oi < 8; oi++) {
		for (int ai = 1; ai < 9; ai++) {
			Vec2 checkAddress = address_;
			checkAddress.x += ai * movedX[oi];
			checkAddress.y += ai * movedY[oi];

			bool isOver = false;

			// 値が範囲を超えているかをまず調べる
			if (checkAddress.x <= 0 || checkAddress.x >= maxLine) {
				isOver = true;
			}

			if (checkAddress.y <= 0 || checkAddress.y >= maxLine) {
				isOver = true;
			}

			if (!isOver) {
				if (board[checkAddress.y][checkAddress.x] == 0) {
					moveCount++;
				} else if (board[checkAddress.y][checkAddress.x] / 10 == static_cast<int>(checkType_ + 1)) {
					// 敵がいたらbreak
					moveCount++;
					gettenCount += PieceGetting(static_cast<PieceType>(board[checkAddress.y][checkAddress.x] % 10));
					break;
				} else {
					break;
				}
			}
		}
	}

	result =  gettenCount;

	return result;
}

int Queen::PieceGetting(const PieceType& type) {
	switch (type) {
	case PawnType:
		return 100;

	case KnightType:
		return 400;

	case BishopType:
		return 400;

	case RookType:
		return 600;

	case QueenType:
		return 100;

	case KingType:
		return 100000;
	}

	return 0;
}

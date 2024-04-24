#include "King.h"

King::King(const Vec2& address) {
	Init(address);
}

King::~King() {
}

void King::Init(const Vec2& address) {
	LoadFile::LoadEntityData("./Resources/json/king.json");
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

	GH_ = Novice::LoadTexture("./Resources/pices.png");

	address_ = address;

	isIdle_ = false;
	isPoint_ = false;

	pieceType_ = KingType;
}

void King::Update() {
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

void King::Draw() {
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);

	MovePlaceDraw();
}

void King::Move(const Vec2& moveToAddress) {
	pos_ = { moveToAddress.x * 64.0f - 32.0f, moveToAddress.y * 64.0f - 32.0f };
	address_ = moveToAddress;
}

void King::MovedInit() {
	pos_ = { address_.x * 64.0f - 32.0f, address_.y * 64.0f - 32.0f };
	movePlaces_.clear();

	isPoint_ = true;
	isIdle_ = false;
	isCursorOn_ = false;
}

void King::MovePlaceInit() {
	std::vector<std::vector<int>> nowArray = Board::GetCurrentArray();
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	int movedX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int oi = 0; oi < 8; oi++) {
		Vec2 checkAddress = address_;
		checkAddress.x += movedX[oi];
		checkAddress.y += movedY[oi];

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
			}
		}
	}
}

void King::MovePlaceUpdate() {
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

void King::MovePlaceDraw() {
	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Draw();
		}
	}
}

std::vector<Moved> King::GetCanMove(const std::vector<std::vector<int>>& board) {
	std::vector<Moved> result{};
	std::vector<std::vector<int>> nowArray = board;
	// 入れつからアドレスを計算する最大値を計算する
	int maxLine = static_cast<int>(nowArray.size()) - 1;

	int movedX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int oi = 0; oi < 8; oi++) {
		Vec2 checkAddress = address_;
		checkAddress.x += movedX[oi];
		checkAddress.y += movedY[oi];

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
				result.push_back({ checkAddress, address_ });
			} else if (nowArray[checkAddress.y][checkAddress.x] / 10 == 1) {
				result.push_back({ checkAddress, address_ });
			}
		}
	}

	return result;
}

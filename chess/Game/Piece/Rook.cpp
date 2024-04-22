#include "Rook.h"

Rook::Rook(const Vec2& address) {
	Init(address);
}

Rook::~Rook() {
}

void Rook::Init(const Vec2& address) {
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

	GH_ = Novice::LoadTexture("./Resources/pices.png");

	address_ = address;

	isIdle_ = false;

	pieceType_ = RookType;
}

void Rook::Update() {
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

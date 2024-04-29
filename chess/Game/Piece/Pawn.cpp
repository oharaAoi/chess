#include "Pawn.h"

Pawn::Pawn(const Vec2& address, const PlayerType& type){
	Init(address, type);
}

Pawn::~Pawn(){
}

//=================================================================================================================
//	↓　初期化
//=================================================================================================================
void Pawn::Init(const Vec2& address, const PlayerType& type){
	LoadFile::LoadEntityData("./Resources/json/pawn.json");
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

	pieceType_ = PawnType;

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

//=================================================================================================================
//	↓　更新
//=================================================================================================================
void Pawn::Update(){
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

//=================================================================================================================
//	↓　描画
//=================================================================================================================
void Pawn::Draw(){
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);

	MovePlaceDraw();
}

void Pawn::Move(const Vec2& moveToAddress) {
	pos_ = { moveToAddress.x * 64.0f - 32.0f, moveToAddress.y * 64.0f - 32.0f };
	address_ = moveToAddress;
}

void Pawn::MovedInit() {
	movePlaces_.clear();

	isPoint_ = true;
	isIdle_ = false;
	isCursorOn_ = false;
}

//=================================================================================================================
//	↓　動ける範囲の処理
//=================================================================================================================
void Pawn::MovePlaceInit() {
	std::vector<std::vector<int>> nowArray = Board::GetCurrentArray();
	// 上を確認
	// 0(何もなかったら生成)
	if (nowArray[address_.y + (1 * coefficient_)][address_.x] == 0) {
		Vec2 address = { address_.x , address_.y + (1 * coefficient_) };
		movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
	}

	// 右上と左上を確認して敵の駒があったら取れる
	if (nowArray[address_.y + (1 * coefficient_)][address_.x + 1 ] / 10 == static_cast<int>(checkType_ + 1)) {
		Vec2 address = { address_.x + 1 , address_.y + (1 * coefficient_) };
		movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
	}

	if (nowArray[address_.y + (1 * coefficient_)][address_.x - 1] / 10 == static_cast<int>(checkType_ + 1)) {
		Vec2 address = { address_.x - 1 , address_.y + (1 * coefficient_) };
		movePlaces_.push_back(std::make_unique<PieceMovePlace>(address));
	}
}

void Pawn::MovePlaceUpdate() {
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

void Pawn::MovePlaceDraw() {
	if (isIdle_) {
		for (int oi = 0; oi < movePlaces_.size(); oi++) {
			movePlaces_[oi]->Draw();
		}
	}
}

/// <summary>
/// 敵と味方で反転しないと行けない
/// </summary>
/// <returns></returns>
std::vector<Moved> Pawn::GetCanMove(const std::vector<std::vector<int>>& board) {
	std::vector<Moved> result{};
	std::vector<std::vector<int>> nowArray = board;
	// 上を確認
	// 0(何もなかったら生成)
	if (nowArray[address_.y + (1 * coefficient_)][address_.x] == 0) {
		Vec2 address = { address_.x , address_.y + (1 * coefficient_) };
		result.push_back({ address , address_ });
	}

	// 右上を確認(敵がいたらtrue)
	if (nowArray[address_.y + (1 * coefficient_)][address_.x + 1] / 10 == 1) {
		Vec2 address = { address_.x + 1 , address_.y + (1 * coefficient_) };
		result.push_back({ address , address_ });
	}

	// 左上を確認(敵がいたらtrue)
	if (nowArray[address_.y + (1 * coefficient_)][address_.x - 1] / 10 == 1) {
		Vec2 address = { address_.x - 1 , address_.y + (1 * coefficient_) };
		result.push_back({ address , address_ });
	}

	return result;
}

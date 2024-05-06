#pragma once
#include "MyNovice.h"
#include "Matrix.h"
#include "MyMath.h"

enum PlayerType {
	kPlayer,
	kCPU
};

enum PieceType {
	PawnType = 1,
	KnightType,
	BishopType,
	RookType,
	QueenType,
	KingType
};

struct Moved {
	Vec2 toMove;
	Vec2 fromMove;
	int32_t eval;
};

enum IsCheckMate {
	cannt,
	isPlayer,
	isCPU
};


class BaseEntity{
public:

	BaseEntity() = default;
	virtual	~BaseEntity() = default;

	void Init();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void CheackOnCursor(const Vec2f& mousePos);

	virtual void MoveAI(const Moved& move);

	virtual void IsClicked();

	virtual bool GetIsPoint() const { return isPoint_; }
	virtual void SetIsPoint(const bool& isPoint) { isPoint_ = isPoint; }

	virtual bool GetIsAlive() const { return isAlive_; }
	virtual void SetIsAlive(const bool& isAlive) { isAlive_ = isAlive; }

	virtual IsCheckMate GetIsCheck() const { return isCheck_; }

public:

	virtual Vec2 GetAddress() const { return address_; }

	virtual PieceType GetPieceType() const { return pieceType_; }

	virtual std::vector<Moved> GetCanMove(const std::vector<std::vector<int>>& board) = 0;

	/// <summary>
	/// 駒の可動性
	/// </summary>
	/// <returns>駒が何マス動けるか</returns>
	virtual int PieceMobility(const std::vector<std::vector<int>>& board) = 0;

	virtual int PieceGetting(const PieceType& type) = 0;

protected:

	Vec2f pos_;
	Vec2f size_;
	Vec2f scale_;
	Vec2f leftTop_;
	Vec2f velocity_;
	Vec2f acceleration_;

	float theta_;

	Vec2 address_;

	// 各頂点
	RectVerf localVertex_;
	RectVerf worldVertex_;
	RectVerf screenVertex_;

	// 行列
	Matrix3x3 worldMatrix_;
	Matrix3x3 screenMatrix_;

	unsigned int color_;
 
	bool isAlive_;

	// マウスが上にあるかを判断
	bool isCursorOn_;

	// 動く待機状態か判断する
	bool isIdle_;
	bool isPreIdle_;

	bool isPoint_;

	bool isFirstMove_ = false;

	PieceType pieceType_;

	// 駒がプレイヤーを取るかCPUを取るか
	PlayerType checkType_;

	// プラスかマイナスの係数
	int coefficient_;

	IsCheckMate isCheck_;
};



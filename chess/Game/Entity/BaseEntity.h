#pragma once
#include "MyNovice.h"
#include "Matrix.h"
#include "MyMath.h"

enum PieceType {
	PawnType = 1,
	KnightType,
	BishopType,
	RookType,
	QueenType,
	KingType
};

class BaseEntity{
public:

	BaseEntity() = default;
	virtual	~BaseEntity() = default;

	void Init();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void CheackOnCursor(const Vec2f& mousePos);

	virtual void IsClicked();

public:

	virtual Vec2 GetAddress() const { return address_; }

	virtual PieceType GetPieceType() const { return pieceType_; }

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

	PieceType pieceType_;
};



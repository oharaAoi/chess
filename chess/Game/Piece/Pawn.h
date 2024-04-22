#pragma once
#include "BaseEntity.h"
#include "LoadFile.h"
#include "DrawUtils.h"
#include "PieceMovePlace.h"
#include "Board.h"

class Pawn
: public BaseEntity{
public:

	Pawn(const Vec2& address);
	virtual ~Pawn();

	void Init(const Vec2& address);
	void Update()override;
	void Draw()override;

public:


public:

	void Move(const Vec2& moveToAddress);

	// 移動範囲に関する関数
	void MovePlaceInit();

	void MovePlaceUpdate();

	void MovePlaceDraw();

private:

	int GH_;

	bool isMoveCursolOn_;

	// 動ける方向を示すブロックのポインタを格納した配列
	std::vector<std::unique_ptr<PieceMovePlace>> movePlaces_;

};


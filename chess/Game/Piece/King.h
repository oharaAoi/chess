#pragma once
#include "BaseEntity.h"
#include "LoadFile.h"
#include "DrawUtils.h"
#include "PieceMovePlace.h"
#include "Board.h"

class King 
	: public BaseEntity {
public:

	King(const Vec2& address);
	virtual ~King();

	void Init(const Vec2& address);
	void Update()override;
	void Draw()override;

public:

	void Move(const Vec2& moveToAddress);

	// 移動範囲に関する関数
	void MovePlaceInit();

	void MovePlaceUpdate();

	void MovePlaceDraw();

	/// <summary>
	/// 移動できる方向を配列に代入して返す
	/// </summary>
	/// <returns></returns>
	std::vector<Moved> GetCanMove() override;

private:

	int GH_;

	bool isMoveCursolOn_;

	// 動ける方向を示すブロックのポインタを格納した配列
	std::vector<std::unique_ptr<PieceMovePlace>> movePlaces_;

};

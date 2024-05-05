#pragma once
#include "BaseEntity.h"
#include "LoadFile.h"
#include "DrawUtils.h"
#include "PieceMovePlace.h"
#include "Board.h"

class Queen
	: public BaseEntity {
public:

	Queen(const Vec2& address, const PlayerType& type);
	virtual ~Queen();

	void Init(const Vec2& address, const PlayerType& type);
	void Update()override;
	void Draw()override;

public:

	void Move(const Vec2& moveToAddress);

	/// <summary>
	/// 動いた後の処理
	/// </summary>
	void MovedInit();

	// 移動範囲に関する関数
	void MovePlaceInit();

	void MovePlaceUpdate();

	void MovePlaceDraw();

	/// <summary>
	/// 移動できる方向を配列に代入して返す
	/// </summary>
	/// <returns></returns>
	std::vector<Moved> GetCanMove(const std::vector<std::vector<int>>& board) override;

	/// <summary>
	/// 駒の可動性を評価
	/// </summary>
	/// <returns></returns>
	int PieceMobility(const std::vector<std::vector<int>>& board) override;

	int PieceGetting(const PieceType& type) override;

private:

	int GH_;

	bool isMoveCursolOn_;

	// 動ける方向を示すブロックのポインタを格納した配列
	std::vector<std::unique_ptr<PieceMovePlace>> movePlaces_;

	// 可動性の評価値
	int mobility_[19] = { -141, -30, -30, -7, 19, 40, 55, 59, 75, 78, 96, 96, 100, 121, 127, 131, 133, 136, 141 };

};



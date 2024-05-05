#pragma once
#include "BaseEntity.h"
#include "LoadFile.h"
#include "DrawUtils.h"
#include "PieceMovePlace.h"
#include "Board.h"

class Rook
	: public BaseEntity {
public:

	Rook(const Vec2& address, const PlayerType& type);
	virtual ~Rook();

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
	int mobility_[16] = { -62, -60, -20, 2, 3, 3, 11, 22, 32, 40, 40, 41, 48, 57, 57, 62 };

};



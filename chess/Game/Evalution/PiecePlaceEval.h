#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include "LoadFile.h"
#include <memory>
#include <vector>
#include <unordered_map>

/// <summary>
/// 駒の位置によって評価するクラス
/// </summary>
class PiecePlaceEval {
public:

	PiecePlaceEval(const int& maxRow, const int& maxCol);
	~PiecePlaceEval();

	void Init();

	int Eval(const Vec2& address, const PieceType& type);

private:

	std::vector<std::vector<int>> pownSquareTable_;
	std::vector<std::vector<int>> knightSquareTable_;
	std::vector<std::vector<int>> bishopSquareTable_;
	std::vector<std::vector<int>> rookSquareTable_;
	std::vector<std::vector<int>> queenSquareTable_;
	std::vector<std::vector<int>> kingSquareTable_;

	int maxRow_;
	int maxCol_;

};


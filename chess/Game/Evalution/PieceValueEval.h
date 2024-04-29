#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include <memory>
#include <vector>
#include <unordered_map>

class Board;

/// <summary>
/// 駒の価値で評価するクラス
/// </summary>
class PieceValueEval {
public:

	PieceValueEval(const int& maxRow, const int& maxCol);
	~PieceValueEval();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 評価
	/// </summary>
	int Eval();

private:

	std::unordered_map<std::string, int> pieceValues_ = {
	{"PawnType", 142}, {"KnightType", 784}, {"BishopType", 828}, {"RookType", 1286},
	{"QueenType", 2528}, {"KingType", 0}
	};

	int maxRow_;
	int maxCol_;

};


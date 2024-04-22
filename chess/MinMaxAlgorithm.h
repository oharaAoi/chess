#pragma once
#include "MyVector2.h"
#include "BaseEntity.h"
#include "MyMath.h"
#include "Board.h"

struct EvalDate {
	Vec2 moveToIndex;// どこのアドレスに移動するか
	int evaluation; // 評価値
	PieceType type;	// どの種類の駒を移動さるか
};

/// <summary>
/// minmaxアルゴリズムを行うクラス
/// </summary>
class MinMaxAlgorithm {

public:

	MinMaxAlgorithm();
	~MinMaxAlgorithm();

	/// <summary>
	/// 評価関数
	/// </summary>
	/// <param name="depth"></param>
	/// <param name="maximizingPlayer"></param>
	//int minmax(int depth, int alpha, int beta, bool maximizingPlayer);

private:



};


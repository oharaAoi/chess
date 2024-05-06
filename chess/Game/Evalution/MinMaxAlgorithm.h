#pragma once
#include "MyVector2.h"
#include "BaseEntity.h"
#include "MyMath.h"
#include "Board.h"

#include <limits>
#include <algorithm>
#include <functional>
#include <cassert>

struct EvalDate {
	int32_t eval;
	int32_t alpha;
	int32_t beta;
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
	int AlphaBeta(int depth, int alpha, int beta, bool maximizingPlayer);

	Moved FindBestMove(int depth);

	void SetBoard(Board* board) { board_ = board; };

	//
	int32_t GetRoopCount() const { return roopCount_; }

	int32_t GetEval() const { return eval_; }
 
private:

	Board* board_ = nullptr;

	// 何回AlphaBeta関数を行ったか
	int32_t roopCount_;

	// 出した評価値
	int32_t eval_ = 0;

	int32_t alpha_ = 0;
	int32_t beta_ = 0;

};


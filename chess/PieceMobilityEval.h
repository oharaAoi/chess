#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include <memory>
#include <vector>
#include <unordered_map>

class PieceMobilityEval {
public:

	PieceMobilityEval();
	~PieceMobilityEval();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 評価
	/// </summary>
	int Eval();

private:


};


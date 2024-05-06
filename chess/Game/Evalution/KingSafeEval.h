#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include "LoadFile.h"
#include <memory>
#include <vector>
#include <stack>
#include <unordered_map>

class KingSafeEval {
public:

	KingSafeEval(const int& maxRow, const int& maxCol);
	~KingSafeEval();

	void Init();

	int Eval(std::vector<std::vector<int>> boardArray);

	/// <summary>
	/// キングの周りに来れる駒があるかを評価
	/// </summary>
	/// <param name="address">盤面のアドレス</param>
	/// <param name="playerType">アドレスの操作タイプ</param>
	/// <param name="kingAddress">キングのアドレス</param>
	/// <returns></returns>
	int ProtectEval(std::vector<std::vector<int>> boardArray);

	/// <summary>
	/// 攻撃する駒を取ることができるかの評価
	/// </summary>
	/// <param name="address">盤面のアドレス</param>
	/// <param name="playerType">アドレスの操作タイプ</param>
	/// <param name="attackAddress">攻撃する駒のアドレス</param>
	/// <returns></returns>
	//int ProtectToAttackPieceEval(const std::vector<Vec2>& address, const std::vector<PlayerType>& playerType, const std::vector<Vec2>& attackAddress);

private:

	std::vector<std::vector<int>> boardArray_;

	int movedX_[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY_[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	int maxRow_;
	int maxCol_;

	Vec2 kingAddress_;

	std::vector<Vec2> kingAttackAddress_;
};


#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include "LoadFile.h"
#include <memory>
#include <vector>
#include <unordered_map>

class KingSafeEval {
public:

	KingSafeEval();
	~KingSafeEval();

	void Init();

	int Eval(std::vector<std::vector<int>> boardArray, const Vec2& address);

	int ProtectEval(const std::vector<Vec2>& address, std::vector<PlayerType> playerType, const Vec2& kingAddress);

private:

	std::vector<std::vector<int>> boardArray_;

	int movedX_[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int movedY_[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

};


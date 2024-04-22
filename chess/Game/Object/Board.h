#pragma once
#include <memory>
#include <vector>

#include "Block.h"
#include "LoadFile.h"
#include "BaseEntity.h"

enum PlayerType {
	kPlayer,
	kCPU
};

class Board {
public:

	Board();
	~Board();

	void Init();
	void Updata();
	void Draw();

public:

	static std::vector<std::vector<int>> GetCurrentArray() { return currentArray_; }

	static void SetCurrentArray(const Vec2& address, const PlayerType& playerType, const PieceType& pieceType);

private:

	std::vector<std::unique_ptr<Block>> block_;

	static std::vector<std::vector<int>> currentArray_;

};


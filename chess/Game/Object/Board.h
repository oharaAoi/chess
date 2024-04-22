#pragma once
#include <memory>
#include <vector>

#include "Block.h"
#include "LoadFile.h"
#include "BaseEntity.h"

class Enemy;
class BaseEntity;

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

	/// <summary>
	/// エネミーのインスタンスを保持
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

public:

	std::vector<Moved> CreateCanMove();

private:

	std::vector<std::unique_ptr<Block>> block_;

	static std::vector<std::vector<int>> currentArray_;

	// エネミーのインスタンスを保持しておく(pieceにアクセスするため)
	Enemy* enemy_ = nullptr;

};


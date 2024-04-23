#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Block.h"
#include "LoadFile.h"
#include "BaseEntity.h"

class Enemy;
class Player;
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
	/// エネミーのインスタンスをセット
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

	/// <summary>
	/// プレイヤーのインスタンスをセット
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player) { player_ = player; }

public:

	/// <summary>
	/// 今の盤面から動ける手をすべて生成する
	/// </summary>
	/// <returns></returns>
	std::vector<Moved> CreateCanMove(const std::vector<std::vector<int>>& board, const PlayerType& playerType);

	/// <summary>
	/// 引数の移動の情報を適用した配列を生成
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	void CreateMovedArray(const Moved& move);

	/// <summary>
	/// 移動を適用した配列を戻すための関数
	/// </summary>
	/// <param name="move"></param>
	void CreateUndoMovedArray(const Moved& move);

	/// <summary>
	/// 引数のボードからボード全体の評価を
	/// </summary>
	/// <param name="board"></param>
	/// <returns></returns>
	int Evaluation();

private:

	std::unordered_map<std::string, int> pieceValues_ = {
		{"PawnType", 100}, {"KnightType", 400}, {"BishopType", 400}, {"RookType", 600},
		{"QueenType", 1200}, {"KingType", 1000000}
	};

	std::vector<std::vector<int>> pownSquareTable_;

	std::vector<std::unique_ptr<Block>> block_;

	static std::vector<std::vector<int>> currentArray_;

	int maxRow_;
	int maxCol_;

	// エネミーのインスタンスを保持しておく(pieceにアクセスするため)
	Enemy* enemy_ = nullptr;
	// プレイヤーのインスタンスも保持して置く
	Player* player_ = nullptr;

};


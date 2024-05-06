#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stack>

#include "Block.h"
#include "LoadFile.h"
#include "BaseEntity.h"

#include "KingsAddress.h"

// 評価
#include "PieceValueEval.h"
#include "PiecePlaceEval.h"
#include "KingSafeEval.h"

class Enemy;
class Player;
class BaseEntity;

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
	static void SetCurrentArray(const std::vector<std::vector<int>>& board) { currentArray_ = board; }

	static std::vector<std::vector<int>> GetKeepArray() { return keepArray_; }
	static void SetKeepArray() { keepArray_ = currentArray_; }

	static Vec2 GetKingAttackAddress() { return kingAttackAddress_; }
	static void SetKingAttackAddress(const Vec2& address) { kingAttackAddress_ = address; }

	/// <summary>
	/// エネミーのインスタンスをセット
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

	/// <summary>
	/// プレイヤーのインスタンスをセット
	/// </summary>s
	/// <param name="player"></param>
	void SetPlayer(Player* player) { player_ = player; }

	bool GetIsGameSet() const { return isGameSet_; }

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

	void SetKingsAddress(const Vec2& player, const Vec2& cpu);

	bool GetingPlayerKing(const Vec2& cpuMoveAddress);

private:

	std::vector<std::unique_ptr<Block>> block_;

	static std::vector<std::vector<int>> currentArray_;
	static std::vector<std::vector<int>> keepArray_;

	// キングを攻撃できる配列を保存する(配列にしないのはCPU側しか評価しないのと2つあったらほぼ詰みだから)
	static Vec2 kingAttackAddress_;

	int maxRow_;
	int maxCol_;

	// エネミーのインスタンスを保持しておく(pieceにアクセスするため)
	Enemy* enemy_ = nullptr;
	// プレイヤーのインスタンスも保持して置く
	Player* player_ = nullptr;

	bool isGameSet_;

	// 評価するクラス
	std::unique_ptr<PieceValueEval> pieceValueEval_;
	std::unique_ptr<PiecePlaceEval> piecePlaceEval_;
	std::unique_ptr<KingSafeEval> kingSafeEval_;

	std::unique_ptr<KingsAddress> kingsAddress_;

	std::stack<int> movePieceStack_;
};


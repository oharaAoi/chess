#pragma once
#include "Block.h"
#include "BaseEntity.h"
#include "LoadFile.h"
#include <memory>
#include <vector>
#include <unordered_map>

class Board;

/// <summary>
/// 駒の位置によって評価するクラス
/// </summary>
class PiecePlaceEval {
public:

	PiecePlaceEval(const int& maxRow, const int& maxCol);
	~PiecePlaceEval();

	void Init();

	int Eval(std::vector<std::vector<int>> boardArray, const Vec2& address, const PieceType& type);
	int WhiteEval(std::vector<std::vector<int>> boardArray, const Vec2& address, const PieceType& type);

	/// <summary>
	/// 移動する盤面に相手の駒があったら補正がかかるようにする
	/// </summary>
	/// <param name="address">自色の駒のアドレス</param>
	/// <returns>補正値</returns>
	int CheckAddressOnWhitePiece(const Vec2& address);

	int CheckAddressOnBlackPiece(const Vec2& address);

private:

	std::vector<std::vector<int>> ePownSquareTable_;
	std::vector<std::vector<int>> eKnightSquareTable_;
	std::vector<std::vector<int>> eBishopSquareTable_;
	std::vector<std::vector<int>> eRookSquareTable_;
	std::vector<std::vector<int>> eQueenSquareTable_;
	std::vector<std::vector<int>> eKingSquareTable_;

	std::vector<std::vector<int>> pPownSquareTable_;
	std::vector<std::vector<int>> pKnightSquareTable_;
	std::vector<std::vector<int>> pBishopSquareTable_;
	std::vector<std::vector<int>> pRookSquareTable_;
	std::vector<std::vector<int>> pQueenSquareTable_;
	std::vector<std::vector<int>> pKingSquareTable_;

	std::vector<std::vector<int>> boardArray_;
	std::vector<std::vector<int>> keepArray_;

	int maxRow_;
	int maxCol_;

	int takePieceValue_[6] = { 0, 5, 15, 15, 25, 45 };

};


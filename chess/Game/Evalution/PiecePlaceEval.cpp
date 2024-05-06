#include "PiecePlaceEval.h"
#include "Board.h"

PiecePlaceEval::PiecePlaceEval(const int& maxRow, const int& maxCol) {
	maxRow_ = maxRow;
	maxCol_ = maxCol;
	Init();
}

PiecePlaceEval::~PiecePlaceEval() {
}

void PiecePlaceEval::Init() {
	ePownSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "pown");
	eKnightSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "knight");
	eBishopSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "bishop");
	eRookSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "rook");
	eQueenSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "queen");
	eKingSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "king");

	// 配列をコピー
	pPownSquareTable_ = ePownSquareTable_;
	pKnightSquareTable_ = eKnightSquareTable_;
	pBishopSquareTable_ = eBishopSquareTable_;
	pRookSquareTable_ = eRookSquareTable_;
	pQueenSquareTable_ = eQueenSquareTable_;
	pKingSquareTable_ = eKingSquareTable_;

	// 反転させる
	std::reverse(pPownSquareTable_.begin(), pPownSquareTable_.end());
	std::reverse(pKnightSquareTable_.begin(), pKnightSquareTable_.end());
	std::reverse(pBishopSquareTable_.begin(), pBishopSquareTable_.end());
	std::reverse(pRookSquareTable_.begin(), pRookSquareTable_.end());
	std::reverse(pQueenSquareTable_.begin(), pQueenSquareTable_.end());
	std::reverse(pKingSquareTable_.begin(), pKingSquareTable_.end());

}

int PiecePlaceEval::Eval(std::vector<std::vector<int>> boardArray, const Vec2& address, const PieceType& type) {
	int result;

	boardArray_ = boardArray;

	for (int row = 0; row < maxRow_; row++) {
		for (int col = 0; col < maxCol_; col++) {
			if (address.x == col && address.y == row) {
				switch (type) {
				case PawnType:
					result = ePownSquareTable_[row][col];
					return result;

				case KnightType:
					result = eKnightSquareTable_[row][col];
					return result;

				case BishopType:
					result = eBishopSquareTable_[row][col];
					return result;

				case RookType:
					result = eRookSquareTable_[row][col];
					return result;

				case QueenType:
					result = eQueenSquareTable_[row][col];
					return result;

				case KingType:
					result = eKingSquareTable_[row][col];
					return result;
				}
			}
		}
	}

	return 0;
}

int PiecePlaceEval::WhiteEval(std::vector<std::vector<int>> boardArray, const Vec2& address, const PieceType& type) {
	int result;

	boardArray_ = boardArray;

	for (int row = 0; row < maxRow_; row++) {
		for (int col = 0; col < maxCol_; col++) {
			if (address.x == col && address.y == row) {
				switch (type) {
				case PawnType:
					result = pPownSquareTable_[row][col];
					return result;

				case KnightType:
					result = pKnightSquareTable_[row][col];
					return result;

				case BishopType:
					result = pBishopSquareTable_[row][col];
					return result;

				case RookType:
					result = pRookSquareTable_[row][col];
					return result;

				case QueenType:
					result = pQueenSquareTable_[row][col];
					return result;

				case KingType:
					result = pKingSquareTable_[row][col];
					return result;
				}
			}
		}
	}

	return 0;
}

/// <summary>
/// 移動する盤面に相手の駒があったら補正がかかるようにする
/// </summary>
/// <param name="address">自色の駒のアドレス</param>
/// <returns>補正値</returns>
int PiecePlaceEval::CheckAddressOnWhitePiece(const Vec2& address) {
	if (keepArray_[address.y][address.x] / 10 == (kPlayer + 1)) {
		switch (keepArray_[address.y][address.x] % 10) {
		case PawnType:
			return takePieceValue_[PawnType];
		
		case KnightType:
			return takePieceValue_[KnightType];
			break;

		case BishopType:
			return takePieceValue_[BishopType];
			break;

		case RookType:
			return takePieceValue_[RookType];
			break;

		case QueenType:
			return takePieceValue_[QueenType];
			break;
		}
	}

	return 0;
}

int PiecePlaceEval::CheckAddressOnBlackPiece(const Vec2& address) {
	if (keepArray_[address.y][address.x] / 10 == (kCPU + 1)) {
		switch (keepArray_[address.y][address.x] % 10) {
		case PawnType:
			return takePieceValue_[PawnType];
			
		case KnightType:
			return takePieceValue_[KnightType];
			
		case BishopType:
			return takePieceValue_[BishopType];
			
		case RookType:
			return takePieceValue_[RookType];
			
		case QueenType:
			return takePieceValue_[QueenType];
			
		}
	}

	return 0;
}


#include "PiecePlaceEval.h"

PiecePlaceEval::PiecePlaceEval(const int& maxRow, const int& maxCol) {
	maxRow_ = maxRow;
	maxCol_ = maxCol;
	Init();
}

PiecePlaceEval::~PiecePlaceEval() {
}

void PiecePlaceEval::Init() {
	pownSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "pown");
	knightSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "knight");
	bishopSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "bishop");
	rookSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "rook");
	queenSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "queen");
	kingSquareTable_ = LoadFile::LoadPieceEval("./Resources/json/EvalPiece.json", "king");

}

int PiecePlaceEval::Eval(const Vec2& address, const PieceType& type) {
	int eval = 0;

	for (int row = 0; row < maxRow_; row++) {
		for (int col = 0; col < maxCol_; col++) {
			if (address.x == col && address.y == row) {

				switch (type) {
				case PawnType:
					eval = pownSquareTable_[row][col];
					break;

				case KnightType:
					eval = knightSquareTable_[row][col];
					break;

				case BishopType:
					eval = bishopSquareTable_[row][col];
					break;

				case RookType:
					eval = rookSquareTable_[row][col];
					break;

				case QueenType:
					eval = queenSquareTable_[row][col];
					break;

				case KingType:
					eval = kingSquareTable_[row][col];
					break;
				}
			}
		}
	}

	return eval;
}


#include "PieceValueEval.h"
#include "Board.h"

PieceValueEval::PieceValueEval(const int& maxRow, const int& maxCol) {
	maxRow_ = maxRow;
	maxCol_ = maxCol;

	Init();
}

PieceValueEval::~PieceValueEval() {
}

void PieceValueEval::Init() {
	
}

int PieceValueEval::Eval() {
	// 結果の評価値
	int eval = 0;

	std::vector<std::vector<int>> boardArray = Board::GetCurrentArray();

	// 自分の駒の数　- 相手の駒の数　= 点を基礎スコアとする
	for (int row = 0; row < maxRow_; row++) {
		for (int col = 0; col < maxCol_; col++) {
			switch (boardArray[row][col] % 10) {
			case PawnType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["PawnType"];
				} else {
					eval += pieceValues_["PawnType"];
				}
				break;

			case KnightType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["KnightType"];
				} else {
					eval += pieceValues_["KnightType"];
				}

				break;

			case BishopType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["BishopType"];
				} else {
					eval += pieceValues_["BishopType"];
				}

				break;

			case RookType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["RookType"];
				} else {
					eval += pieceValues_["RookType"];
				}

				break;

			case QueenType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["QueenType"];
				} else {
					eval += pieceValues_["QueenType"];
				}

				break;

			case KingType:
				if (boardArray[row][col] / 10 == 1) {
					eval -= pieceValues_["KingType"];
				} else {
					eval += pieceValues_["KingType"];
				}

				break;
			}
		}
	}

	return  eval;
}

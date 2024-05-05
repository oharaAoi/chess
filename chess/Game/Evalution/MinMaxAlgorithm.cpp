#include "MinMaxAlgorithm.h"

MinMaxAlgorithm::MinMaxAlgorithm() {
	roopCount_ = 0;
}

MinMaxAlgorithm::~MinMaxAlgorithm() {
}


/// <summary>
/// 自分にとって一番良い手を敵は一番低い手(自分にとって一番いやな手を選ぶ)
/// </summary>
/// <param name="depth"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="maximizingPlayer"></param>
/// <returns></returns>
int MinMaxAlgorithm::AlphaBeta(int depth, int alpha, int beta, bool maximizingPlayer) {
	roopCount_++;
	// 深さが0に達したら関数を終了する
	if (depth == 0) {
		return board_->Evaluation(); // ここに評価関数が入る予定;
	}

	// アルファ値が確定している最善の手の評価値
	// 一旦CPUが使う前提で作る

	// 最大値を探索するか最小値を探索するか
	// 最大値の場合は子のノードに対して比較を行い数値が大きいものを返す
	if (maximizingPlayer) {
		// 最大の評価値
		// 現在の盤面から打てる手をすべて配列に格納する
		std::vector<Moved> allCanMoved = board_->CreateCanMove(Board::GetCurrentArray(), kCPU);
		// 打てる手が決まったらそれをすべてループ分に回す
		// 範囲for文を使うhttps://cpprefjp.github.io/lang/cpp11/range_based_for.html
		for (const Moved& moved : allCanMoved) {
			// 打てる手をボードに適応させる
			board_->CreateMovedArray(moved);
			// 適応させた手で相手の手の評価をする
			int eval = AlphaBeta(depth - 1, alpha, beta, false);
			// 動きを適応させたボードを元に戻す
			board_->CreateUndoMovedArray(moved);
			// 評価値とmax値を比較する
			// アルファ値と評価値を比較する
			alpha = max(alpha, eval);
			// アルファ値とベータ値を比較する
			// β値を上回ったため先読みせず評価しない
			if (beta <= alpha) {
				return alpha;
			}
		}

		return alpha;

	} else {
		// 現在の盤面から打てる手をすべて配列に格納する
		std::vector<Moved> allCanMoved = board_->CreateCanMove(Board::GetCurrentArray(), kPlayer);
		for (const Moved& moved : allCanMoved) {
			// 打てる手をボードに適応させる
			board_->CreateMovedArray(moved);
			// 適応させた手で相手の手の評価をする
			int eval = AlphaBeta(depth - 1, alpha, beta, true);
			// 動きを適応させたボードを元に戻す
			board_->CreateUndoMovedArray(moved);
			beta = min(beta, eval);
			// α値を下回ったため先読みせず評価を返す
			if (beta <= alpha) {
				return beta;
			}
		}

		return beta;
	}
}

Moved MinMaxAlgorithm::FindBestMove(int depth) {
	Moved result{};
	// 最大の評価
	int bestEval = INT_MIN;

	roopCount_ = 0;
	
	alpha_ = INT_MIN;
	beta_ = INT_MAX;

	// 動ける手を探す
	std::vector<Moved> allCanMoved = board_->CreateCanMove(Board::GetCurrentArray(), kCPU);

	// 今の盤面を保存しておく
	//Board::SetKeepArray();

	for (const Moved& moved : allCanMoved) {
		// 相手のキングを取れるか
		if (board_->GetingPlayerKing(moved.toMove)) {
			return moved;
		}

		// 打てる手をボードに適応させる
		board_->CreateMovedArray(moved);

		int eval = AlphaBeta(depth - 1, alpha_, beta_, false);
		board_->CreateUndoMovedArray(moved);

		alpha_ = eval;

		if (bestEval < eval) {
			bestEval = eval;
			result = moved;
		}
	}

	eval_ = bestEval;

	return result;
}

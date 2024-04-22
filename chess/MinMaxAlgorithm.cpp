#include "MinMaxAlgorithm.h"

MinMaxAlgorithm::MinMaxAlgorithm() {
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
int MinMaxAlgorithm::minmax(int depth, int alpha, int beta, bool maximizingPlayer) {
	// 深さが0に達したら関数を終了する
	if (depth == 0) {
		return 0;
	}

	// 最大値を探索するか最小値を探索するか
	// 最大値の場合は子のノードに対して比較を行い数値が大きいものを返す
	if (maximizingPlayer) {
		// 最大の評価値
		int maxEval = -999999;
	} else {
		// 最小の評価理 
		int minEval = 10000000;
	}
}

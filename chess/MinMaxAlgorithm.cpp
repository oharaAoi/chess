#include "MinMaxAlgorithm.h"

MinMaxAlgorithm::MinMaxAlgorithm() {
}

MinMaxAlgorithm::~MinMaxAlgorithm() {
}

/// <summary>
/// �����ɂƂ��Ĉ�ԗǂ����G�͈�ԒႢ��(�����ɂƂ��Ĉ�Ԃ���Ȏ��I��)
/// </summary>
/// <param name="depth"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="maximizingPlayer"></param>
/// <returns></returns>
int MinMaxAlgorithm::minmax(int depth, int alpha, int beta, bool maximizingPlayer) {
	// �[����0�ɒB������֐����I������
	if (depth == 0) {
		return 0;
	}

	// �ő�l��T�����邩�ŏ��l��T�����邩
	// �ő�l�̏ꍇ�͎q�̃m�[�h�ɑ΂��Ĕ�r���s�����l���傫�����̂�Ԃ�
	if (maximizingPlayer) {
		// �ő�̕]���l
		int maxEval = -999999;
	} else {
		// �ŏ��̕]���� 
		int minEval = 10000000;
	}
}

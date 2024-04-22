#pragma once
#include "MyVector2.h"
#include "BaseEntity.h"
#include "MyMath.h"
#include "Board.h"

struct Moved {
	Vec2 moveToIndex;// �ǂ��̃A�h���X�Ɉړ����邩
	int evaluation; // �]���l
	PieceType type;	// �ǂ̎�ނ̋���ړ����邩
};

/// <summary>
/// minmax�A���S���Y�����s���N���X
/// </summary>
class MinMaxAlgorithm {

public:

	MinMaxAlgorithm();
	~MinMaxAlgorithm();

	/// <summary>
	/// �]���֐�
	/// </summary>
	/// <param name="depth"></param>
	/// <param name="maximizingPlayer"></param>
	int minmax(int depth, int alpha, int beta, bool maximizingPlayer);

private:



};


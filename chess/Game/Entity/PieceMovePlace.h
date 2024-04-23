#pragma once
#include "MyNovice.h"
#include "BaseEntity.h"
#include "LoadFile.h"
#include "DrawUtils.h"

class PieceMovePlace 
: public BaseEntity {
public:

	PieceMovePlace(const Vec2& address);
	virtual ~PieceMovePlace();

	void Init(const Vec2& address);
	void Update()override;
	void Draw()override;

public:

	bool GetIsMove() const { return isMove_; }

	bool GetIsCursorOn() const { return isCursorOn_; }

	void IsClick();

	/// <summary>
	/// 移動できる方向を配列に代入して返す
	/// </summary>
	/// <returns></returns>
	std::vector<Moved> GetCanMove(const std::vector<std::vector<int>>& board) override;

private:

	int GH_;

	bool isMove_;
};


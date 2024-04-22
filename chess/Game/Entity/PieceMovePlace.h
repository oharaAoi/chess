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

private:

	int GH_;

	bool isMove_;
};


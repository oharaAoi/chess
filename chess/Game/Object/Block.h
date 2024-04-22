#pragma once
#include "Base_Object.h"

enum kBlockType {
	kNorn,
	kWhite,
	kBlock
};

class Block
: public Base_Object{
public:

	Block();
	~Block();

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetPos(const Vec2f& pos) { pos_ = pos; }
	void SetDrawLt(const Vec2f& drawLt) { leftTop_ = drawLt; }

	void SetType(const kBlockType& type) { type_ = type; }
	kBlockType GetType() const { return type_; }

private:

	kBlockType type_;
	int GH_;
};


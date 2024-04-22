#pragma once
#include "Matrix.h"
#include "MyMath.h"
#include "DrawUtils.h"

class Base_Object{
public:

	Base_Object() = default;
	~Base_Object() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	Vec2f pos_;
	Vec2f size_;
	Vec2f scale_;
	Vec2f leftTop_;

	float theta_;

	// 各頂点
	RectVerf localVertex_;
	RectVerf worldVertex_;
	RectVerf screenVertex_;

	// 行列
	Matrix3x3 worldMatrix_;
	Matrix3x3 screenMatrix_;

	unsigned int color_;
};


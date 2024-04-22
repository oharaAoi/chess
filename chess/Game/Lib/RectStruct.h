#pragma once
#include "MyVector2.h"
#include "Matrix.h"
#include "RectVertex.h"

struct RectParam {
	Vec2f pos;
	Vec2f size;
	Vec2f scale;

	float theta;

	Vec2f leftTop;

	RectVerf localVertex;
	RectVerf worldVertex;
	RectVerf screenVertex;

	Matrix3x3 worldMatrix;
	Matrix3x3 screenMatrix;

	unsigned int color;

	int GH;
};
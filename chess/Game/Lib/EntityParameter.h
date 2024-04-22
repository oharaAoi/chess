#pragma once
#include "MyVector2.h"

/// <summary>
/// 速度を持った物のパラメータ
/// </summary>
struct EntityParam {
	Vec2f pos;
	Vec2f size;
	Vec2f scale;
	Vec2f leftTop;
	Vec2f velocity;
	Vec2f acceleration;
	float theta;
};
#pragma once
#include "MyVector2.h"

struct ParticleParam {
	Vec2f worldPos;
	float theta;
	Vec2f scale;
	Vec2f size;
	Vec2f leftTop;

	Vec2f velocity;
	Vec2f acceration;

	bool isAlive;
	int lifeCount;

	unsigned int color;
};


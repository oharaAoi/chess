#pragma once
#include <Novice.h>
#include "MyVector2.h"
#include "RectVertex.h"

void DrawSprite(const Vec2f& leftTop, const Vec2f& scale, const int& GH, const unsigned int& color);

void DrawSpriteRect(const Vec2f& leftTop, const Vec2f& drawLeftTop, const Vec2f& drawSize, const int& GH, const Vec2f& scale, const unsigned int& color);

void DrawQuad(Vec2f pos, Vec2f size, Vec2f lt,int gh, unsigned int color);

void DrawQuad(RectVerf vertex, Vec2f size, Vec2f lt, int gh, unsigned int color);

void DrawEllipse(Vec2f centerPos, float radius, unsigned int color, FillMode mode);

void PlayAudio(int& voiceHandle, int soundHandle, float soundVolume, bool isLoop);
#include "Draw.h"

void DrawSprite(const Vec2f& leftTop, const Vec2f& scale, const int& GH, const unsigned int& color){
	Novice::DrawSprite(
		static_cast<int>(leftTop.x),
		static_cast<int>(leftTop.y),
		GH, 
		scale.x,
		scale.y,
		0.0f,
		color
	);
}

void DrawSpriteRect(const Vec2f& leftTop, const Vec2f& drawLeftTop, const Vec2f& drawSize, const int& GH, const Vec2f& scale, const unsigned int& color){
	Novice::DrawSpriteRect(
		static_cast<int>(leftTop.x),
		static_cast<int>(leftTop.y),
		static_cast<int>(drawLeftTop.x),
		static_cast<int>(drawLeftTop.y),
		static_cast<int>(drawSize.x),
		static_cast<int>(drawSize.y),
		GH,
		scale.x,
		scale.y,
		0.0f,
		color
	);
}

void DrawQuad(Vec2f pos, float width, float height, Vec2f lt,
	int gh, unsigned int color) {
	Novice::DrawQuad(
		static_cast<int>((pos.x - (width / 2))),
		static_cast<int>((pos.y - (height / 2))),
		static_cast<int>((pos.x + (width / 2))),
		static_cast<int>((pos.y - (height / 2))),
		static_cast<int>((pos.x - (width / 2))),
		static_cast<int>((pos.y + (height / 2))),
		static_cast<int>((pos.x + (width / 2))),
		static_cast<int>((pos.y + (height / 2))),
		static_cast<int>(lt.x),
		static_cast<int>(lt.y),
		static_cast<int>(width),
		static_cast<int>(height),
		gh,
		color
	);
}

void DrawQuad(Vec2f pos, Vec2f size, Vec2f lt, int gh, unsigned int color){
	Novice::DrawQuad(
		static_cast<int>((pos.x - (size.x/ 2))),
		static_cast<int>((pos.y - (size.y / 2))),
		static_cast<int>((pos.x + (size.x/ 2))),
		static_cast<int>((pos.y - (size.y / 2))),
		static_cast<int>((pos.x - (size.x/ 2))),
		static_cast<int>((pos.y + (size.y / 2))),
		static_cast<int>((pos.x + (size.x/ 2))),
		static_cast<int>((pos.y + (size.y / 2))),
		static_cast<int>(lt.x),
		static_cast<int>(lt.y),
		static_cast<int>(size.x),
		static_cast<int>(size.y),
		gh,
		color
	);

}

void DrawQuad(RectVerf vertex, Vec2f size, Vec2f lt, int gh, unsigned int color){
	Novice::DrawQuad(
		static_cast<int>(vertex.lt.x),
		static_cast<int>(vertex.lt.y),
		static_cast<int>(vertex.rt.x),
		static_cast<int>(vertex.rt.y),
		static_cast<int>(vertex.lb.x),
		static_cast<int>(vertex.lb.y),
		static_cast<int>(vertex.rb.x),
		static_cast<int>(vertex.rb.y),
		static_cast<int>(lt.x),
		static_cast<int>(lt.y),
		static_cast<int>(size.x),
		static_cast<int>(size.y),
		gh,
		color
	);
}

void DrawEllipse(Vec2f centerPos, float radius, unsigned int color, FillMode mode){
	Novice::DrawEllipse(
		static_cast<int>(centerPos.x),
		static_cast<int>(centerPos.y),
		static_cast<int>(radius),
		static_cast<int>(radius),
		0.0f,
		color,
		mode
	);
}


void PlayAudio(int& voiceHandle, int soundHandle, float soundVolume, bool isLoop) {
	if (Novice::IsPlayingAudio(voiceHandle) == 0 || voiceHandle == -1) {
		voiceHandle = Novice::PlayAudio(soundHandle, isLoop, soundVolume);
	}
}

#include "Block.h"

Block::Block(){
	Init();
}

Block::~Block(){
}

void Block::Init(){
	pos_ = { 0.0f, 0.0f };
	size_ = { 64.0f, 64.0f };
	scale_ = { 1.0f, 1.0f };
	leftTop_ = { 0.0f, 0.0f };

	theta_ = 0;

	ScreenRectVertex(localVertex_, size_);
	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);

	color_ = 0xffffffff;

	GH_ = Novice::LoadTexture("./Resources/blockTile.png");
}

void Block::Update(){
	worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
}

void Block::Draw(){
	DrawUtils::DrawQuad(worldMatrix_, localVertex_, leftTop_, size_, GH_, color_);
}

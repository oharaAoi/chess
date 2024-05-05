#include "KingsAddress.h"

KingsAddress::KingsAddress() {
}

KingsAddress::~KingsAddress() {
}

void KingsAddress::Init() {
}

void KingsAddress::Update(const Vec2& playerKing, const Vec2& cpuKing) {
	playerKing_ = playerKing;
	cpuKing_ = cpuKing;
}

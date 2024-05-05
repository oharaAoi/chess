#pragma once
#include "MyVector2.h"

class KingsAddress {
public:

	KingsAddress();
	~KingsAddress();

	void Init();

	void Update(const Vec2& playerKing, const Vec2& cpuKing);

	Vec2 GetPlayerKingAddress() const { return playerKing_; }

private:

	Vec2 playerKing_;
	Vec2 cpuKing_;

};


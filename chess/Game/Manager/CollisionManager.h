#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Board.h"

class CollisionManager {
public:

	CollisionManager(Player* player, Enemy* enemy);
	~CollisionManager();

	void Init(Player* player, Enemy* enemy);
	
	void OnCollision(const bool& isPlaying);

private:

	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;

};


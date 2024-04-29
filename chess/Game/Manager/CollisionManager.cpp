#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, Enemy* enemy) {
	Init(player, enemy);
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::Init(Player* player, Enemy* enemy) {
	player_ = player;
	enemy_ = enemy;
}

void CollisionManager::OnCollision(const bool& isPlaying) {
	// フラグがtrueだったら自分が指した後の当たり判定をとる(重なっていた時に白がとる)
	for (int oi = 0; oi < player_->GetPices().size(); oi++) {
		// プレイヤーのアドレスを得る
		Vec2 playerAddress = player_->GetPices()[oi]->GetAddress();
		for (int ai = 0; ai < enemy_->GetPices().size(); ai++) {
			// エネミーのアドレスを得る
			Vec2 enemyAddress = enemy_->GetPices()[ai]->GetAddress();
			// アドレスが重なってたら指された方を消す
			if (playerAddress.x == enemyAddress.x && playerAddress.y == enemyAddress.y) {
				if (enemy_->GetPices()[ai]->GetIsAlive() && player_->GetPices()[oi]->GetIsAlive()) {
					if (isPlaying) {
						enemy_->GetPices()[ai]->SetIsAlive(false);
					} else {
						player_->GetPices()[oi]->SetIsAlive(false);
					}
				}
			}
		}
	}
}



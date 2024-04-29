#pragma once
#include <memory>
#include "MyNovice.h"

#include "Base_Scene.h"
#include "ImGuiManager.h"

// entity
#include "Player.h"
#include "Enemy.h"
// object
#include "Board.h"
// system
#include "Camera.h"
#include "DrawUtils.h"

#include "MinMaxAlgorithm.h"
#include "CollisionManager.h"

class Scene_Game
:public Base_Scene{

public:

	Scene_Game();
	~Scene_Game();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	// entity
	std::unique_ptr<Player> player_;

	std::unique_ptr<Enemy> enemy_;

	// object
	std::unique_ptr<Board> board_;

	// system
	std::unique_ptr<DrawUtils> drawUtils_;

	std::unique_ptr<MinMaxAlgorithm> minmax_;

	std::unique_ptr<CollisionManager> collisionManager_;

	bool isGameSet_;

	// どう移動したか
	Moved moved_;
};



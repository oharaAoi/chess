#pragma once
#include<stack>
#include<memory>
#include "Base_Scene.h"
#include "Scene_Game.h"

class SceneManager{
public: // メンバ関数

	// constructor:destructor
	SceneManager();
	~SceneManager();

	void Init();
	void Update();

private:

	std::stack<std::unique_ptr<Base_Scene>> sceneStack_;
	std::unique_ptr<Base_Scene> scene_[3];

	std::unique_ptr<Base_Scene> game;
};


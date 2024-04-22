#include "SceneManager.h"

SceneManager::SceneManager(){
	Init();
}

SceneManager::~SceneManager(){
}

void SceneManager::Init(){
	game = std::make_unique<Scene_Game>();
	sceneStack_.push(std::move(game));
}

void SceneManager::Update(){
	sceneStack_.top()->Update();
	sceneStack_.top()->Draw();
}

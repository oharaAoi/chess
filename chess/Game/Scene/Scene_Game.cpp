#include "Scene_Game.h"

Scene_Game::Scene_Game(){
	Init();
}

Scene_Game::~Scene_Game(){
}

//=================================================================================================================
//	↓　
//=================================================================================================================
void Scene_Game::Init(){
	player_ = std::make_unique<Player>();

	enemy_ = std::make_unique<Enemy>();

	board_ = std::make_unique<Board>();

	drawUtils_ = std::make_unique<DrawUtils>();
}

//=================================================================================================================
//	↓　
//=================================================================================================================
void Scene_Game::Update(){
	// 盤面の初期化(現在の駒の状況を一旦リセットし次の処理で更新するため)
	board_->Updata();
	// 盤面の状態を更新する
	player_->BoardSetting();
	enemy_->BoardSetting();

	player_->Update();
	enemy_->Update();

	drawUtils_->Update(MyNovice::GetCamera()->GetVpMatrix());
}

//=================================================================================================================
//	↓　
//=================================================================================================================
void Scene_Game::Draw(){

	board_->Draw();

	player_->Draw();
	enemy_->Draw();

	ImGui::Begin("Scene");
	ImGui::Text("Scene_Game");
	ImGui::End();
}

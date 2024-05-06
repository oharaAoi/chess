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

	// 
	board_->SetEnemy(enemy_.get());
	board_->SetPlayer(player_.get());

	minmax_ = std::make_unique<MinMaxAlgorithm>();
	minmax_->SetBoard(board_.get());

	collisionManager_ = std::make_unique<CollisionManager>(player_.get(), enemy_.get());

	isGameSet_ = false;

	moved_ = { {0,0}, {0,0} };
}

//=================================================================================================================
//	↓　
//=================================================================================================================
void Scene_Game::Update(){
	if (player_->GetIsLose() || enemy_->GetIsLose()) {
		isGameSet_ = true;
	}

	if (isGameSet_) {
		return;
	}

	player_->Update();
	enemy_->Update();

	// 盤面の初期化(現在の駒の状況を一旦リセットし次の処理で更新するため)
	board_->Updata();

	// 盤面の状態を更新する
	player_->BoardSetting();
	enemy_->BoardSetting();

	board_->SetKingsAddress(player_->GetKingAddress(), enemy_->GetKingAddress());

	// playerが指したら入る
	if (player_->GetIsPoint()) {
		// まずplayerの駒と敵の駒の当たり判定を取る(当たっていたら敵の駒が取られる)
		collisionManager_->OnCollision(player_->GetIsPoint());

		// playerの指すターンが終わる
		player_->SetIsPoint(false);

		// 敵の駒の生きている判定を取る
		enemy_->CheckIsAlive();

		// 盤面の状態を更新する
		player_->BoardSetting();
		enemy_->BoardSetting();

		// 敵が駒を指す
		moved_ = minmax_->FindBestMove(3);
		enemy_->AiPoint(moved_);

		// 当たり判定をとる(当たっていたらplayerの駒が取れる)
		collisionManager_->OnCollision(player_->GetIsPoint());
	}

	// 盤面の初期化(現在の駒の状況を一旦リセットし次の処理で更新するため)
	board_->Updata();

	// 盤面の状態を更新する
	player_->BoardSetting();
	enemy_->BoardSetting();

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
	if(ImGui::Button("Reset")) {
		Init();
	}
	ImGui::End();

	ImGui::Begin("Result");
	if (player_->GetIsLose()) {
		ImGui::Text("CPU : WIN");
	} else if (enemy_->GetIsLose()) {
		ImGui::Text("PLAYER : WIN");
	} else {
		ImGui::Text("Game");
	}

	ImGui::Spacing();
	ImGui::Spacing();

	// move
	ImGui::Text("Move");
	ImGui::Text("from: col: %d, row: %d", moved_.fromMove.x, moved_.fromMove.y);
	ImGui::Text("to: col: %d, row: %d", moved_.toMove.x, moved_.toMove.y);

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Count");
	ImGui::Text("roopCount: %d", minmax_->GetRoopCount());

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Evalution");
	ImGui::Text("eval: %d", minmax_->GetEval());

	ImGui::End();
}

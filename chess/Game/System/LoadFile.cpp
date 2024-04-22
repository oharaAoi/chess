#include "LoadFile.h"

std::vector<std::vector<int>> LoadFile::mapArr_{};
std::vector<std::vector<int>> LoadFile::piceArr_{};

EntityState LoadFile::entityData_{};

LoadFile* LoadFile::GetInstance(){
	static LoadFile instance;
	return &instance;
}

void LoadFile::LoadMapData(std::string fileName){
	json mapDate;

	std::ifstream inputFile(fileName);

	if (inputFile.is_open()) {
		inputFile >> mapDate;

		// loadjsonクラスのmapArrの中にデータを入れる
		// それをゲッターを通じて取得
		mapArr_ = mapDate["map"]["tiles"];

		// ワールド座標系にしているため行を反転させる(もしかしたらいらないかも)
		std::reverse(mapArr_.begin(), mapArr_.end());

		// ファイルを閉じる
		inputFile.close();
	}
}

void LoadFile::LoadPiceSetData(std::string fileName) {
	json mapDate;

	std::ifstream inputFile(fileName);

	if (inputFile.is_open()) {
		inputFile >> mapDate;

		// loadjsonクラスのmapArrの中にデータを入れる
		// それをゲッターを通じて取得
		piceArr_ = mapDate["map"]["tiles"];

		// ワールド座標系にしているため行を反転させる(もしかしたらいらないかも)
		std::reverse(piceArr_.begin(), piceArr_.end());

		// ファイルを閉じる
		inputFile.close();
	}
}

void LoadFile::LoadEntityData(const std::string& filePath) {
	json entityData;

	std::ifstream inputFile(filePath);

	if (inputFile.is_open()) {
		inputFile >> entityData;

		// 座標
		if (entityData.contains("pos")) {
			entityData_.pos = { entityData["pos"]["x"], entityData["pos"]["y"] };
		}

		// サイズ
		if (entityData.contains("size")) {
			entityData_.size = { entityData["size"]["x"], entityData["size"]["y"] };
		}

		// スケール
		if (entityData.contains("scale")) {
			entityData_.scale = { entityData["scale"]["x"], entityData["scale"]["y"] };
		}

		// 左上頂点
		if (entityData.contains("leftTop")) {
			entityData_.leftTop = { entityData["leftTop"]["x"], entityData["leftTop"]["y"] };
		}

		// thete
		if (entityData.contains("theta")) {
			entityData_.theta = entityData["theta"];
		}
	}

	// ファイルを閉じる
	inputFile.close();
}

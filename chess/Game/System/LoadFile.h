#pragma once
#include <json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <vector>
#include "MyVector2.h"

using json = nlohmann::json;

/// <summary>
/// ファイルから情報を得るための構造体
/// </summary>
struct EntityState {
	Vec2f pos;
	Vec2f size;
	Vec2f scale;
	Vec2f leftTop;
	float theta;
};

class LoadFile{
private:

	LoadFile() {};
	~LoadFile() {};

	// stage
	static std::vector<std::vector<int>> mapArr_;

	static std::vector<std::vector<int>> piceArr_;

	static EntityState entityData_;

public:

	// コピーコンストラクタの禁止
	LoadFile(const LoadFile& obj) = delete;
	LoadFile operator + (const LoadFile& obj) = delete;

	static LoadFile* GetInstance();

	static void LoadMapData(std::string fileName);

	static void LoadPiceSetData(std::string fileName);

	static void LoadEntityData(const std::string& filePath);

	static std::vector<std::vector<int>> LoadPieceEval(const std::string& filePath, const std::string& pieceType);

public:

	static std::vector<std::vector<int>> GetMapArr() { return mapArr_; }

	static std::vector<std::vector<int>> GetPiceSetArr() { return piceArr_; }

	static EntityState GetEntityState() { return entityData_; }

};


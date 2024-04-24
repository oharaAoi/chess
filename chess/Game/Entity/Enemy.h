﻿#pragma once
#include <memory>
#include <vector>
#include "LoadFile.h"
#include "BaseEntity.h"
#include "Board.h"

class Pawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;

class Enemy {
public:

	Enemy();
	~Enemy();

public:

	void Init();
	void Update();
	void Draw();

public: // accsesser

	const std::vector<std::unique_ptr<BaseEntity>>& GetPices() const { return pices_; }

public:

	/// <summary>
	/// 駒の状況を更新する
	/// </summary>
	void BoardSetting();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	void AiPoint(const Moved& move);

private:

	std::vector<std::unique_ptr<BaseEntity>> pices_;

	// 駒を指したか
	bool isPoint_;

};


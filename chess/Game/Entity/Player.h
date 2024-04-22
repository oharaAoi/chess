#pragma once
#include <memory>
#include <vector>
#include "LoadFile.h"
#include "BaseEntity.h"
#include "Board.h"
// Pice
//#include "Pawn.h"
//#include "Knight.h"
//#include "Bishop.h"
//#include "Rook.h"
//#include "Queen.h"
//#include "King.h"

class Pawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;

class Player {
public:

	Player();
	~Player();

public:

	void Init();

	void Update();

	void Draw();

public:

	/// <summary>
	/// 駒の状況を更新する
	/// </summary>
	void BoardSetting();

private:

	/*std::vector<std::unique_ptr<Pawn>> pawn_;
	std::vector<std::unique_ptr<Knight>> knight_;
	std::vector<std::unique_ptr<Bishop>> bishop_;
	std::vector<std::unique_ptr<Rook>> rook_;
	std::unique_ptr<Queen> queen_;
	std::unique_ptr<King> king_;*/


	std::vector<std::unique_ptr<BaseEntity>> pices_;

};



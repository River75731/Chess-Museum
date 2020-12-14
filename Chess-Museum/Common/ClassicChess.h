#pragma once
#include "Common.h"

enum ClassicChessType {
	Empty,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

class ClassicChessPosition : public Position2d, public ChessPosition{
public:
	bool isValid(); // whether it's on board
};

class ClassicChessMove : public ChessMove{
public:

};

class ClassicChess : public Chess{
protected:

public:
};
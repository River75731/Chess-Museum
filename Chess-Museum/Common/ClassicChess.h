#pragma once
#include <vector>
#include "Position.h"
#include "Chess.h"


/*
	Classic Chess
	Board : x from 1 to 8 and y from 1 to 8
	Type : Rook, Knight, Bishop, Queen, King, Pawn
	Player : White(0) and Black(1)
	Status : 0(Not End, White turn), 1(Not End, Black turn), 2(End, White Win), 3(End, Black Win)
	Object : Dead(0) and Alive(1)
	ObjectIdx : index in object array
	Object Array : [32], each has a ClssicChessObject
	History :
	8	R	K	B	Q	KK	B	K	R
	7	P	P	P	P	P	P	P	P
	6
	5
	4
	3
	2	P	P	P	P	P	P	P	P
	1	R	K	B	Q	KK	B	K	R	
   y/x	1	2	3	4	5	6	7	8
*/

enum ClassicChessObjectType {
	CLASSICCHESS_EMPTY,
	CLASSICCHESS_PAWN,
	CLASSICCHESS_ROOK,
	CLASSICCHESS_KNIGHT,
	CLASSICCHESS_BISHOP,
	CLASSICCHESS_QUEEN,
	CLASSICCHESS_KING
};

enum ClassicChessPlayerType {
	CLASSICCHESS_WHITE,
	CLASSICCHESS_BLACK
};

enum ClassicChessStatus {
	CLASSICCHESS_WHITE_TURN,
	CLASSICCHESS_BLACK_TURN,
	CLASSICCHESS_WHITE_WIN,
	CLASSICCHESS_BLACK_WIN
};

enum ClassicChessObjectStatus {
	CLASSICCHESS_DEAD,
	CLASSICCHESS_ALIVE
};

class ClassicChessPosition : public Position2i, public ChessPosition{
public:
	bool isValid() const; // whether it's on board
};

class ClassicChessObject {
protected:
	const int index;
	ClassicChessObjectStatus status;
	ClassicChessObjectType type;
	const ClassicChessPlayerType player;
	const ClassicChessPosition position;
};

class ClassicChessMove : public ChessMove{
protected:
	ClassicChessObject object;
	ClassicChessPosition dest;
public:
	bool isValid() const;	
};

class ClassicChess : public Chess{
private:
	ClassicChessObject objects[32];
	std::vector<ClassicChessMove> history;
public:
	ClassicChess();
};
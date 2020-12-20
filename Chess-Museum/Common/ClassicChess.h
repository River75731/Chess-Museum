#pragma once
#include <vector>
#include <array>
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
	7	P	P	P	P	P	P	P	P   BLACK
	6
	5
	4
	3
	2	P	P	P	P	P	P	P	P
	1	R	K	B	Q	KK	B	K	R	WHITE
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
	CLASSICCHESS_INTERRUPT_UPGRADEPAWN,
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
	ClassicChessPosition();
	ClassicChessPosition(const int& x, const int& y);
	ClassicChessPosition(const ClassicChessPosition& that);
	bool isValid() const; // whether it's on board
	void output(const std::string &name = "DEFAULT") const;
};

// const type ClassicChessObject : object cannot be modified
class ClassicChessObject {	
private:
	const int index;
	const ClassicChessObjectStatus status;
	const ClassicChessObjectType type;
	const ClassicChessPlayerType player;
	const ClassicChessPosition position;
public:
	// Constructor & Destructor
	ClassicChessObject(const int& index, const ClassicChessPlayerType& player, const ClassicChessPosition& position, const ClassicChessObjectType& type, const ClassicChessObjectStatus& status = CLASSICCHESS_ALIVE);
	ClassicChessObject(const ClassicChessObject& that);
	~ClassicChessObject();
	// Get Method
	const int getIndex() const;
	const ClassicChessObjectStatus getStatus() const;
	const ClassicChessObjectType getType() const;
	const ClassicChessPlayerType getPlayer() const;
	const ClassicChessPosition getPosition() const;
};

// const type ClassicChessMove : move cannot be modified
class ClassicChessMove : public ChessMove{
private:
	const ClassicChessObject object;
	const ClassicChessPosition dest;
public:
	// Constructor & Destructor
	ClassicChessMove(const ClassicChessObject& object, const ClassicChessPosition& dest);
	ClassicChessMove(const ClassicChessObject& object, const int& x, const int& y);
	ClassicChessMove(const ClassicChessMove& that);
	~ClassicChessMove();
	// Get Method
	const ClassicChessObject getObject() const;
	const ClassicChessPosition getDest() const;
	/*
		Valid Move :
		1 > Both Position of Object and Destination should be valid and shouldn't be the same
		2 > Object should be ALIVE
		3 > PAWN is allowed to move forward 1 step or 2 steps(beginning), and horizontally 1 step (kill other) or 0 step
		4 > ROOK goes straight forward horizontally or vertically
		5 > KNIGHT goes straight forward for 2 steps and horizontally one step
		6 > BISHOP goes horizontally n steps and vertically n steps
		7 > QUEEN goes for BISHOP unions ROOK
		8 > KING goes one step for any direction
	*/
	bool isValid() const;	
};

class ClassicChess : public Chess{
private:
	ClassicChessStatus status;
	std::array<int, 32> objects;		// store the object locations in array board, -1 if dead
	std::array<std::unique_ptr<ClassicChessObject>, 64> board;	// store the board
	std::vector<std::unique_ptr<ClassicChessMove>> history; // chess history

	// functions
	ClassicChessPosition toPosition(const int& index) const; // index to position
	int toIndex(const ClassicChessPosition& position) const; // position to index

	void loadMsg(std::string address);
	void saveMsg(std::string address);

	void execMove(std::unique_ptr<ChessMove> move) = 0;	// execute a move
	bool isValidMove(std::unique_ptr<ChessMove> move) const = 0; // whether a move is valid (consider all objects)
public:
	// Constructors & Destructor
	ClassicChess();
	ClassicChess(std::string address);
	~ClassicChess();
	// functions to public
	void tryUpgradePawn(const ClassicChessObjectType& type);	// upgrade a pawn after judging whether it's valid
	void tryMove(const std::unique_ptr<ClassicChessMove>& move);	// execute a move after judging whether it's valid
};
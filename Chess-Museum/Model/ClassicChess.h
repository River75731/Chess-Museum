#pragma once
#include <vector>
#include <array>
#include "../Common/Common.h"
#include "Chess.h"


/*
	Classic Chess
	Board : x from 1 to 8 and y from 1 to 8
	Type : Rook, Knight, Bishop, Queen, King, Pawn
	Player : White(0) and Black(1)
	Status : 0(Interrupt : Upgrade Pawn), 1(Not End, White turn), 2(Not End, Black turn), 
			 3(Not End, White Being checked), 4(Not End, Black Being checked), 
			 5(End, White Win), 6(End, Black Win)
	ObjectStatus : Dead(0) and Alive(1)
	Objects : index in board array
	Board Array : [64], each has a unique_ptr<ClssicChessObject>, can be nullptr
	Move Type : Passive(0) and Active(1) NOTE: Passive for castling rooks, or being killed
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
	CLASSICCHESS_INTERRUPT_UPGRADEPAWN_WHITE,
	CLASSICCHESS_INTERRUPT_UPGRADEPAWN_BLACK,
	CLASSICCHESS_WHITE_TURN,
	CLASSICCHESS_BLACK_TURN,
	CLASSICCHESS_WHITE_CHECK,	// white being checked
	CLASSICCHESS_BLACK_CHECK,	// black being checked
	CLASSICCHESS_WHITE_WIN,
	CLASSICCHESS_BLACK_WIN
};

enum ClassicChessObjectStatus {
	CLASSICCHESS_DEAD,
	CLASSICCHESS_ALIVE
};

enum ClassicChessMoveType {
	CLASSICCHESS_PASSIVEMOVE,
	CLASSICCHESS_ACTIVEMOVE
};

class ClassicChessPosition final : public Position2i, public ChessPosition{
public:
	ClassicChessPosition();
	ClassicChessPosition(const int& x, const int& y);
	ClassicChessPosition(const Position2i& that);
	ClassicChessPosition(const ClassicChessPosition& that);
	~ClassicChessPosition();
	bool isValid() const; // whether it's on board
	void output(const std::string &name = "DEFAULT") const;
};

// const type ClassicChessObject : object cannot be modified
class ClassicChessObject final {	
private:
	const int index;
	const ClassicChessObjectStatus status;
	const ClassicChessObjectType type;
	const ClassicChessPlayerType player;
	const ClassicChessPosition position;
public:
	// Constructor & Destructor
	ClassicChessObject();
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
class ClassicChessMove final : public ChessMove{
private:
	const ClassicChessObject object;
	const ClassicChessPosition dest;
	const ClassicChessMoveType type;
public:
	// Constructor & Destructor
	ClassicChessMove(const ClassicChessObject& object, const ClassicChessPosition& dest, const ClassicChessMoveType& type = CLASSICCHESS_ACTIVEMOVE);
	ClassicChessMove(const ClassicChessObject& object, const int& x, const int& y, const ClassicChessMoveType& type = CLASSICCHESS_ACTIVEMOVE);
	ClassicChessMove(const ClassicChessMove& that);
	~ClassicChessMove();
	// Get Method
	const ClassicChessObject getObject() const;
	const ClassicChessPosition getDest() const;
	const ClassicChessMoveType getType() const;
	/*
		Valid Move :
		1 > Both Position of Object and Destination should be valid and shouldn't be the same
		2 > Object should be ALIVE
		3 > PAWN is allowed to move forward 1 step or 2 steps(beginning), and horizontally 1 step (kill other) or 0 step
		4 > ROOK goes straight forward horizontally or vertically
		5 > KNIGHT goes straight forward for 2 steps and horizontally one step
		6 > BISHOP goes horizontally n steps and vertically n steps
		7 > QUEEN goes for BISHOP unions ROOK
		8 > KING goes one step for any direction , two steps for castling
	*/
	bool isValid() const;	
};

class ClassicChess final : public Chess{
private:
	ClassicChessStatus status;
	std::array<int, 32> objects;		// store the object locations in array board, -1 if dead
	std::array<std::unique_ptr<ClassicChessObject>, 64> board;	// store the board
	std::vector<std::unique_ptr<ClassicChessMove>> history; // chess history

	// functions
	ClassicChessPosition toPosition(const int& index) const; // index to position
	int toIndex(const ClassicChessPosition& position) const; // position to index
	int toIndex(const Position2i& position) const;
	bool validIndex(const Position2i& position, const Vector2i& delta) const;

	void loadMsg(std::string address);
	void saveMsg(std::string address);

	bool isBlocked(const Position2i &src, const Position2i& dest) const;
	bool isChecked(const ClassicChessPlayerType player) const;
	void execMove(const std::unique_ptr<ClassicChessMove> &move);	// execute a move
	bool isValidMove(const std::unique_ptr<ClassicChessMove>& move) const; // whether a move is valid (consider all objects)
	void tryMove(const std::unique_ptr<ClassicChessMove>& move);	// execute a move after judging whether it's valid
public:
	static const std::map<const std::string, const ClassicChessStatus> stringToStatus;
	static const std::map<const std::string, const ClassicChessMoveType> stringToMoveType;
	static const std::map<const std::string, const ClassicChessObjectStatus> stringToObjectStatus;
	static const std::map<const std::string, const ClassicChessPlayerType> stringToPlayerType;
	static const std::map<const std::string, const ClassicChessObjectType> stringToObjectType;

	// Constructors & Destructor
	ClassicChess(const std::string &address = "./Data/DefaultChess.txt");
	ClassicChess(const ClassicChess& that);
	~ClassicChess();
	// functions to public
	void reset(std::string address);
	void tryUpgradePawn(const ClassicChessObjectType& type);	// upgrade a pawn after judging whether it's valid
	void tryMove(const Position2i &src, const Position2i& dest);	
	// Get Method
	const ClassicChessStatus getStatus() const;
	const std::array<int, 32> getIndex() const;

	const ClassicChessObject getObject(const Position2i& position) const;
	const bool isEmpty(const Position2i& position) const;
	const bool isValidChoice(const Position2i& position) const;
	const ClassicChessObjectType getObjectType(const Position2i& position) const;
	const ClassicChessPlayerType getPlayerType(const Position2i& position) const;

};
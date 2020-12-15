#pragma once
#include"Common.h"

#include <memory>

class ChessPosition {
public:
	virtual bool isValid() const = 0; // whether a position is valid (regardless of other objects)
};

class ChessMove{
public:
	virtual bool isValid() const = 0; // whether a move is valid (regardless of other objects)
};

class Chess {
protected:
	virtual void execMove(std::unique_ptr<ChessMove> move) = 0;	// execute a move
	virtual bool isValidMove(std::unique_ptr<ChessMove> move) const = 0; // whether a move is valid (consider all objects)
public:
	virtual void tryMove(std::unique_ptr<ChessMove> move) = 0;	// execute a move after judging whether it's valid
};
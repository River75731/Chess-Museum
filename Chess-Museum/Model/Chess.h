#pragma once
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
public:
};
#pragma once

#include <memory>

class ChessPosition {

};

class ChessMove {

};

class Chess {
public:
	virtual bool isValidMove(std::unique_ptr<ChessMove> move) const = 0;
	virtual void execMove(std::unique_ptr<ChessMove> move) = 0;
};
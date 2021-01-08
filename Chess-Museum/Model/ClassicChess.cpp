#include "ClassicChess.h"

ClassicChessPosition::ClassicChessPosition() : Position2i()
{
}

ClassicChessPosition::ClassicChessPosition(const int& x, const int& y) : Position2i(x, y)
{
}

ClassicChessPosition::ClassicChessPosition(const ClassicChessPosition & that) : Position2i(that.getX(), that.getY())
{
}

bool ClassicChessPosition::isValid() const
{
	return this->inRange(1, 1, 8, 8);
}

void ClassicChessPosition::output(const std::string &name) const
{
	std::cout << "ClassicChessPosition2i : " << name << "\t = ( " << this->x << " , " << this->y << " ).\n";
}

ClassicChessObject::ClassicChessObject(const int& index, const ClassicChessPlayerType& player, const ClassicChessPosition& position, const ClassicChessObjectType& type, const ClassicChessObjectStatus& status) : index(index), player(player), position(position), status(status), type(type)
{
}

ClassicChessObject::ClassicChessObject(const ClassicChessObject & that) : index(that.getIndex()), status(that.getStatus()), type(that.getType()), player(that.getPlayer()), position(that.getPosition())
{
}

ClassicChessObject::~ClassicChessObject()
{
}

const int ClassicChessObject::getIndex() const
{
	return this->index;
}

const ClassicChessObjectStatus ClassicChessObject::getStatus() const
{
	return this->status;
}

const ClassicChessObjectType ClassicChessObject::getType() const
{
	return this->type;
}

const ClassicChessPlayerType ClassicChessObject::getPlayer() const
{
	return this->player;
}

const ClassicChessPosition ClassicChessObject::getPosition() const
{
	return this->position;
}

ClassicChessMove::ClassicChessMove(const ClassicChessObject & object, const ClassicChessPosition & dest, const ClassicChessMoveType& type) : object(object), dest(dest), type(type)
{
}

ClassicChessMove::ClassicChessMove(const ClassicChessObject & object, const int& x, const int& y, const ClassicChessMoveType& type) : object(object), dest(x, y), type(type)
{
}

ClassicChessMove::ClassicChessMove(const ClassicChessMove & that) : object(that.getObject()), dest(that.getDest()), type(that.getType())
{
}

ClassicChessMove::~ClassicChessMove()
{
}

const ClassicChessObject ClassicChessMove::getObject() const
{
	return object;
}

const ClassicChessPosition ClassicChessMove::getDest() const
{
	return dest;
}

const ClassicChessMoveType ClassicChessMove::getType() const
{
	return type;
}

bool ClassicChessMove::isValid() const
{
	ClassicChessPosition source(object.getPosition());
	if (!source.isValid() || !dest.isValid()) return false;
	if (object.getStatus() == CLASSICCHESS_DEAD) return false;
	if (source == dest) return false;
	Vector2i delta = dest - source;
	switch (object.getType()) {
		case CLASSICCHESS_PAWN:
			if ((source.getY() == 2 && object.getPlayer() == CLASSICCHESS_WHITE) ||
				(source.getY() == 7 && object.getPlayer() == CLASSICCHESS_BLACK)) { // beginning
				if (object.getPlayer() == CLASSICCHESS_WHITE) {
					if (delta == Vector2i(0, 2) || delta == Vector2i(1, 1) || delta == Vector2i(0, 1) || delta == Vector2i(-1, 1)) return true;
					else return false;
				}
				else {
					if (delta == Vector2i(0, -2) || delta == Vector2i(1, -1) || delta == Vector2i(0, -1) || delta == Vector2i(-1, -1)) return true;
					else return false;
				}
			}
			else {
				if (object.getPlayer() == CLASSICCHESS_WHITE) {
					if (delta == Vector2i(1, 1) || delta == Vector2i(0, 1) || delta == Vector2i(-1, 1)) return true;
					else return false;
				}
				else {
					if (delta == Vector2i(1, -1) || delta == Vector2i(0, -1) || delta == Vector2i(-1, -1)) return true;
					else return false;
				}
			}
			break;
		case CLASSICCHESS_ROOK:
			if (delta.getX() == 0 || delta.getY() == 0) return true;
			else return false;
			break;
		case CLASSICCHESS_KNIGHT:
			if ((abs(delta.getX()) == 2 && abs(delta.getY()) == 1) || (abs(delta.getX()) == 1 && abs(delta.getY()) == 2)) return true;
			else return false;
			break;
		case CLASSICCHESS_BISHOP:
			if (abs(delta.getX()) == abs(delta.getY())) return true;
			else return false;
			break;
		case CLASSICCHESS_QUEEN:
			if (abs(delta.getX()) == abs(delta.getY()) || delta.getX() == 0 || delta.getY() == 0) return true;
			else return false;
			break;
		case CLASSICCHESS_KING:
			if (Position2i(delta).inRange(-1, -1, 1, 1)) return true;
			else if ((source == Position2i(5, 1) && object.getPlayer() == CLASSICCHESS_WHITE) ||
				(source == Position2i(5, 8) && object.getPlayer() == CLASSICCHESS_BLACK))
				if (delta == Vector2i(2, 0) || delta == Vector2i(-2, 0)) return true; // castling
			else return false;
			break;
	}
	return false;
}

ClassicChessPosition ClassicChess::toPosition(const int & index) const
{
	return ClassicChessPosition(index % 8 + 1, index / 8 + 1);
}

int ClassicChess::toIndex(const ClassicChessPosition & position) const
{
	return position.getY() * 8 + position.getX() - 9;
}

int ClassicChess::toIndex(const Position2i & position) const
{
	return position.getY() * 8 + position.getX() - 9;
}

bool ClassicChess::validIndex(const Position2i & position, const Vector2i & delta) const
{
	Position2i newpos = position + delta;
	return toIndex(newpos) >= 0 && toIndex(newpos) <= 63;
}

bool ClassicChess::isChecked(const ClassicChessPlayerType player) const
{
	// Find king
	ClassicChessPosition pos;
	for (int i = 0; i <= 31; i++)
	{
		if (board.at(objects.at(i))->getPlayer() == player && board.at(objects.at(i))->getType() == CLASSICCHESS_KING)
		{
			pos = board.at(objects.at(i))->getPosition();
			break;
		}
	}
	// Pawn Check
	int pawnDeltaY = (player == CLASSICCHESS_BLACK ? 1 : -1);
	if (validIndex(pos, Vector2i(1,pawnDeltaY)))
		if(board.at(toIndex(pos + Vector2i(1, pawnDeltaY)))->getPlayer() != player && board.at(toIndex(pos + Vector2i(1, pawnDeltaY)))->getType() == CLASSICCHESS_PAWN) return true;
	if (validIndex(pos, Vector2i(-1,pawnDeltaY)))
		if(board.at(toIndex(pos + Vector2i(-1, pawnDeltaY)))->getPlayer() != player && board.at(toIndex(pos + Vector2i(-1, pawnDeltaY)))->getType() == CLASSICCHESS_PAWN) return true;
	// King Check
	Vector2i kingDelta[8] = { {0,1},{0,-1},{1,0},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1} };
	for (int i = 0; i <= 7; i++) {
		if (validIndex(pos, kingDelta[i]))
			if (board.at(toIndex(pos + kingDelta[i]))->getPlayer() != player && board.at(toIndex(pos + kingDelta[i]))->getType() == CLASSICCHESS_KING) return true;
	}
	// Knight Check
	Vector2i knightDelta[8] = { {2,1},{2,-1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2} };
	for (int i = 0; i <= 7; i++) {
		if (validIndex(pos, knightDelta[i]))
			if (board.at(toIndex(pos + knightDelta[i]))->getPlayer() != player && board.at(toIndex(pos + knightDelta[i]))->getType() == CLASSICCHESS_KING) return true;
	}
	// Bishop & Queen Check
	bool bishopBlocked[4] = { false,false,false,false };
	for (int i = 1; i <= 7; i++) {
		if (bishopBlocked[0] && bishopBlocked[1] && bishopBlocked[2] && bishopBlocked[3]) break;
		Vector2i bishopDelta[4] = { {i,i},{-i,i},{i,-i},{-i,-i} };
		for (int j = 0; j <= 3; j++) {
			if (!bishopBlocked[j]) {
				if (validIndex(pos, bishopDelta[j])) {
					if (board.at(toIndex(pos + bishopDelta[j]))->getType() != CLASSICCHESS_EMPTY) {
						if (board.at(toIndex(pos + bishopDelta[j]))->getPlayer() != player && (board.at(toIndex(pos + bishopDelta[j]))->getType() == CLASSICCHESS_BISHOP || board.at(toIndex(pos + bishopDelta[j]))->getType() == CLASSICCHESS_QUEEN)) return true;
						else bishopBlocked[j] = true;
					}
				}
			}
		}
	}
	// Rook & Queen Check
	bool rookBlocked[4] = { false,false,false,false };
	for (int i = 1; i <= 7; i++) {
		if (rookBlocked[0] && rookBlocked[1] && rookBlocked[2] && rookBlocked[3]) break;
		Vector2i rookDelta[4] = { {i,0},{-i,0},{0,i},{0,-i} };
		for (int j = 0; j <= 3; j++) {
			if (!rookBlocked[j]) {
				if (validIndex(pos, rookDelta[j])) {
					if (board.at(toIndex(pos + rookDelta[j]))->getType() != CLASSICCHESS_EMPTY) {
						if (board.at(toIndex(pos + rookDelta[j]))->getPlayer() != player && (board.at(toIndex(pos + rookDelta[j]))->getType() == CLASSICCHESS_BISHOP || board.at(toIndex(pos + rookDelta[j]))->getType() == CLASSICCHESS_QUEEN)) return true;
						else rookBlocked[j] = true;
					}
				}
			}
		}
	}
	return false;
}

void ClassicChess::execMove(std::unique_ptr<ChessMove> move)
{

}

bool ClassicChess::isValidMove(std::unique_ptr<ChessMove> move) const
{
	switch (status)
	{
	/*
		In UPGRADEPAWN mode, only allow a passive move which move a queen/rook/knight/bishop to 
	*/
	case CLASSICCHESS_INTERRUPT_UPGRADEPAWN:

	case CLASSICCHESS_WHITE_TURN:

	case CLASSICCHESS_BLACK_TURN:

	case CLASSICCHESS_WHITE_CHECK:	// white being checked

	case CLASSICCHESS_BLACK_CHECK:	// black being checked
	case CLASSICCHESS_WHITE_WIN:
	case CLASSICCHESS_BLACK_WIN:;
	}
	return true;
}

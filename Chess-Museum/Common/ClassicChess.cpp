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

ClassicChessMove::ClassicChessMove(const ClassicChessObject & object, const ClassicChessPosition & dest) : object(object), dest(dest)
{
}

ClassicChessMove::ClassicChessMove(const ClassicChessObject & object, const int& x, const int& y) : object(object), dest(x, y)
{
}

ClassicChessMove::ClassicChessMove(const ClassicChessMove & that) : object(that.getObject()), dest(that.getDest())
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
			else return false;
			break;
	}
	return false;
}

ClassicChess::ClassicChess()
{
}

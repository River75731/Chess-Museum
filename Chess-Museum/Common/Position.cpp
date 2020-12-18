#include "Position.h"

Position2f::Position2f()
{
	this->x = 0;
	this->y = 0;
}

Position2f::Position2f(const float & x, const float & y)
{
	this->x = x;
	this->y = y;
}

Position2f::Position2f(const Vector2f & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Position2f::Position2f(const Position2i & that)
{
	this->x = (float)(that.getX());
	this->y = (float)(that.getY());
}

Position2f::Position2f(const Position2f & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Position2f::~Position2f()
{
}

const float Position2f::getX() const
{
	return this->x;
}

const float Position2f::getY() const
{
	return this->y;
}

Position2f& Position2f::setX(const float & x)
{
	this->x = x;
	return *this;
}

Position2f& Position2f::setY(const float & y)
{
	this->y = y;
	return *this;
}

Position2f Position2f::operator+(const Vector2f & that) const
{
	return Position2f(this->x + that.getX(), this->y + that.getY());
}

Position2f Position2f::operator-(const Vector2f & that) const
{
	return Position2f(this->x - that.getX(), this->y - that.getY());
}

Vector2f Position2f::operator-(const Position2f & that) const
{
	return Vector2f(this->x - that.getX(), this->y - that.getY());
}

bool Position2f::operator==(const Position2f & that) const
{
	return floatEqual(this->x, that.getX()) && floatEqual(this->y, that.getY());
}

bool Position2f::operator!=(const Position2f & that) const
{
	return !floatEqual(this->x, that.getX()) || !floatEqual(this->y, that.getY());
}

Position2f & Position2f::operator=(const Position2f & that)
{
	this->x = that.getX();
	this->y = that.getY();
	return *this;
}

Position2f & Position2f::operator+=(const Vector2f & that)
{
	this->x += that.getX();
	this->y += that.getY();
	return *this;
}

Position2f & Position2f::operator-=(const Vector2f & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	return *this;
}

bool Position2f::inArea(const float & xmin, const float & ymin, const float & xlength, const float & ylength) const
{
	return (this->x >= xmin) && (this->y >= ymin) && (this->x <= xmin + xlength) && (this->x <= ymin + ylength);
}

Position2f & Position2f::setInArea(const float & xmin, const float & ymin, const float & xlength, const float & ylength)
{
	if (this->x < xmin) this->x = xmin;
	if (this->x > xmin + xlength) this->x = xmin + xlength;
	if (this->y < ymin) this->y = ymin;
	if (this->y > ymin + ylength) this->y = ymin + ylength;
	return *this;
}

bool Position2f::inRange(const float & xmin, const float & ymin, const float & xmax, const float & ymax) const
{
	return (x >= xmin) && (x <= xmax) && (y >= ymin) && (y <= ymax);
}

Position2f & Position2f::setInRange(const float & xmin, const float & ymin, const float & xmax, const float & ymax)
{
	if (this->x < xmin) this->x = xmin;
	if (this->x > xmax) this->x = xmax;
	if (this->y < ymin) this->y = ymin;
	if (this->y > ymax) this->y = ymax;
	return *this;
}

void Position2f::output(const std::string & name) const
{
	std::cout << "Position2f : " << name << "\t = ( " << this->x << " , " << this->y << " ).\n";
}

Position2i::Position2i()
{
	this->x = 0;
	this->y = 0;
}

Position2i::Position2i(const int & x, const int & y)
{
	this->x = x;
	this->y = y;
}

Position2i::Position2i(const Vector2i & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Position2i::Position2i(const Position2f & that)
{
	this->x = floatRound(that.getX());
	this->y = floatRound(that.getY());
}

Position2i::Position2i(const Position2i & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Position2i::~Position2i()
{
}

const int Position2i::getX() const
{
	return this->x;
}

const int Position2i::getY() const
{
	return this->y;
}

Position2i & Position2i::setX(const int & x)
{
	this->x = x;
	return *this;
}

Position2i & Position2i::setY(const int & y)
{
	this->y = y;
	return *this;
}

Position2i Position2i::operator+(const Vector2i & that) const
{
	return Position2i(this->x + that.getX(), this->y + that.getY());
}

Position2i Position2i::operator-(const Vector2i & that) const
{
	return Position2i(this->x - that.getX(), this->y - that.getY());
}

Vector2i Position2i::operator-(const Position2i & that) const
{
	return Vector2i(this->x - that.getX(), this->y - that.getY());
}

bool Position2i::operator==(const Position2i & that) const
{
	return this->x == that.getX() && this->y == that.getY();
}

bool Position2i::operator!=(const Position2i & that) const
{
	return this->x != that.getX() || this->y != that.getY();
}

Position2i & Position2i::operator=(const Position2i & that)
{
	this->x = that.getX();
	this->y = that.getY();
	return *this;
}

Position2i & Position2i::operator+=(const Vector2i & that)
{
	this->x += that.getX();
	this->y += that.getY();
	return *this;
}

Position2i & Position2i::operator-=(const Vector2i & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	return *this;
}

bool Position2i::inArea(const int & xmin, const int & ymin, const int & xlength, const int & ylength) const
{
	return this->x >= xmin && this->x <= xmin + xlength && this->y >= ymin && this->y <= ymin + ylength;
}

Position2i & Position2i::setInArea(const int & xmin, const int & ymin, const int & xlength, const int & ylength)
{
	if (this->x < xmin) this->x = xmin;
	if (this->x > xmin + xlength) this->x = xmin + xlength;
	if (this->y < ymin) this->y = ymin;
	if (this->y > ymin + ylength) this->y = ymin + ylength;
	return *this;
}

bool Position2i::inRange(const int & xmin, const int & ymin, const int & xmax, const int & ymax) const
{
	return this->x >= xmin && this->x <= xmax && this->y >= ymin && this->y <= ymax;
}

Position2i & Position2i::setInRange(const int & xmin, const int & ymin, const int & xmax, const int & ymax)
{
	if (this->x < xmin) this->x = xmin;
	if (this->x > xmax) this->x = xmax;
	if (this->y < ymin) this->y = ymin;
	if (this->y > ymax) this->y = ymax;
	return *this;
}

void Position2i::output(const std::string & name) const
{
	std::cout << "Position2i : " << name << "\t = ( " << this->x << " , " << this->y << " ).\n";
}

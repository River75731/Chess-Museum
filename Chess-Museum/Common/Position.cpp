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

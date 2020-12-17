#include "Vector.h"

Vector2f::Vector2f()
{
	x = 0;
	y = 0;
}

Vector2f::Vector2f(const float & x, const float & y)
{
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(const Vector2f & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Vector2f::~Vector2f()
{
}

const float Vector2f::getX() const
{
	return x;
}

const float Vector2f::getY() const
{
	return y;
}

Vector2f& Vector2f::setX(const float & x)
{
	this->x = x;
	return *this;
}

Vector2f& Vector2f::setY(const float & y)
{
	this->y = y;
	return *this;
}

const float Vector2f::getAngle() const
{
	float angle = acos(x / this->getLength());
	return y >= 0 ? angle : 360 - angle;
}

Vector2f Vector2f::operator+(const Vector2f & that) const
{
	return Vector2f(this->x + that.getX(), this->y + that.getY());
}

Vector2f Vector2f::operator-(const Vector2f & that) const
{
	return Vector2f(this->x - that.getX(), this->y - that.getY());
}

Vector2f Vector2f::operator-() const
{
	return Vector2f(-this->x, -this->y);
}

Vector2f Vector2f::operator*(const float & that) const
{
	return Vector2f(this->x * that, this->y * that);
}

Vector2f Vector2f::operator/(const float & that) const
{
	return Vector2f(this->x / that, this->y / that);
}

bool Vector2f::operator==(const Vector2f & that) const
{
	return floatEqual(this->x, that.getX()) && floatEqual(this->y, that.getY());
}

bool Vector2f::operator!=(const Vector2f & that) const
{
	return !floatEqual(this->x, that.getX()) || !floatEqual(this->y, that.getY());
}

Vector2f & Vector2f::operator=(const Vector2f & that)
{
	this->x = that.getX();
	this->y = that.getY();
	return *this;
}

Vector2f & Vector2f::operator+=(const Vector2f & that)
{
	this->x += that.getX();
	this->y += that.getY();
	return *this;
}

Vector2f & Vector2f::operator-=(const Vector2f & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	return *this;
}

Vector2f & Vector2f::operator*=(const float & that)
{
	this->x *= that;
	this->y *= that;
	return *this;
}

Vector2f & Vector2f::operator/=(const float & that)
{
	this->x /= that;
	this->y /= that;
	return *this;
}

const float Vector2f::dot(const Vector2f & that) const
{
	return this->x * that.getX() + this->y * that.getY();
}

const float Vector2f::getLength() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2f & Vector2f::normalize()
{
	float length = this->getLength();
	this->x /= length;
	this->y /= length;
	return *this;
}

Vector2f & Vector2f::scale(const float & scaleX, const float & scaleY)
{
	this->x *= scaleX;
	this->y *= scaleY;
	return *this;
}

Vector2f & Vector2f::rotate(const float & angle)
{
	float newAngle = angle + this->getAngle();
	float length = this->getLength();
	this->x = cos(newAngle) * length;
	this->y = sin(newAngle) * length;
	return *this;
}

const float Vector2f::angle(const Vector2f & that) const
{
	return that.getAngle() - this->getAngle();
}


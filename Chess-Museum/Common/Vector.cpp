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

Vector2f::Vector2f(const Vector2i & that)
{
	this->x = (float)(that.getX());
	this->y = (float)(that.getY());
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
	if (floatEqual(x, 0) && floatEqual(y, 0)) return 0;
	float angle = toDegree(acos(x / this->getLength()));
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

void Vector2f::output(const std::string &name) const
{
	std::cout << "Vector2f : " << name << "\t = ( " << this->x << " , " << this->y << " ),\t Length = " << this->getLength() << ",\t Angle = " << this->getAngle() << " degree.\n";
	return;
}

Vector2i::Vector2i()
{
	this->x = 0;
	this->y = 0;
}

Vector2i::Vector2i(const int & x, const int & y)
{
	this->x = x;
	this->y = y;
}

Vector2i::Vector2i(const Vector2i & that)
{
	this->x = that.getX();
	this->y = that.getY();
}

Vector2i::Vector2i(const Vector2f & that)
{
	this->x = floatRound(that.getX());
	this->y = floatRound(that.getY());
}

Vector2i::~Vector2i()
{
}

const int Vector2i::getX() const
{
	return this->x;
}

const int Vector2i::getY() const
{
	return this->y;
}

Vector2i & Vector2i::setX(const int & x)
{
	this->x = x;
	return *this;
}

Vector2i & Vector2i::setY(const int & y)
{
	this->y = y;
	return *this;
}

const float Vector2i::getAngle() const
{
	if (x == 0 && y == 0) return 0;
	float angle = toDegree(acos(x / this->getLength()));
	return y >= 0 ? angle : 360 - angle;
}

const float Vector2i::getLength() const
{
	return (float)sqrt(this->x * this->x + this->y * this->y);
}

Vector2i Vector2i::operator+(const Vector2i & that) const
{
	return Vector2i(this->x + that.getX(), this->y + that.getY());
}

Vector2i Vector2i::operator-(const Vector2i & that) const
{
	return Vector2i(this->x - that.getX(), this->y - that.getY());
}

Vector2i Vector2i::operator-() const
{
	return Vector2i(-this->x, -this->y);
}

Vector2i Vector2i::operator*(const int & that) const
{
	return Vector2i(this->x * that, this->y * that);
}

Vector2i Vector2i::operator/(const int & that) const
{
	return Vector2i(this->x / that, this->y / that);
}

bool Vector2i::operator==(const Vector2i & that) const
{
	return this->x == that.getX() && this->y == that.getY();
}

bool Vector2i::operator!=(const Vector2i & that) const
{
	return this->x != that.getX() || this->y != that.getY();
}

Vector2i & Vector2i::operator=(const Vector2i & that)
{
	this->x = that.getX();
	this->y = that.getY();
	return *this;
}

Vector2i & Vector2i::operator+=(const Vector2i & that)
{
	this->x += that.getX();
	this->y += that.getY();
	return *this;
}

Vector2i & Vector2i::operator-=(const Vector2i & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	return *this;
}

Vector2i & Vector2i::operator*=(const int & that)
{
	this->x *= that;
	this->y *= that;
	return *this;
}

Vector2i & Vector2i::operator/=(const int & that)
{
	this->x /= that;
	this->y /= that;
	return *this;
}

const int Vector2i::dot(const Vector2i & that) const
{
	return this->x * that.getX() + this->y * that.getY();
}

Vector2i & Vector2i::scale(const int & scaleX, const int & scaleY)
{
	this->x *= scaleX;
	this->y *= scaleY;
	return *this;
}

Vector2i & Vector2i::rotate(const int & angle)
{
	int smallAngle = angle % 360;
	if (smallAngle == 180 || smallAngle == -180)
	{
		this->x = -this->x;
		this->y = -this->y;
		return *this;
	}
	if (smallAngle == 90 || smallAngle == -270)
	{
		smallAngle = this->x;
		this->x = -this->y;
		this->y = this->x;
		return *this;
	}
	if (smallAngle == -90 || smallAngle == 270)
	{
		smallAngle = this->x;
		this->x = this->y;
		this->y = -this->x;
		return *this;
	}
	return *this;
}

const float Vector2i::angle(const Vector2i & that) const
{
	return that.getAngle() - this->getAngle();
}

void Vector2i::output(const std::string & name) const
{
	std::cout << "Vector2i : " << name << "\t = ( " << this->x << " , " << this->y << " ),\t Length = " << this->getLength() << ",\t Angle = " << this->getAngle() << " degree.\n";
	return;
}

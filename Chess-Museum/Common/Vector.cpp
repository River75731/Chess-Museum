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

Vector3f::Vector3f()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(const float & x, const float & y, const float & z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f(const Vector3f & that)
{
	this->x = that.getX();
	this->y = that.getY();
	this->z = that.getZ();
}

Vector3f::Vector3f(const Vector3i & that)
{
	this->x = (float)(that.getX());
	this->y = (float)(that.getY());
	this->z = (float)(that.getZ());
}

Vector3f::~Vector3f()
{
}

const float Vector3f::getX() const
{
	return this->x;
}

const float Vector3f::getY() const
{
	return this->y;
}

const float Vector3f::getZ() const
{
	return this->z;
}

Vector3f & Vector3f::setX(const float & x)
{
	this->x = x;
	return *this;
}

Vector3f & Vector3f::setY(const float & y)
{
	this->y = y;
	return *this;
}

Vector3f & Vector3f::setZ(const float & z)
{
	this->z = z;
	return *this;
}

const float Vector3f::getLength() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3f Vector3f::operator+(const Vector3f & that) const
{
	return Vector3f(this->x + that.getX(), this->y + that.getY(), this->z + that.getZ());
}

Vector3f Vector3f::operator-(const Vector3f & that) const
{
	return Vector3f(this->x - that.getX(), this->y - that.getY(), this->z - that.getZ());
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-this->x, -this->y, -this->z);
}

Vector3f Vector3f::operator*(const float & that) const
{
	return Vector3f(this->x * that, this->y * that, this->z * that);
}

Vector3f Vector3f::operator/(const float & that) const
{
	return Vector3f(this->x / that, this->y / that, this->z / that);
}

bool Vector3f::operator==(const Vector3f & that) const
{
	return floatEqual(this->x, that.getX()) && floatEqual(this->y, that.getY()) && floatEqual(this->z, that.getZ());
}

bool Vector3f::operator!=(const Vector3f & that) const
{
	return !floatEqual(this->x, that.getX()) || !floatEqual(this->y, that.getY()) || !floatEqual(this->z, that.getZ());
}

Vector3f & Vector3f::operator=(const Vector3f & that)
{
	this->x = that.getX();
	this->y = that.getY();
	this->z = that.getZ();
	return *this;
}

Vector3f & Vector3f::operator+=(const Vector3f & that)
{
	this->x += that.getX();
	this->y += that.getY();
	this->z += that.getZ();
	return *this;
}

Vector3f & Vector3f::operator-=(const Vector3f & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	this->z -= that.getZ();
	return *this;
}

Vector3f & Vector3f::operator*=(const float & that)
{
	this->x *= that;
	this->y *= that;
	this->z *= that;
	return *this;
}

Vector3f & Vector3f::operator/=(const float & that)
{
	this->x /= that;
	this->y /= that;
	this->z /= that;
	return *this;
}

const float Vector3f::dot(const Vector3f & that) const
{
	return this->x * that.getX() + this->y * that.getY() + this->z * that.getZ();
}

Vector3f & Vector3f::normalize()
{
	if ((*this) == Vector3f()) return *this;
	float length = this->getLength();
	this->x /= length;
	this->y /= length;
	this->z /= length;
	return *this;
}

Vector3f & Vector3f::scale(const float & scaleX, const float & scaleY, const float & scaleZ)
{
	this->x *= scaleX;
	this->y *= scaleY;
	this->z *= scaleZ;
	return *this;
}

void Vector3f::output(const std::string & name) const
{
	std::cout << "Vector3f : " << name << "\t = ( " << this->x << " , " << this->y << " , " << this->z << " ),\t Length = " << this->getLength() << ".\n";
}

Vector3i::Vector3i()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3i::Vector3i(const int & x, const int & y, const int & z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3i::Vector3i(const Vector3i & that)
{
	this->x = that.getX();
	this->y = that.getY();
	this->z = that.getZ();
}

Vector3i::Vector3i(const Vector3f & that)
{
	this->x = floatRound(that.getX());
	this->y = floatRound(that.getY());
	this->z = floatRound(that.getZ());
}

Vector3i::~Vector3i()
{
}

const int Vector3i::getX() const
{
	return this->x;
}

const int Vector3i::getY() const
{
	return this->y;
}

const int Vector3i::getZ() const
{
	return this->z;
}

Vector3i & Vector3i::setX(const int & x)
{
	this->x = x;
	return *this;
}

Vector3i & Vector3i::setY(const int & y)
{
	this->y = y;
	return *this;
}

Vector3i & Vector3i::setZ(const int & z)
{
	this->z = z;
	return *this;
}

const float Vector3i::getLength() const
{
	return sqrt(float(this->x * this->x + this->y * this->y + this->z * this->z));
}

Vector3i Vector3i::operator+(const Vector3i & that) const
{
	return Vector3i(this->x + that.getX(), this->y + that.getY(), this->z + that.getZ());
}

Vector3i Vector3i::operator-(const Vector3i & that) const
{
	return Vector3i(this->x - that.getX(), this->y - that.getY(), this->z - that.getZ());
}

Vector3i Vector3i::operator-() const
{
	return Vector3i(-this->x, -this->y, -this->z);
}

Vector3i Vector3i::operator*(const int & that) const
{
	return Vector3i(this->x * that, this->y * that, this->z * that);
}

Vector3i Vector3i::operator/(const int & that) const
{
	return Vector3i(this->x / that, this->y / that, this->z / that);
}

bool Vector3i::operator==(const Vector3i & that) const
{
	return this->x == that.getX() && this->y == that.getY() && this->z == that.getZ();
}

bool Vector3i::operator!=(const Vector3i & that) const
{
	return this->x != that.getX() || this->y != that.getY() || this->z != that.getZ();
}

Vector3i & Vector3i::operator=(const Vector3i & that)
{
	this->x = that.getX();
	this->y = that.getY();
	this->z = that.getZ();
	return *this;
}

Vector3i & Vector3i::operator+=(const Vector3i & that)
{
	this->x += that.getX();
	this->y += that.getY();
	this->z += that.getZ();
	return *this;
}

Vector3i & Vector3i::operator-=(const Vector3i & that)
{
	this->x -= that.getX();
	this->y -= that.getY();
	this->z -= that.getZ();
	return *this;
}

Vector3i & Vector3i::operator*=(const int & that)
{
	this->x *= that;
	this->y *= that;
	this->z *= that;
	return *this;
}

Vector3i & Vector3i::operator/=(const int & that)
{
	this->x /= that;
	this->y /= that;
	this->z /= that;
	return *this;
}

const int Vector3i::dot(const Vector3i & that) const
{
	return this->x * that.getX() + this->y * that.getY() + this->z * that.getZ();
}

Vector3i & Vector3i::scale(const int & scaleX, const int & scaleY, const int & scaleZ)
{
	this->x *= scaleX;
	this->y *= scaleY;
	this->z *= scaleZ;
	return *this;
}

void Vector3i::output(const std::string & name) const
{
	std::cout << "Vector3i : " << name << "\t = ( " << this->x << " , " << this->y << " , " << this->z << " ),\t Length = " << this->getLength() << ".\n";
}

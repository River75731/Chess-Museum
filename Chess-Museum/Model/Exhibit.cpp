#include "Exhibit.h"

const float Exhibit::scaleSpeed = 1.05f;
const float Exhibit::scaleMax = 2.0f;
const float Exhibit::rotateSpeed = 0.1f;
const float Exhibit::translateSpeed = 0.05f;
const float Exhibit::translateMax = 1.0f;

Exhibit::Exhibit(const ExhibitType & type, const unsigned int & textureNum, const unsigned int & lightNum = 0, const Vector3f & translate, const float & rotate, const Vector3f & scale, const bool & hasTable, const bool & isRotating)
{
	this->type = type;
	this->textureNum = textureNum;
	this->lightNum = lightNum;
	this->translate = translate;
	this->rotate = rotate;
	this->scale = scale;
	this->hasTable = hasTable;
	this->isRotating = isRotating;
}

Exhibit::Exhibit(const Exhibit & that)
{
	this->type = that.getType();
	this->textureNum = that.getTextureNum();
	this->lightNum = that.getLightNum();
	this->translate = that.getTranslate();
	this->rotate = that.getRotate();
	this->scale = that.getScale();
	this->hasTable = that.getHasTable();
	this->isRotating = that.getIsRotating();
}

Exhibit::~Exhibit()
{
}

const ExhibitType Exhibit::getType() const
{
	return this->type;
}

const unsigned int Exhibit::getTextureNum() const
{
	return this->textureNum;
}

const unsigned int Exhibit::getLightNum() const
{
	return this->lightNum;
}

const bool Exhibit::getIsRotating() const
{
	return this->isRotating;
}

Exhibit & Exhibit::setType(const ExhibitType & type)
{
	this->type = type;
	return *this;
}

Exhibit & Exhibit::setTextureNum(const unsigned int & textureNum)
{
	this->textureNum = textureNum;
	return *this;
}

Exhibit & Exhibit::setLightNum(const unsigned int & lightNum)
{
	this->lightNum = lightNum;
	return *this;
}

Exhibit & Exhibit::setTranslate(const Vector3f & translate)
{
	this->translate = translate;
	return *this;
}

Exhibit & Exhibit::setRotate(const float & rotate)
{
	this->rotate = rotate;
	return *this;
}

Exhibit & Exhibit::setScale(const Vector3f & scale)
{
	this->scale = scale;
	return *this;
}

Exhibit & Exhibit::setHasTable(const bool & hasTable)
{
	this->hasTable = hasTable;
	return *this;
}

Exhibit & Exhibit::setIsRotating(const bool & isRotating)
{
	this->isRotating = isRotating;
	return *this;
}

Exhibit & Exhibit::clearLight()
{
	this->lightNum = 0;
	return *this;
}

Exhibit & Exhibit::clearTexture()
{
	this->textureNum = 0;
	return *this;
}

Exhibit & Exhibit::changeHasTable()
{
	this->hasTable = !this->hasTable;
	return *this;
}

Exhibit & Exhibit::changeIsRotating()
{
	this->isRotating = !this->isRotating;
	return *this;
}

Exhibit & Exhibit::execTranslate(const float & time, const int & directX, const int & directY, const int & directZ)
{
	float moveX = (float)directX, moveY = (float)directY, moveZ = (float)directZ;
	if (directX != 1 && directX != -1) moveX = 0;
	if (directY != 1 && directY != -1) moveY = 0;
	if (directZ != 1 && directZ != -1) moveZ = 0;
	moveX = moveX * time * translateSpeed + translate.getX();
	moveY = moveY * time * translateSpeed + translate.getY();
	moveZ = moveZ * time * translateSpeed + translate.getZ();
	if (moveX > translateMax) moveX = translateMax;
	if (moveX < -translateMax) moveX = -translateMax;
	if (moveY > translateMax) moveY = translateMax;
	if (moveY < -translateMax) moveY = -translateMax;
	if (moveZ > translateMax) moveZ = translateMax;
	if (moveZ < -translateMax) moveZ = -translateMax;
	translate = Vector3f(moveX, moveY, moveZ);
	return *this;
}

Exhibit & Exhibit::execRotate(const float & time, const int & direction)
{
	float move = (float) direction;
	if (direction != 1 && direction != -1) move = 0;
	rotate += move * time * rotateSpeed;
	return *this;
}

Exhibit & Exhibit::execScale(const int & directX, const int & directY, const int & directZ)
{
	float moveX = scale.getX(), moveY = scale.getY(), moveZ = scale.getZ();
	if (directX == 1) {
		moveX *= scaleSpeed;
		if (moveX > scaleMax) moveX = scaleMax;
	}
	if (directX == -1) {
		moveX /= scaleSpeed;
		if (moveX < 1 / scaleMax) moveX = 1 / scaleMax;
	}
	if (directY == 1) {
		moveY *= scaleSpeed;
		if (moveY > scaleMax) moveY = scaleMax;
	}
	if (directY == -1) {
		moveY /= scaleSpeed;
		if (moveY < 1 / scaleMax) moveY = 1 / scaleMax;
	}
	if (directZ == 1) {
		moveZ *= scaleSpeed;
		if (moveZ > scaleMax) moveZ = scaleMax;
	}
	if (directZ == -1) {
		moveZ /= scaleSpeed;
		if (moveZ < 1 / scaleMax) moveZ = 1 / scaleMax;
	}
	scale = Vector3f(moveX, moveY, moveZ);
	return *this;
}


const bool Exhibit::getHasTable() const
{
	return this->hasTable;
}

const Vector3f Exhibit::getTranslate() const
{
	return this->translate;
}

const float Exhibit::getRotate() const
{
	return this->rotate;
}

const Vector3f Exhibit::getScale() const
{
	return this->scale;
}

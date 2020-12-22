#include "ViewObject.h"

int ViewObject2d::objectCount2d = 0;
int ViewObject3d::objectCount3d = 0;

ViewObject2d::ViewObject2d(const std::string & name) : objectIdx(objectCount2d++), objectName(name)
{
}

const int ViewObject2d::getCount()
{
	return objectCount2d;
}

const int ViewObject2d::getIdx() const
{
	return objectIdx;
}

const std::string ViewObject2d::getName() const
{
	return objectName;
}

ViewObject3d::ViewObject3d(const std::string & name) : objectIdx(objectCount3d++), objectName(name)
{
}

const int ViewObject3d::getCount()
{
	return objectCount3d;
}

const int ViewObject3d::getIdx() const
{
	return objectIdx;
}

const std::string ViewObject3d::getName() const
{
	return objectName;
}

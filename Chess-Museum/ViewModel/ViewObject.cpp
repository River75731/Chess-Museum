#include "ViewObject.h"

int ViewObject2d::objectCount2d = 0;
int ViewObject3d::objectCount3d = 0;

ViewObject2d::ViewObject2d() : objectIdx(objectCount2d++)
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

ViewObject3d::ViewObject3d() : objectIdx(objectCount3d++)
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

#pragma once
#include "../Common/Common.h"

// All static object (with texture or without texture) must be inherited from ViewObject2d or ViewObject3d
// Don't instantiate ViewObject!

class ViewObject {
protected:
	static int objectCount;		// the number of static object

	const int objectListIdx;		// the index in gl list (return value of glGenList)
	const std::string objectName;	// name of the object (must be unique)

public:
	virtual void init() = 0;	// generate a object in View
	virtual void draw() = 0;	// call the drawing function in View
};

int ViewObject::objectCount = 0;

class ViewObject2d : public ViewObject {

};

class ViewObject3d : public ViewObject {

};
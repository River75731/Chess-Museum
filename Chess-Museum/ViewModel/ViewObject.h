#pragma once
#include "../Common/Common.h"
#include <gl/glut.h>

// All static object (with texture or without texture) must be inherited from ViewObject2d or ViewObject3d
// There shouldn't include ViewObject2d in a 3d group and shouldn't include a ViewObject3d in a 2d group
// Don't instantiate ViewObject!

class ViewObject {
public:
	virtual void draw() const = 0;	// call the drawing function in View
};

std::vector<std::shared_ptr<ViewObject2d>> object2d;
std::vector<std::shared_ptr<ViewObject3d>> object3d;

// shouldn't be instantialized
class ViewObject2d : public ViewObject {
protected:
	static int objectCount2d;		// the number of static object
	const int objectIdx;			// index in object2d
public:
	ViewObject2d();
	static const int getCount();
	const int getIdx() const;
};

// shouldn't be instantialized
class ViewObject3d : public ViewObject {
protected:
	static int objectCount3d;		// the number of static object
	const int objectIdx;			// index in object3d
public:
	ViewObject3d();
	static const int getCount();
	const int getIdx() const;
};

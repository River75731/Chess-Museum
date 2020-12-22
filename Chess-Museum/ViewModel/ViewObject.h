#pragma once
#include "../Common/Common.h"

// All static object (with texture or without texture) must be inherited from ViewObject2d or ViewObject3d
// There shouldn't include ViewObject2d in a 3d group and shouldn't include a ViewObject3d in a 2d group
// Don't instantiate ViewObject!

class ViewObject {
protected:
	virtual void init() = 0;	// generate a object in View
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
	const std::string objectName;	// name of the object (must be unique)
public:
	ViewObject2d(const std::string& name);
	static const int getCount();
	const int getIdx() const;
	const std::string getName() const;
};

// shouldn't be instantialized
class ViewObject3d : public ViewObject {
protected:
	static int objectCount3d;		// the number of static object
	const int objectIdx;			// index in object3d
	const std::string objectName;	// name of the object (must be unique)
public:
	ViewObject3d(const std::string& name);
	static const int getCount();
	const int getIdx() const;
	const std::string getName() const;
};
#pragma once
#include "../Common/Common.h"
#include "ViewObject.h"

// All dynamic object (with texture or without texture) must be inherited from ViewGroup2d / ViewGroup3d
// Don't instantiate ViewGroup!

class ViewGroup {
protected:
	static int groupCount;
	int groupIdx;
	std::string groupName;
public:
	virtual void init() = 0;
	virtual void draw() = 0;
};

class ViewGroup2d : public ViewGroup {
protected:
	Position2f groupOrigin;
	std::vector<std::shared_ptr<ViewObject2d>> objects;
};

class ViewGroup3d : public ViewGroup {
protected:
	Position3f groupOrigin;
	std::vector<std::shared_ptr<ViewObject3d>> objects;
};



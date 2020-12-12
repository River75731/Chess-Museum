#pragma once
#include "../Common/Common.h"
#include "ViewModel.h"

// All dynamic object (with texture or without texture) must be inherited from ViewGroup2d / ViewGroup3d
// Don't instantiate ViewGroup!

class ViewGroup {
protected:
	static int groupCount;
	int groupNum;
	std::string groupName;
public:
	virtual void init() = 0;
	virtual void draw() = 0;
};

int ViewGroup::groupCount = 0;

class ViewGroup2d : public ViewGroup {
protected:
	Position2d groupOrigin;
	std::vector<std::shared_ptr<ViewObject2d>> objects;
};

class ViewGroup3d : public ViewGroup {
protected:
	Position3d groupOrigin;
	std::vector<std::shared_ptr<ViewObject3d>> objects;
};



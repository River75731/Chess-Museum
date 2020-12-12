#pragma once
#include "../Common/Common.h"
#include "ViewModel.h"

// All dynamic object in one scene(window) should be ViewScene2d or ViewScene3d
// Don't instantiate ViewScene!

class ViewScene {
protected:
	static int sceneCount;

	int sceneNum;
	std::string sceneName;
public:
	virtual void init() = 0;
	virtual void draw() = 0;
};

class ViewScene2d : public ViewScene {
protected:
	std::vector<std::unique_ptr<ViewGroup2d>> groups;
};

class ViewScene3d : public ViewScene {
protected:
	std::vector<std::unique_ptr<ViewGroup3d>> groups;
};
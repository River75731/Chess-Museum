#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#include "gl/glut.h"

enum ViewObjectType
{
	Circle = 1,
	Cone,
	Cube,
	Cylinder,
	Prism,
	Sphere,
	Triangle
};

class View
{
public:
	static void Rotate(float angle, Vec3f axis);
	static void Scale(Vec3f times);
	static void Translate(Vec3f direction);
	static void setList();
	static void DrawModel(ViewObjectType Type, Vec3f direction, float angle, Vec3f axis, Vec3f times);
};
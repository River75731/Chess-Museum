#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#include "gl/glut.h"
#include <map>

enum ViewObjectType
{
	CIRCLE = 1,
	CONE,
	CUBE,
	CYLINDER,
	PRISM3,
	SPHERE,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

class View
{
public:
	static void Rotate(float angle, Vec3f axis);
	static void Scale(Vec3f times);
	static void Translate(Vec3f direction);
	static void setList();
	static void DrawModel(GLuint listN, Vec2f coordinate, Vec3f translate, float angle, Vec3f axis, Vec3f scale);
};
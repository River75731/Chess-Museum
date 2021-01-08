#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#include "gl/glut.h"
#include <map>

#define BUFSIZE 512

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
	static void onMouseMove(int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void SetEyeLocation();
	static void KeyBoardCallBackFunc(unsigned char k, int x, int y);
	static void KeyBoardUpCallBackFunc(unsigned char k, int x, int y);
	static void Display();
	static void Init(int argc, char *argv[]);
	static void Reshape(int w, int h);
	static void Idle();
	static void EyeMove();
	//static void init();
	static bool ButtonDown;
	static bool Move;
	static char Key;
	static void PickMode(int x, int y);
	static int du, OriX, OriY; //du���ӵ��x��ļн�
	static float c;
	static Vec3f EyeLocation;
	static Vec3f EyeDirection;
	static Vec3f EyeUp;
	static Vec3f MoveIncrement;
	static float Pitch, Yaw; //�����ǣ�ƫ����
	static void DrawModel(GLuint listN, Vec2f coordinate, Vec3f translate, float angle, Vec3f axis, Vec3f scale);
};
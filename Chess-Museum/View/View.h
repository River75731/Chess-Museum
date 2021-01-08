#pragma once
#include "gl/glut.h"
#include "../Common/vectors.h"
#include "../Common/MathBase.h"
#define BUFSIZE 512

enum  Viewobject_Type{
	Circle = 1, Cone, Cube, Cylinder,Prism,Sphere,Triangle
};
class View
{
public:
	static void Rotate(float angle, Vec3f axis);
	static void Scale(Vec3f times);
	static void Translate(Vec3f direction);
	static void setList();
	static void DrawModel(Viewobject_Type Type, float angle, Vec3f axis, Vec3f times, Vec3f direction);
	static void onMouseMove(int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void SetEyeLocation();
	static void KeyBoardCallBackFunc(unsigned char k, int x, int y);
	static void KeyBoardUpCallBackFunc(unsigned char k, int x, int y);
	static void Display();
	static void Init(int argc, char* argv[]);
	static void Reshape(int w, int h);
	static void Idle();
	static void EyeMove();
	//static void init();
	static bool ButtonDown;
	static bool Move;
	static char Key;
	static void PickMode(int x, int y);
	static int du, OriX , OriY ;   //duÊÇÊÓµãºÍxÖáµÄ¼Ð½Ç
	static float c ;    
	static Vec3f EyeLocation ;
	static Vec3f EyeDirection;
	static Vec3f EyeUp ;
	static Vec3f MoveIncrement ;
	static float Pitch , Yaw ;//¸©Ñö½Ç£¬Æ«º½½Ç
};
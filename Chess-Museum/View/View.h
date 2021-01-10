#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#pragma comment(lib, "glew32.lib")
#include <gl/glew.h>
#include <gl/glut.h>
#include <map>
#include <vector>
#include <windows.h>

#define BUFSIZE 512
/* Texture */
#define TEXTURE_NUM 20
#define BITMAP_ID 0x4D42
#define imageweight 128
#define imageheight 128

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
	KING,
	TABLE,
	MARBLETABLE,
	CHESSBOARD
};

class View
{
public:
	static void Init(int argc, char *argv[]);
	static void PickMode(int x, int y);
	static void DrawModel(ViewObjectType type, Vec2f coordinate, Vec3f translate, float angle, Vec3f axis, Vec3f scale, int texIndex);

private:
	static void Mouse(int button, int state, int x, int y);
	static void onMouseMove(int x, int y);
	static void EyeMove();
	static void KeyBoardCallBackFunc(unsigned char k, int x, int y);
	static void KeyBoardUpCallBackFunc(unsigned char k, int x, int y);
	static void Display();
	static void Reshape(int w, int h);
	static void Idle();

	static void Rotate(float angle, Vec3f axis);
	static void Scale(Vec3f times);
	static void Translate(Vec3f direction);
	static void SetEyeLocation();

	static void initMapRelation();
	static void setList();

	static unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	static void texload(int i, std::string filename);
	static void initTexture();

	static void loadShader();

	//==========================================================================================
	//==========================================================================================

	static bool ButtonDown;
	static bool Move;
	static char Key;
	static int du, OriX, OriY;
	static float c;
	static Vec3f EyeLocation;
	static Vec3f EyeDirection;
	static Vec3f EyeUp;
	static Vec3f MoveIncrement;
	static float Pitch, Yaw;

	static std::map<std::string, ViewObjectType> objMap; // from OBJ_NAME to TYPE
	static std::map<ViewObjectType, GLuint> listMap; // from TYPE to listNum/VAO
	static std::map<GLuint, unsigned int> VAOMap; // from VAO to FACE_NUM
	static std::map<ViewObjectType, std::vector<int>> texMap;
	static std::string texFileNames[TEXTURE_NUM];
	static unsigned int texture[TEXTURE_NUM];
	static std::string texturePath;
};

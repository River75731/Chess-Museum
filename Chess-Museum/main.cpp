#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "View/View.h"
#include<windows.h>

#include <conio.h>
using namespace std;

#define PI 3.1415926535
static int du = 90, OriX = -1, OriY = -1;   //du是视点和x轴的夹角
static float r = 1.5, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数
float eye[3] = { 0, 0, 2.5 };
float direction[3] = { 0, 0, -1 };
float up[3] = { 0, 1, 0 };

float left_t[3] = { -1, 0, 0 };

float pitch = 0, yaw = 270;
bool but;
enum {
	snowManHeadDL = 1, snowManBodyDL,
};

bool move_t = false;
int s_row, s_col;

void keyboard(unsigned char k, int x, int y)
{	
	move_t = true;

}
void keyboard1(unsigned char k, int x, int y)
{
	move_t = false;

}



void Mouse(int button, int state, int x, int y)
{
	if (GLUT_DOWN == state)
	{
		

		OriX = x, OriY = y;
		but = true;
	}
}

void onMouseMove(int x, int y)
{
	if (but)
	{
		pitch -= (y - OriY) * 0.1;
		yaw += (x - OriX) * 0.1;
		if (pitch > 90.0)
			pitch = 90.0;
		else if (pitch < -90.0)
			pitch = -90.0;
		if (yaw > 360.0)
			yaw = 0.0;
		else if (yaw < 0.0)
			yaw = 360.0;

		direction[0] = 1.0 * cos(c * yaw) * cos(c * pitch);
		direction[1] = 1.0 * sin(c * pitch);
		direction[2] = 1.0 * sin(c * yaw) * cos(c * pitch);
		up[0] = 1.0 * cos(c * yaw) * cos(c * (pitch + 90.0));
		up[1] = 1.0 * sin(c * (pitch + 90.0));
		up[2] = 1.0 * sin(c * yaw) * cos(c * (pitch + 90.0));
		left_t[0] = 1.0 * cos(c * (yaw - 90.0)) * cos(c * pitch);
		left_t[1] = 1.0 * sin(c * pitch);
		left_t[2] = 1.0 * sin(c * (yaw - 90.0)) * cos(c * pitch);

		OriX = x, OriY = y;
	}
}




void reshape(int w, int h)
{
	 
	glViewport(0, 0, w, h);    //截图;1、2为视口的左下角;3、4为视口的宽度和高度
	glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);     //对模型视景矩阵堆栈应用随后的矩阵操作.
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	

	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = { 10, 10, 10, 0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);
	
	

	if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
		char ch = _getch();//使用_getch()函数获取按下的键值
		cout << ch;
	}
	

	View::DrawModel(CUBE, Vec2f(), Vec3f(4, 0, 0), 0, Vec3f(0, 1, 0), Vec3f(2, 2, 2));
	
	
	glutSolidCube(1.0f);


	glutSwapBuffers();

}
void idle()
{
	glutPostRedisplay();
}



int main(int argc, char* argv[])
{
	View::Init(argc, argv);
	return 0;
}

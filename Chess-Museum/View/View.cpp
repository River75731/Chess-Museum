#include "View.h"


bool View::ButtonDown = false;
bool View::Move = false;
int View::du = 90, View::OriX = -1, View::OriY = -1;   
float View::c = PI / 180.0;    //弧度和角度转换参数
Vec3f View::EyeLocation = Vec3f(0, 0, 2.5);
Vec3f View::EyeDirection = Vec3f(0, 0, -1);
Vec3f View::EyeUp = Vec3f(0, 1, 0);
Vec3f View::MoveIncrement = Vec3f(-1, 0, 0);
float View::Pitch = 0, View::Yaw = 270;//俯仰角，偏航角
char View::Key = ' ';
void View::Rotate(float angle, Vec3f axis)
{
	glRotatef(angle, axis.x(), axis.y(), axis.z());
}

void  View::Scale(Vec3f times)
{
	glScalef(times.x(), times.y(), times.z());
}
void View::Translate(Vec3f EyeDirection)
{
	glTranslatef(EyeDirection.x(), EyeDirection.y(), EyeDirection.z());
}
void View::setList()
{

	glNewList(Circle, GL_COMPILE);

	glBegin(GL_POLYGON);

	int i = 0;
	for (i = 0; i <= 360; i++)
	{
		
		float p = i * PI / 180;
		glNormal3f(0, 1, 0);
		glVertex3f(sin(p), 0.0f, cos(p));
	}
	glEnd();

	glEndList();

	glNewList(Cone, GL_COMPILE);
	
	glutSolidCone(1, 1, 32, 32);

	glEndList();

	glNewList(Cube, GL_COMPILE);

	glutSolidCube(1);

	glEndList();

	glNewList(Cylinder, GL_COMPILE);

	for (int i = 0; i <= 360; i++)
	{
		float p = i * PI / 180;
		float q = (i + 1) * PI / 180;

		glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, 0);
		glVertex3f(sin(p), 0.0f, cos(p));
		glVertex3f(sin(q), 0.0f, cos(q));
		glVertex3f(0, 1, 0);
		glVertex3f(sin(p), 1, cos(p));
		glVertex3f(sin(q), 1, cos(q));
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(sin(p), 0.0f, cos(p));
		glVertex3f(sin(q), 0.0f, cos(q));
		glVertex3f(sin(q), 1, cos(q));
		glVertex3f(sin(p), 1, cos(p));
		glEnd();
	}

	glEndList();

	glNewList(Prism, GL_COMPILE);

	glutSolidCube(1);

	glEndList();
	
	glNewList(Sphere, GL_COMPILE);

	glutSolidSphere(1, 32, 32);

	glEndList();

	glNewList(Triangle, GL_COMPILE);

	glEndList();
}
void View::DrawModel(Viewobject_Type Type,float angle,Vec3f axis,Vec3f times,Vec3f EyeDirection)
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Rotate(angle, axis);
	Translate(EyeDirection);
	Scale(times);
	switch (Type)

	{
	case Circle:
		glCallList(Circle);
		break;
	case Cone:

		break;
	case Cube:
		glCallList(Cube);
		break;
	case Cylinder:
		
		break;
	case Prism:

		break;
	case Sphere:

		break;


	default:
		break;
	}
	glPopMatrix();
}

void View::Mouse(int button, int state, int x, int y)
{
	if (GLUT_DOWN == state)
	{
		OriX = x, OriY = y;
		ButtonDown = true;
	}
}

void View::onMouseMove(int x, int y)
{
	
	if (ButtonDown)
	{
		Pitch -= (y - OriY) * 0.1;
		Yaw += (x - OriX) * 0.1;
		if (Pitch > 90.0)
			Pitch = 90.0;
		else if (Pitch < -90.0)
			Pitch = -90.0;
		if (Yaw > 360.0)
			Yaw = 0.0;
		else if (Yaw < 0.0)
			Yaw = 360.0;
		EyeDirection.Set(1.0 * cos(c * Yaw) * cos(c * Pitch), 1.0 * sin(c * Pitch), 1.0 * sin(c * Yaw) * cos(c * Pitch));
		EyeUp.Set(1.0 * cos(c * Yaw) * cos(c * (Pitch + 90.0)), 1.0 * sin(c * (Pitch + 90.0)), 1.0 * sin(c * Yaw) * cos(c * (Pitch + 90.0)));
		MoveIncrement.Set(1.0 * cos(c * (Yaw - 90.0)) * cos(c * Pitch), 1.0 * sin(c * Pitch), 1.0 * sin(c * (Yaw - 90.0)) * cos(c * Pitch));
		OriX = x, OriY = y;
	}
}

void View::SetEyeLocation()
{
	glLoadIdentity();
	gluLookAt(EyeLocation[0], EyeLocation[1], EyeLocation[2],
		EyeLocation[0] + EyeDirection[0], EyeLocation[1] + EyeDirection[1], EyeLocation[2] + EyeDirection[2],
		EyeUp[0], EyeUp[1], EyeUp[2]);
}

void View::KeyBoardCallBackFunc(unsigned char k, int x, int y)
{
	Key = k;
	Move = true;
}

void View::KeyBoardUpCallBackFunc(unsigned char k, int x, int y)
{
	Move = false;
}
void View::EyeMove()
{
	switch (Key)
	{
	case 'w':
		EyeLocation += 0.01*EyeDirection;
		break;
	case 's':
		EyeLocation -= 0.01*EyeDirection;
		break;
	case 'a':
		EyeLocation += 0.01*MoveIncrement;
		break;
	case 'd':
		EyeLocation -= 0.01*MoveIncrement;
		break;
	case 'z':
		EyeLocation -= 0.01*EyeUp;
		break;
	case 'c':
		EyeLocation += 0.1*EyeUp;
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}
void View::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	SetEyeLocation();
	if(Move)
	EyeMove();
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = { 10, 10, 10, 0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);
	DrawModel(Cube, 0, Vec3f(0, 1, 0), Vec3f(2, 2, 2), Vec3f(4, 0, 0));
	glutSolidCube(1.0f);
	glutSwapBuffers();
}
void View::PickMode(int x, int y)
{
	GLuint selectBuf[BUFSIZE];
	GLint viewport[4];
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(x, viewport[3] - y, 5, 5, viewport);

	gluPerspective(45, 1, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
	
	int hits;

	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering model
	hits = glRenderMode(GL_RENDER);

	// if there are hits process them
	if (hits != 0)
	{
		unsigned int i, j;
		GLuint names, *ptr, minZ, *ptrNames, numberOfNames;

		printf("hits = %d\n", hits);
		ptr = (GLuint *)selectBuf;
		ptrNames = ptr + 3;
		minZ = 0xffffffff;

		for (i = 0; i < hits; i++) {
			names = *ptr;
			ptr++;

			if (*ptr < minZ) {
				numberOfNames = names;
				minZ = *ptr;
				ptrNames = ptr + 2;
			}

			ptr += names + 2;
		}

		printf("The closest hit names are ");
		ptr = ptrNames;
		for (j = 0; j < numberOfNames; j++, ptr++) {
			printf("%d ", *ptr);
		}
		printf("\n");

		assert(numberOfNames == 3);

	}
}
void View::Reshape(int w, int h)
{

	glViewport(0, 0, w, h);    //截图;1、2为视口的左下角;3、4为视口的宽度和高度
	glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);     //对模型视景矩阵堆栈应用随后的矩阵操作.
}
void View::Idle()
{
	glutPostRedisplay();
}
void View::Init(int argc, char* argv[])
{
	glutInit(&argc, argv);                                          //初始化glut库
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);      //设置初始显示模式
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("***************");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	setList();
	glutReshapeFunc(Reshape);       //
	glutDisplayFunc(Display);           //
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyBoardCallBackFunc);
	glutKeyboardUpFunc(KeyBoardUpCallBackFunc);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutMainLoop();//enters the GLUT event processing loop.
}
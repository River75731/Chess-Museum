#include "View.h"
#include "../Common/ObjParser.h"
#include "../Common/textfile.h"
#include "../ViewModel/ViewModel.h"
#include <vector>

#define MAX_FRAGMENT_NUM 100000

bool View::ButtonDown = false;
bool View::Move = false;
int View::du = 90, View::OriX = -1, View::OriY = -1;
float View::c = PI / 180.0;
Vec3f View::EyeLocation = Vec3f(0, 0, 0);
Vec3f View::EyeDirection = Vec3f(0, 0, -1);
Vec3f View::EyeUp = Vec3f(0, 1, 0);
Vec3f View::MoveIncrement = Vec3f(-1, 0, 0);
float View::Pitch = 0, View::Yaw = 270;
char View::Key = ' ';

std::map<std::string, ViewObjectType> View::objMap;
std::map<ViewObjectType, GLuint> View::listMap;
std::map<GLuint, unsigned int> View::VAOMap;

std::map<ViewObjectType, std::vector<int>> View::texMap;
std::string View::texturePath = "texture/";
unsigned int View::texture[TEXTURE_NUM] = {0};
std::string View::texFileNames[TEXTURE_NUM] =
	{
		"tex_marble_table.bmp",
		"pawn_white.bmp",
		"pawn_black.bmp",
		"rook_white.bmp",
		"rook_black.bmp",
		"knight_white.bmp",
		"knight_black.bmp",
		"bishop_white.bmp",
		"bishop_black.bmp",
		"queen_white.bmp",
		"queen_black.bmp",
		"king_white.bmp",
		"king_black.bmp"};

void View::initMapRelation()
{
	objMap["CIRCLE"] = CIRCLE;
	objMap["CONE"] = CONE;
	objMap["CUBE"] = CUBE;
	objMap["CYLINDER"] = CYLINDER;
	objMap["PRISM3"] = PRISM3;
	objMap["SPHERE"] = SPHERE;
	objMap["PAWN"] = PAWN;
	objMap["ROOK"] = ROOK;
	objMap["KNIGHT"] = KNIGHT;
	objMap["BISHOP"] = BISHOP;
	objMap["QUEEN"] = QUEEN;
	objMap["KING"] = KING;
	objMap["TABLE"] = TABLE;
	objMap["MARBLETABLE"] = MARBLETABLE;
	objMap["CHESSBOARD"] = CHESSBOARD;

	std::vector<int> tex;

	tex.emplace_back(texture[0]);
	texMap[MARBLETABLE] = tex;
	tex.clear();

	tex.emplace_back(texture[1]);
	tex.emplace_back(texture[2]);
	texMap[PAWN] = tex;
	tex.clear();

	tex.emplace_back(texture[3]);
	tex.emplace_back(texture[4]);
	texMap[ROOK] = tex;
	tex.clear();

	tex.emplace_back(texture[5]);
	tex.emplace_back(texture[6]);
	texMap[KNIGHT] = tex;
	tex.clear();

	tex.emplace_back(texture[7]);
	tex.emplace_back(texture[8]);
	texMap[BISHOP] = tex;
	tex.clear();

	tex.emplace_back(texture[9]);
	tex.emplace_back(texture[10]);
	texMap[QUEEN] = tex;
	tex.clear();

	tex.emplace_back(texture[11]);
	tex.emplace_back(texture[12]);
	texMap[KING] = tex;
	tex.clear();
}

void View::Rotate(float angle, Vec3f axis)
{
	glRotatef(angle, axis.x(), axis.y(), axis.z());
}

void View::Scale(Vec3f times)
{
	glScalef(times.x(), times.y(), times.z());
}

void View::Translate(Vec3f direction)
{
	glTranslatef(direction.x(), direction.y(), direction.z());
}

void View::setList()
{
	glNewList(CIRCLE, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	int i = 0;
	for (i = 0; i <= 360; i++)
	{
		float p = i * PI / 180;
		glNormal3f(0, 1, 0);
		glTexCoord2f(sin(p), cos(p));
		glVertex3f(sin(p), 0.0f, cos(p));
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(CONE, GL_COMPILE);
	glutSolidCone(1, 1, 32, 32);
	glEndList();

	glNewList(CUBE, GL_COMPILE);
	glutSolidCube(1);
	glEndList();

	glNewList(CYLINDER, GL_COMPILE);
	for (int i = 0; i < 360; i++)
	{
		float p = i * PI / 180;
		float q = (i + 1) * PI / 180;

		glBegin(GL_TRIANGLES);
		glNormal3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(sin(p), 0, cos(p));
		glVertex3f(sin(q), 0, cos(q));
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(sin(p), 1, cos(p));
		glVertex3f(sin(q), 1, cos(q));
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(sin(p), 0, cos(p));
		glVertex3f(sin(p), 0, cos(p));
		glNormal3f(sin(q), 0, cos(q));
		glVertex3f(sin(q), 0, cos(q));
		glNormal3f(sin(q), 0, cos(q));
		glVertex3f(sin(q), 1, cos(q));
		glNormal3f(sin(p), 0, cos(p));
		glVertex3f(sin(p), 1, cos(p));
		glEnd();
	}
	glEndList();

	glNewList(PRISM3, GL_COMPILE);
	for (int i = 0; i < 360; i += 120)
	{
		float p = i * PI / 180;
		float q = (i + 1) * PI / 180;

		glBegin(GL_TRIANGLES);
		glNormal3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(sin(p), 0, cos(p));
		glVertex3f(sin(q), 0, cos(q));
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(sin(p), 1, cos(p));
		glVertex3f(sin(q), 1, cos(q));
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(sin(p), 0, cos(p));
		glVertex3f(sin(p), 0, cos(p));
		glNormal3f(sin(q), 0, cos(q));
		glVertex3f(sin(q), 0, cos(q));
		glNormal3f(sin(q), 0, cos(q));
		glVertex3f(sin(q), 1, cos(q));
		glNormal3f(sin(p), 0, cos(p));
		glVertex3f(sin(p), 1, cos(p));
		glEnd();
	}
	glEndList();

	glNewList(SPHERE, GL_COMPILE);
	glutSolidSphere(1, 32, 32);
	glEndList();

	std::vector<TriangleMesh> tm = ObjParser::parseFile();
	for (std::vector<TriangleMesh>::iterator iter = tm.begin(); iter != tm.end(); iter++)
	{
		iter->setVAO();
		listMap[objMap[iter->getObjName()]] = iter->getListNum();
		VAOMap[iter->getListNum()] = iter->getF().size();
	}
}

void View::DrawModel(ViewObjectType type, Vec2f coordinate, Vec3f translate, float angle, Vec3f axis, Vec3f scale, int texIndex)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	Translate(Vec3f(coordinate.x(), coordinate.y(), 0));
	Translate(translate);
	Rotate(angle, axis);
	Scale(scale);

	glEnable(GL_TEXTURE_2D);
	if (texIndex != -1)
	{
		glBindTexture(GL_TEXTURE_2D, texMap[type][texIndex]);
	}
	else
		glBindTexture(GL_TEXTURE_2D, 0);

	switch (type)
	{
	CIRCLE:
	CONE:
	CUBE:
	CYLINDER:
	PRISM3:
	SPHERE:
		glCallList(type);
		break;
	default:
		glBindVertexArray(listMap[type]);
		glDrawElements(GL_TRIANGLES, VAOMap[listMap[type]] * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		glBindVertexArray(0);
		break;
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void View::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	SetEyeLocation();
	if (Move)
		EyeMove();
	glEnable(GL_LIGHTING);
	GLfloat gray[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat light_pos[] = {10, 10, 10, 0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(10000, 0, 0);
	glVertex3f(-10000, 0, 0);
	glVertex3f(0, 10000, 0);
	glVertex3f(-0, -10000, 0);
	glVertex3f(0, 0, 10000);
	glVertex3f(-0, 0, -10000);
	glEnd();

	DrawModel(PAWN, Vec2f(), Vec3f(0, 0, 0), 0, Vec3f(0, 1, 0), Vec3f(0.01, 0.01, 0.01), -1);
	DrawModel(PAWN, Vec2f(), Vec3f(0.1, 0, 0), 0, Vec3f(0, 1, 0), Vec3f(0.01, 0.01, 0.01), 0);
	DrawModel(PAWN, Vec2f(), Vec3f(-0.1, 0, 0), 0, Vec3f(0, 1, 0), Vec3f(0.01, 0.01, 0.01), 1);

	glutSwapBuffers();
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
		EyeLocation += 0.001 * EyeDirection;
		break;
	case 's':
		EyeLocation -= 0.001 * EyeDirection;
		break;
	case 'a':
		EyeLocation += 0.001 * MoveIncrement;
		break;
	case 'd':
		EyeLocation -= 0.001 * MoveIncrement;
		break;
	case 'z':
		EyeLocation -= 0.001 * EyeUp;
		break;
	case 'c':
		EyeLocation += 0.001 * EyeUp;
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
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

		for (i = 0; i < hits; i++)
		{
			names = *ptr;
			ptr++;

			if (*ptr < minZ)
			{
				numberOfNames = names;
				minZ = *ptr;
				ptrNames = ptr + 2;
			}

			ptr += names + 2;
		}

		printf("The closest hit names are ");
		ptr = ptrNames;
		for (j = 0; j < numberOfNames; j++, ptr++)
		{
			printf("%d ", *ptr);
		}
		printf("\n");

		assert(numberOfNames == 3);
	}
}

void View::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 0.01, 100000.0);
	glMatrixMode(GL_MODELVIEW);
}

void View::Idle()
{
	glutPostRedisplay();
}

void View::Init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("***************");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		cout << "glewInit failed, aborting." << endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	initTexture();
	initMapRelation();
	loadShader();
	setList();

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyBoardCallBackFunc);
	glutKeyboardUpFunc(KeyBoardUpCallBackFunc);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);

	glutMainLoop();
}

unsigned char *View::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;
	BITMAPFILEHEADER bitmapFileHeader;
	unsigned char *bitmapImage;
	int imageIdx = 0;
	unsigned char temp;

	fopen_s(&filePtr, filename, "rb");
	if (filePtr == NULL)
		return NULL;
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	if (!bitmapImage)
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	if (bitmapImage == NULL)
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// // Reverse
	// int size = bitmapInfoHeader->biSizeImage;
	// for (imageIdx = 0; imageIdx <= size / 2; imageIdx++)
	// {
	// 	temp = bitmapImage[imageIdx];
	// 	bitmapImage[imageIdx] = bitmapImage[size - imageIdx - 1];
	// 	bitmapImage[size - imageIdx - 1] = temp;
	// }

	fclose(filePtr);
	return bitmapImage;
}

void View::texload(int i, std::string filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char *bitmapData;
	char c_filename[BUFSIZE];
	strcpy(c_filename, (texturePath + filename).c_str());

	bitmapData = LoadBitmapFile(c_filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bitmapInfoHeader.biWidth,
				 bitmapInfoHeader.biHeight,
				 0,
				 GL_BGR,
				 GL_UNSIGNED_BYTE,
				 bitmapData);
}

void View::initTexture()
{
	glGenTextures(TEXTURE_NUM, texture);
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		texload(i, texFileNames[i]);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void View::loadShader()
{
	char vfilename[] = "shader/v.vert";
	char ffilename[] = "shader/f.frag";
	GLuint v, f, p;
	char *vs = NULL, *fs = NULL;
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	vs = textFileRead(vfilename);
	fs = textFileRead(ffilename);
	const char *vv = vs;
	const char *ff = fs;
	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
	free(vs);
	free(fs);
	glCompileShader(v);
	glCompileShader(f);
	p = glCreateProgram();
	glAttachShader(p, v);
	glAttachShader(p, f);
	glLinkProgram(p);
	glUseProgram(p);

	GLint length;
	GLsizei num;
	char *log;
	glGetShaderiv(v, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char *) malloc(sizeof(char) * length);
		glGetShaderInfoLog(v, length, &num, log);
		std::cout << "Vertex shader compile log:" << std::endl << log << std::endl << std::endl << std::endl;
	}
	glGetShaderiv(f, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char *) malloc(sizeof(char) * length);
		glGetShaderInfoLog(f, length, &num, log);
		std::cout << "Fragment shader compile log:" << std::endl << log << std::endl << std::endl << std::endl;
	}
}

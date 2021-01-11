#include "View.h"
#include "../Common/ObjParser.h"
#include "../Common/textfile.h"
#include "../ViewModel/ViewModel.h"
#include <vector>
#include <iostream>
#define HEIGHT 0.8
bool View::ButtonDown = false;
bool View::Move = false;
int View::du = 90, View::OriX = -1, View::OriY = -1;
float View::c = PI / 180.0; 
Vec3f View::EyeLocation = Vec3f(0, 0, 2);
Vec3f View::EyeDirection = Vec3f(-1.99999,0.0069813,0.0);
Vec3f View::EyeUp = Vec3f(0, 1, 0);
Vec3f View::MoveIncrement = Vec3f(0.00174537,0,0.999998);
Vec3f View::EyeDirection_t = Vec3f(-1.99999, 0.0069813, 0.0);
float View::Pitch = 0, View::Yaw = 180; 
char View::Key = ' ';
Position2i View::CurrentPosition = Position2i(1, 1);
GLuint program;

ViewSceneType View::CurrentState = SCENE;
Model View::MyModel = Model();
std::map<std::string, ViewObjectType> View::objMap;
std::map<ViewObjectType, GLuint> View::listMap;
std::map<GLuint, unsigned int> View::VAOMap;

std::map<ViewObjectType, std::vector<int>> View::texMap;
std::map<ExhibitType, ViewObjectType> IndexMap;
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
		"king_black.bmp",
		"chess_board.bmp",
		"floor.bmp",
		"wall.bmp",
		"wood_brown.bmp",
		"ceiling.bmp"};

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

	IndexMap[EXHIBIT_EMPTY] = IndexMap[EXHIBIT_CHESS_SET]= IndexMap[EXHIBIT_WINDOW]= IndexMap[EXHIBIT_DOOR]=EMPTY;

	IndexMap[EXHIBIT_PAWN] = PAWN;
	IndexMap[EXHIBIT_ROOK] = ROOK;
	IndexMap[EXHIBIT_KNIGHT] = KNIGHT;
	IndexMap[EXHIBIT_BISHOP] = BISHOP;
	IndexMap[EXHIBIT_QUEEN] = QUEEN;
	IndexMap[EXHIBIT_KING] = KING;

	tex.emplace_back(texture[0]);
	texMap[MARBLETABLE] = tex;
	tex.clear();

	tex.emplace_back(texture[13]);
	texMap[CHESSBOARD] = tex;
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

	tex.emplace_back(texture[14]);
	tex.emplace_back(texture[15]);
	tex.emplace_back(texture[16]);
	tex.emplace_back(texture[17]);
	texMap[CUBE] = tex;
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

	GLfloat vertexes[] = {
		0.5f, 0.0f, 0.5f, 1.0f,
		0.5f, 0.0f, -0.5f, 1.0f,
		-0.5f, 0.0f, -0.5f, 1.0f,
		-0.5f, 0.0f, 0.5f, 1.0f,
		0.5f, 1.0f, 0.5f, 1.0f,
		0.5f, 1.0f, -0.5f, 1.0f,
		-0.5f, 1.0f, -0.5f, 1.0f,
		-0.5f, 1.0f, 0.5f, 1.0f};
	GLfloat normals[] = {
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f};
	GLfloat texCoordes[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f};
	glNewList(CUBE, GL_COMPILE);
	glBegin(GL_QUADS);

	glNormal3fv(normals + 0 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 0 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 3 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 2 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 1 * 4);

	glNormal3fv(normals + 1 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 0 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 1 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 5 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 4 * 4);

	glNormal3fv(normals + 2 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 2 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 3 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 7 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 6 * 4);

	glNormal3fv(normals + 3 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 0 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 4 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 7 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 3 * 4);

	glNormal3fv(normals + 4 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 1 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 2 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 6 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 5 * 4);

	glNormal3fv(normals + 5 * 3);
	glTexCoord2fv(texCoordes + 0 * 2);
	glVertex4fv(vertexes + 4 * 4);
	glTexCoord2fv(texCoordes + 1 * 2);
	glVertex4fv(vertexes + 5 * 4);
	glTexCoord2fv(texCoordes + 2 * 2);
	glVertex4fv(vertexes + 6 * 4);
	glTexCoord2fv(texCoordes + 3 * 2);
	glVertex4fv(vertexes + 7 * 4);
	glEnd();
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

	Translate(Vec3f(coordinate.x(), 0, coordinate.y()));
	Translate(translate);
	Rotate(angle, axis);
	Scale(scale);

	glEnable(GL_TEXTURE_2D);
	if (texIndex != -1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texMap[type][texIndex]);
	}
	else
		glBindTexture(GL_TEXTURE_2D, 0);

	switch (type)
	{
	case CIRCLE:
	case CONE:
	case CUBE:
	case CYLINDER:
	case PRISM3:
	case SPHERE:
		glUseProgram(0);
		glCallList(type);
		break;
	default:
		glUseProgram(program);
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
	GLfloat gray[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat light_pos[] = {-6.5, 4,- 6.5, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	DrawModel(CUBE, Vec2f(), Vec3f(-6.5, 4, -6.5), 0, Vec3f(0, 1, 0), Vec3f(0.1, 0.1, 0.1), -1);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(10000, 0, 0);
	glVertex3f(-10000, 0, 0);
	glVertex3f(0, 10000, 0);
	glVertex3f(-0, -10000, 0);
	glVertex3f(0, 0, 10000);
	glVertex3f(-0, 0, -10000);
	glEnd();

	
	DrawScene();
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
		EyeDirection.Set(2.0 * cos(c * Yaw) * cos(c * Pitch), 2.0 * sin(c * Pitch), 2.0 * sin(c * Yaw) * cos(c * Pitch));
		EyeUp.Set(1.0 * cos(c * Yaw) * cos(c * (Pitch + 90.0)), 1.0 * sin(c * (Pitch + 90.0)), 1.0 * sin(c * Yaw) * cos(c * (Pitch + 90.0)));
		
		EyeDirection_t.Set(1.0 * cos(c * Yaw), 0, 1.0 * sin(c * Yaw));
		MoveIncrement. Set(1.0 * sin(c * Yaw), 0, -1.0 * cos(c * Yaw));
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
	Exhibit temp;
	ViewObjectType T;
	switch (k)
	{
	case 'e':
	case 'E':
		CurrentState = EDIT;
		Reshape(600, 600);
		break;
	case 'r':
	case 'R':
		CurrentState = SCENE;
		Reshape(600, 600);
		break;
	case 'm':
	case 'M':
		CurrentState = CHESS;
		break;
	case (char)(0xD) :
		if (CurrentState == EDIT)
		{
			CurrentState = EXHIBIT;
			MyModel.chooseBlock(CurrentPosition);
			MyModel.editExhibit();
		}
		break;
	case 't':
		MyModel.changeType();
		MyModel.saveExhibit();
		MyModel.editExhibit();
		break;
	case ' ':
		if (CurrentState == EXHIBIT)
		{
			CurrentState = EDIT;
			MyModel.saveExhibit();
		}
		break;
	case 'q':
		MyModel.getExhibit(Position2i(CurrentPosition), temp);
		 T = IndexMap[temp.getType()];
		if (T != EMPTY)
		{
			int Size = texMap[T].size();
			int currentnum = temp.getTextureNum();
			MyModel.setTextureNum(currentnum + 1 >= Size ? 0 : ++currentnum);
			MyModel.saveExhibit();
			MyModel.editExhibit();
		}
		break;
	case 'f':
		MyModel.execRotate(1, true);
		MyModel.saveExhibit();
		MyModel.editExhibit();
		break;
	case 'g':
		MyModel.execScale(1, true);
		MyModel.saveExhibit();
		MyModel.editExhibit();
		break;

	default:
		Move = true;
		break;

	}
	if(CurrentState == EDIT|| CurrentState == EXHIBIT)
	PoisitionChange();
	
}

void View::KeyBoardUpCallBackFunc(unsigned char k, int x, int y)
{
	Move = false;
}

void View::EyeMove()
{


	Vec3f temp_vec = EyeLocation;
	
		switch (Key)
		{
		float temp[3];
		case 'w':
			temp_vec += 0.05 * EyeDirection_t;
			temp_vec.Get(temp[0], temp[1], temp[2]);	
			
			if (MyModel.canEnter(Position2i((int)(-temp[0]+0.5),(int)(-temp[2]+0.5)))||CurrentState==EDIT|| CurrentState == EXHIBIT)
			{
				EyeLocation += 0.01 * EyeDirection_t;
			}
			break;
		case 's':
			temp_vec -= 0.05 * EyeDirection_t;
			temp_vec.Get(temp[0], temp[1], temp[2]);

			if (MyModel.canEnter(Position2i((int)(-temp[0] + 0.5), (int)(-temp[2] + 0.5))) || CurrentState == EDIT || CurrentState == EXHIBIT)
			EyeLocation -= 0.01 * EyeDirection_t;
			break;
		case 'a':
			temp_vec += 0.05 * MoveIncrement;
			temp_vec.Get(temp[0], temp[1], temp[2]);

			if (MyModel.canEnter(Position2i((int)(-temp[0] + 0.5), (int)(-temp[2] + 0.5))) || CurrentState == EDIT || CurrentState == EXHIBIT)
			EyeLocation += 0.01 * MoveIncrement;
			break;
		case 'd':
			temp_vec -= 0.05 * MoveIncrement;
			temp_vec.Get(temp[0], temp[1], temp[2]);

			if (MyModel.canEnter(Position2i((int)(-temp[0] + 0.5), (int)(-temp[2] + 0.5))) || CurrentState == EDIT || CurrentState == EXHIBIT)
			EyeLocation -= 0.01 * MoveIncrement;
			break;
		case 'z':

			EyeLocation -= 0.01 * EyeUp;
			break;
		case 'c':
			EyeLocation += 0.01 * EyeUp;
			break;
		case 'q':
			exit(0);
			break;
		default:
			break;
		}
	
}

void View::PoisitionChange()
{
	switch (Key)
	{
	case 'i':
		if (CurrentPosition.getX() < 11)
		{
			
			if (CurrentState == EXHIBIT)
			{
				if (MyModel.moveExhibit(CurrentPosition, CurrentPosition + Vector2i(1, 0)))
					CurrentPosition = CurrentPosition + Vector2i(1, 0);
			}
			else
			{
					CurrentPosition = CurrentPosition + Vector2i(1, 0);
			}

		}
		break;
	case 'j':
		if (CurrentPosition.getY() > 1)
		{
			if (CurrentState == EXHIBIT)
			{
				if (MyModel.moveExhibit(CurrentPosition, CurrentPosition - Vector2i(0, 1)))
					CurrentPosition = CurrentPosition - Vector2i(0, 1);
			}
			else
			{
				CurrentPosition = CurrentPosition - Vector2i(0, 1);
			}
		}
		break;
	case'k':
		if (CurrentPosition.getX() > 1)
		{
			if (CurrentState == EXHIBIT)
			{
				if (MyModel.moveExhibit(CurrentPosition, CurrentPosition - Vector2i(1, 0)))
					CurrentPosition = CurrentPosition - Vector2i(1, 0);
			}
			else
			{
				CurrentPosition = CurrentPosition - Vector2i(1, 0);
			}
		}
			break;
	case 'l':
		if (CurrentPosition.getY() < 13)
		{
			if (CurrentState == EXHIBIT)
			{
				if (MyModel.moveExhibit(CurrentPosition, CurrentPosition + Vector2i(0, 1)))
					CurrentPosition = CurrentPosition + Vector2i(0, 1);
			}
			else
			{
				CurrentPosition = CurrentPosition + Vector2i(0, 1);
			}
		}
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
	if (CurrentState == SCENE)
	{
		EyeLocation = Vec3f(0, 0, -2);
		EyeDirection = Vec3f(-1.99999, 0.0069813, 0.0);
		EyeUp = Vec3f(0, 1, 0);
	}
	else if (CurrentState == EDIT)
	{
		EyeLocation = Vec3f(-5, 4, 0);
		EyeDirection = Vec3f(-1.77385,- 0.923499,0.024773);
		EyeUp = Vec3f(-0.379386,0.92521,- 0.00728536);
	}
	gluPerspective(90.0, (float)w / h, 0.01, 100000.0);
	
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

void View::DrawScene()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawGround();
	if (CurrentState == EDIT|| CurrentState==EXHIBIT)
	{
		DrawEdit();
		
		MyModel.enterEdit();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			Exhibit temp = Exhibit();
			MyModel.getExhibit(Position2i(i, j), temp);
			switch (temp.getType())
			{
			case  EXHIBIT_EMPTY:

				break;
			case  EXHIBIT_CHESS_SET:

				break;
			case EXHIBIT_CUBE:
				DrawModel(CUBE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()) , temp.getTextureNum());
				break;
			case EXHIBIT_DOOR:


				break;
			case EXHIBIT_WINDOW:

				break;

			case EXHIBIT_PAWN:
				DrawModel(PAWN, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()), temp.getTextureNum());
				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()),0);

				break;
			case EXHIBIT_ROOK:
				DrawModel(ROOK, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY() , temp.getScale().getZ()), temp.getTextureNum());
				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()), 0);
				break;
			case EXHIBIT_KNIGHT:
				DrawModel(KNIGHT, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY() , temp.getScale().getZ()), temp.getTextureNum());
				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()),0);

				break;
			case EXHIBIT_BISHOP:
				DrawModel(BISHOP, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY() , temp.getScale().getZ()), temp.getTextureNum());

				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()), 0);
				break;

			case EXHIBIT_QUEEN:
				DrawModel(QUEEN, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY() , temp.getScale().getZ()), temp.getTextureNum());
				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()), 0);

				break;
			case EXHIBIT_KING:
				DrawModel(KING, Vec2f(-i, -j), Vec3f(0, HEIGHT, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY() , temp.getScale().getZ()), temp.getTextureNum());
				DrawModel(MARBLETABLE, Vec2f(-i, -j), Vec3f(0, 0, 0), temp.getRotate(), Vec3f(0, 1, 0), Vec3f(temp.getScale().getX(), temp.getScale().getY(), temp.getScale().getZ()),0);
				break;
			}
		}
	}
}
void View::DrawGround()
{
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 13; j++)
		{	if(Position2i(i,j)!=CurrentPosition)
			DrawModel(CUBE, Vec2f(-i, -j), Vec3f(0, 0, 0),0, Vec3f(0, 1, 0), Vec3f(1,0.01,1),0);

			DrawModel(CUBE, Vec2f(-i, -j), Vec3f(0, 5, 0), 0, Vec3f(0, 1, 0), Vec3f(1, 0.01, 1), 3);
		}
	}
}
void View::DrawEdit()
{
	for (int i = 0; i <= 11; i++)
	{
			glLineWidth(2);
			glBegin(GL_LINES);
			glVertex3f(-i-0.5, 0, -0.5);
			glVertex3f(-i-0.5, 0, -10.5);
			glEnd();	
	}
	for (int i = 0; i <= 13; i++)
	{
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(-0.5, 0, -i-0.5);
		glVertex3f(-20.5, 0, -i-0.5);
		glEnd();
	}
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
	program = p;

	GLint length;
	GLsizei num;
	char *log;
	glGetShaderiv(v, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char *)malloc(sizeof(char) * length);
		glGetShaderInfoLog(v, length, &num, log);
		std::cout << "Vertex shader compile log:" << std::endl
				  << log << std::endl
				  << std::endl
				  << std::endl;
	}
	glGetShaderiv(f, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char *)malloc(sizeof(char) * length);
		glGetShaderInfoLog(f, length, &num, log);
		std::cout << "Fragment shader compile log:" << std::endl
				  << log << std::endl
				  << std::endl
				  << std::endl;
	}
}

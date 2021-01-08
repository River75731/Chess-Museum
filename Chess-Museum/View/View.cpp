#include "View.h"
#include "../Common/ObjParser.h"
#include "ViewModel.h"
#include <vector>

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
		glVertex3f(sin(p), 0.0f, cos(p));
	}
	glEnd();
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

	/* Set list for all .obj groups */
	std::map<std::string, ViewObjectType> objMap;
	objMap["PAWN"] = PAWN;
	objMap["ROOK"] = ROOK;
	objMap["KNIGHT"] = KNIGHT;
	objMap["BISHOP"] = BISHOP;
	objMap["QUEEN"] = QUEEN;
	objMap["KING"] = KING;

	std::vector<TriangleMesh> tm = ObjParser::parseFile();
	for (std::vector<TriangleMesh>::iterator iter = tm.begin(); iter != tm.end(); iter++)
	{
		glNewList(objMap[iter->getObjName()], GL_COMPILE);
		for (std::vector<Triangle>::const_iterator iter1 = iter->getTriangles().begin(); iter1 != iter->getTriangles().end(); iter1++)
		{
			iter1->draw();
		}
		glEndList();
	}
}

void View::DrawModel(GLuint listN, Vec2f coordinate, Vec3f translate, float angle, Vec3f axis, Vec3f scale)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	Translate(Vec3f(coordinate.x(), coordinate.y(), 0));
	Translate(translate);
	Rotate(angle, axis);
	Scale(scale);

	glCallList(listN);

	glPopMatrix();
}
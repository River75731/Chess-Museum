#include "View.h"

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

void View::DrawModel(ViewObjectType Type, Vec3f direction, float angle, Vec3f axis, Vec3f times)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	Translate(direction);
	Rotate(angle, axis);
	Scale(times);

	switch (Type)
	{
	case Circle:
		glCallList(Circle);
		break;
	case Cone:
		glCallList(Cone);
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
	case Triangle:

		break;

	default:
		break;
	}
	glPopMatrix();
}
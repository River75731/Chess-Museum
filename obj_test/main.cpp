#include "matrix.h"
#include "triangle.h"
#include <iostream>
#include <string>

#define SCALE 100.0

using namespace std;

Vec3f center(0.0, 0.0, SCALE * 100);
Vec3f direction(0.0, 0.0, -1.0);
Vec3f up(0.0, 1.0, 0.0);
int mouseButton, mouseX, mouseY;
float angle_radians = 0.2;

TriangleMesh *tm;

void dollyCamera(float dist)
{
    center += direction * dist;
}

void rotateCamera(float rx, float ry)
{
    Vec3f horizontal;
    Vec3f::Cross3(horizontal, direction, up);
    horizontal.Normalize();
    // Don't let the model flip upside-down (There is a singularity
    // at the poles when 'up' and 'direction' are aligned)
    float tiltAngle = acos(up.Dot3(direction));
    if (tiltAngle - ry > 3.13)
        ry = tiltAngle - 3.13;
    else if (tiltAngle - ry < 0.01)
        ry = tiltAngle - 0.01;
    Matrix rotMat = Matrix::MakeAxisRotation(up, rx);
    rotMat *= Matrix::MakeAxisRotation(horizontal, ry);
    rotMat.Transform(center);
    rotMat.TransformDirection(direction);
    direction.Normalize();
}

void truckCamera(float dx, float dy)
{
    Vec3f horizontal;
    Vec3f::Cross3(horizontal, direction, up);
    horizontal.Normalize();
    Vec3f screenUp;
    Vec3f::Cross3(screenUp, horizontal, direction);
    center += horizontal * dx + screenUp * dy;
}

void mouse(int button, int state, int x, int y)
{
    // Save the current state of the mouse.  This will be
    // used by the 'motion' function
    mouseButton = button;
    mouseX = x;
    mouseY = y;
}

void motion(int x, int y)
{
    // Left button = rotation
    // (rotate camera around the up and horizontal vectors)
    if (mouseButton == GLUT_LEFT_BUTTON)
    {
        rotateCamera((mouseX - x) * 0.005, (mouseY - y) * 0.005);
        mouseX = x;
        mouseY = y;
    }
    // Middle button = translation
    // (move camera perpendicular to the direction vector)
    else if (mouseButton == GLUT_MIDDLE_BUTTON)
    {
        truckCamera((mouseX - x) * SCALE / 10, (y - mouseY) * SCALE / 10);
        mouseX = x;
        mouseY = y;
    }
    // Right button = zoom
    // (move camera along the direction vector)
    else if (mouseButton == GLUT_RIGHT_BUTTON)
    {
        dollyCamera((x - mouseX) * SCALE);
        mouseX = x;
        mouseY = y;
    }

    // Redraw the scene with the new camera parameters
    glutPostRedisplay();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(center.x(), center.y(), center.z(), center.x() + direction.x(), center.y() + direction.y(), center.z() + direction.z(), up.x(), up.y(), up.z());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat grey[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat gold[] = {0.9, 0.9, 0.0, 1.0};
    GLfloat light_pos[] = {10, 10, 10, 0.0};
    GLfloat shiness[] = {50.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, gold);
    glLightfv(GL_LIGHT0, GL_SHININESS, shiness);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiness);

    tm->draw();
    // glutSolidSphere(10.0, 32, 32);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // Set the OpenGL viewport to fill the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Set the camera parameters to reflect the changes
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle_radians * 180.0 / 3.14159, (float)w / float(h), 0.5, SCALE * 300);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
        exit(0);
        break;
    default:
        printf("UNKNOWN KEYBOARD INPUT  '%c'\n", key);
    }
}

int main(int argc, char *argv[])
{
    string filename("deer.obj");
    tm = new TriangleMesh(filename);
    cout << "TriangleMesh establish success" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("OBJ DEMO");

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
#include "matrix.h"
#include "triangle.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#define SCALE 100.0

using namespace std;

Vec3f center(0.0, 0.0, SCALE * 100);
Vec3f direction(0.0, 0.0, -1.0);
Vec3f up(0.0, 1.0, 0.0);
int mouseButton, mouseX, mouseY;
float angle_radians = 0.2;

std::vector<TriangleMesh> tm;

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

bool writeBMP(const char filename[], unsigned char *data, unsigned int w, unsigned int h)
{
    std::ofstream out_file;

    /** 检查data */
    if (!data)
    {
        std::cerr << "data corrupted! " << std::endl;
        out_file.close();
        return false;
    }

    /** 创建位图文件信息和位图文件头结构 */
    BITMAPFILEHEADER header;
    BITMAPINFOHEADER bitmapInfoHeader;

    unsigned char textureColors = 0; /**< 用于将图像颜色从BGR变换到RGB */

    /** 打开文件,并检查错误 */
    out_file.open(filename, std::ios::out | std::ios::binary);
    if (!out_file)
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }

    /** 填充BITMAPFILEHEADER */
    header.bfType = (WORD)0x4d42; // 3;// BITMAP_ID;
    header.bfSize = w * h * 3 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    /** 写入位图文件头信息 */
    out_file.write((char *)&header, sizeof(BITMAPFILEHEADER));

    /** 填充BITMAPINFOHEADER */
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = w;
    bitmapInfoHeader.biHeight = h;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 24;
    bitmapInfoHeader.biCompression = BI_RGB;  // BI_RLE4 BI_RLE8
    bitmapInfoHeader.biSizeImage = w * h * 3; // 当压缩类型为BI_RGB是也可以设置为0
    bitmapInfoHeader.biXPelsPerMeter = 0;
    bitmapInfoHeader.biYPelsPerMeter = 0;
    bitmapInfoHeader.biClrUsed = 0;
    bitmapInfoHeader.biClrImportant = 0;
    /** 写入位图文件信息 */
    out_file.write((char *)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

    /** 将指针移到数据开始位置 */
    out_file.seekp(header.bfOffBits, std::ios::beg);

    /** 写入图像数据 */
    out_file.write((char *)data, bitmapInfoHeader.biSizeImage);

    out_file.close();
    return true;
}
void saveDisPlayResToBmp(const char filename[])
{
    GLbyte *pBits = 0; // data
    static FILE *fp = NULL;
    GLenum lastBuffer;

    unsigned long lImageSize;
    GLint iViewport[4]; // view

    glGetIntegerv(GL_VIEWPORT, iViewport);
    lImageSize = iViewport[2] * iViewport[3] * 3;

    pBits = (GLbyte *)new unsigned char[lImageSize];
    if (!pBits)
        return;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

    glGetIntegerv(GL_READ_BUFFER, (GLint *)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, iViewport[2], iViewport[3], GL_BGR_EXT, GL_UNSIGNED_BYTE, pBits);
    glReadBuffer(lastBuffer);

    writeBMP(filename, (unsigned char *)pBits, iViewport[2], iViewport[3]);
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

    for (std::vector<TriangleMesh>::iterator iter = tm.begin(); iter != tm.end(); iter++)
    {
        iter->draw();
    }
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
    case ' ':
        saveDisPlayResToBmp("./prtsc/test.bmp");
        break;
    default:
        printf("UNKNOWN KEYBOARD INPUT  '%c'\n", key);
    }
}

int main(int argc, char *argv[])
{
    string filename(argv[1]);
    // std::vector<TriangleMesh> t = TriangleMesh::parseFile(filename);
    tm = TriangleMesh::parseFile(filename);
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
    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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
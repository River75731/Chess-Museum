#include "light.h"

bool View::ifMainLight = false;
bool View::ifDirectionLight = false;
bool View::ifSpotLight = false;

void View::mainSwitch()
{
	ifMainLight = !ifMainLight;
	if (ifMainLight)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
}
void View::directionSwitch()
{
	ifDirectionLight = !ifDirectionLight;
	if (ifDirectionLight)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
}
void View::spotSwitch()
{
	ifSpotLight = !ifSpotLight;
	if (ifSpotLight)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}
}
void View::initLight()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };	//设置漫射光成分
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	//设置镜面光成分

	//点光源（大灯）
	GLfloat MainLightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat MainLightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, MainLightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, MainLightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);

	//平行光
	GLfloat DirectionLightPos[] = { 0.0f, 0.0f, 10.0f, 0.0f };
	GLfloat DirectionLightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, DirectionLightPos);	//光源方向
	glLightfv(GL_LIGHT1, GL_AMBIENT, DirectionLightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);

	//聚光灯
	GLfloat SpotLightPos[] = { 0.0f, 30.0f, 0.0f, 1.0f };
	GLfloat SpotLightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpotLightDir[] = { 0.0f, -10.0f, 0.0f, 1.0f };
	GLfloat SpotLightAngle = 30.0f;
	glLightfv(GL_LIGHT2, GL_POSITION, SpotLightPos);
	glLightfv(GL_LIGHT2, GL_AMBIENT, SpotLightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotLightDir);	//光源方向
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, SpotLightAngle);	//裁减角度
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30);
}
void View::mainPos(Vec3f pos)
{
	GLfloat MainLightPos[] = { pos.x(), pos.y(), pos.z(), 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, MainLightPos);
}
void View::directionPos(Vec3f pos)
{
	GLfloat DirectionLightPos[] = { pos.x(), pos.y(), pos.z(), 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, DirectionLightPos);
}
void View::spotPos(Vec3f pos)
{
	GLfloat SpotLightPos[] = { pos.x(), pos.y(), pos.z(), 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, SpotLightPos);
}
void View::spotDir(Vec3f dir)
{
	GLfloat SpotLightDir[] = { dir.x(), dir.y(), dir.z(), 1.0f };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotLightDir);
}
void View::mainColor(Vec3f col)
{
	GLfloat MainLightAmbient[] = { col.x(), col.y(), col.z(), 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, MainLightAmbient);
}
void View::directionColor(Vec3f col)
{
	GLfloat DirectionLightAmbient[] = { col.x(), col.y(), col.z(), 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, DirectionLightAmbient);
}
void View::spotColor(Vec3f col)
{
	GLfloat SpotLightAmbient[] = { col.x(), col.y(), col.z(), 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, SpotLightAmbient);
}
void View::mater(Vec3f ambient, Vec3f diffuse, Vec3f specular, Vec3f emission, float shininess)
{
	GLfloat matAmbient[] = { ambient.x(), ambient.y(), ambient.z(), 1.0f };  //定义材质的环境光颜色
	GLfloat matDiffuse[] = { diffuse.x(), diffuse.y(), diffuse.z(), 1.0f };  //定义材质的漫反射光颜色
	GLfloat matSpecular[] = { specular.x(), specular.y(), specular.z(), 1.0f };   //定义材质的镜面反射光颜色
	GLfloat matEmission[] = { emission.x(), emission.y(), emission.z(), 1.0f };   //定义材质的辐射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


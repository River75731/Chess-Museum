#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#include "gl/glut.h"
class View
{
public:
	static void initLight();	//第一次打开光照前需要初始化
	static void mainSwitch();	//点光源（大灯）开关
	static void directionSwitch();	//平行光开关
	static void spotSwitch();	//聚光灯开关
	static void mainPos(Vec3f pos);	//改变点光源位置
	static void directionPos(Vec3f pos);	//改变平行光位置（方向）
	static void spotPos(Vec3f pos);	//改变聚光灯位置
	static void spotDir(Vec3f dir);	//改变聚光灯照射方向
	static void mainColor(Vec3f col);	//改变点光源颜色
	static void directionColor(Vec3f col);	//改变平行光颜色
	static void spotColor(Vec3f col);	//改变聚光灯颜色
	static void mater(Vec3f ambient, Vec3f diffuse, Vec3f specular, Vec3f emission, float shininess);
	//改变材质，参数分别为材质的环境光颜色、漫反射颜色、镜面反射颜色、幅射光颜色（实际颜色）、光泽度（0-128）
	static bool ifMainLight;	//开关状态
	static bool ifDirectionLight;
	static bool ifSpotLight;
};
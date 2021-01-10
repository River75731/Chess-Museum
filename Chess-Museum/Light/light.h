#pragma once
#include "../Common/MathBase.h"
#include "../Common/vectors.h"
#include "gl/glut.h"
class View
{
public:
	static void initLight();	//��һ�δ򿪹���ǰ��Ҫ��ʼ��
	static void mainSwitch();	//���Դ����ƣ�����
	static void directionSwitch();	//ƽ�й⿪��
	static void spotSwitch();	//�۹�ƿ���
	static void mainPos(Vec3f pos);	//�ı���Դλ��
	static void directionPos(Vec3f pos);	//�ı�ƽ�й�λ�ã�����
	static void spotPos(Vec3f pos);	//�ı�۹��λ��
	static void spotDir(Vec3f dir);	//�ı�۹�����䷽��
	static void mainColor(Vec3f col);	//�ı���Դ��ɫ
	static void directionColor(Vec3f col);	//�ı�ƽ�й���ɫ
	static void spotColor(Vec3f col);	//�ı�۹����ɫ
	static void mater(Vec3f ambient, Vec3f diffuse, Vec3f specular, Vec3f emission, float shininess);
	//�ı���ʣ������ֱ�Ϊ���ʵĻ�������ɫ����������ɫ�����淴����ɫ���������ɫ��ʵ����ɫ��������ȣ�0-128��
	static bool ifMainLight;	//����״̬
	static bool ifDirectionLight;
	static bool ifSpotLight;
};
#pragma once

#include <graphics.h>

const int NUM_OF_BALLS = 40;//�������
const int intime = 300;//�޵�ʱ��
const double dv = 0.1;//ÿһ�ε��ٶ�����

struct ball{
	double r;//��İ뾶
	double x;//����λ��x����
	double y;//����λ��y����
	double vx;//ˮƽ�ٶ�
	double vy;//��ֱ�ٶ�
	int time;//�޵�ʱ��
	long eatball;//������
	long eatbean;//�Զ�����
	COLORREF color;//�����ɫ
};

extern ball balls[NUM_OF_BALLS];

void ballDraw();
void ballUpdate();
void ballInit();
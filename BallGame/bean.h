#pragma once

#include <graphics.h>

const int NUM_OF_BEANS = 2000;//���ӵ�����
const int retime = 1000;//���ӵ�����ʱ��

struct bean{
	double r;//���ӵİ뾶
	double x;//����λ��x����
	double y;//����λ��y����
	int time;//��������ʱ��
	COLORREF color;//���ӵ���ɫ
};

extern bean beans[NUM_OF_BEANS];

void ReCreate(int);

void beanDraw();
void beanInit();
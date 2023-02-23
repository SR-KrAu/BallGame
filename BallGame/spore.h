#pragma once

#include <graphics.h>

const int NUM_OF_SPORES = 1000;//���ӵ��������

struct spore{
	int exist;//�����Ƿ����,����Ϊ1��������Ϊ0
	double x;//����λ��x����
	double y;//����λ��y����
	double vx;//ˮƽ�ٶ�
	double vy;//��ֱ�ٶ�
	double v;//���ٶ�
	double sintheta;//�ٶȷ���Ƕ�
	COLORREF color;//���ӵ���ɫ
};

extern spore spores[NUM_OF_SPORES];

void sporeDraw();
void sporeUpdate();
void sporeInit();
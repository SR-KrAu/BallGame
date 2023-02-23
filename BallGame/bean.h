#pragma once

#include <graphics.h>

const int NUM_OF_BEANS = 2000;//豆子的总数
const int retime = 1000;//豆子的重生时间

struct bean{
	double r;//豆子的半径
	double x;//绝对位置x坐标
	double y;//绝对位置y坐标
	int time;//豆子重生时间
	COLORREF color;//豆子的颜色
};

extern bean beans[NUM_OF_BEANS];

void ReCreate(int);

void beanDraw();
void beanInit();
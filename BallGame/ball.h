#pragma once

#include <graphics.h>

const int NUM_OF_BALLS = 40;//球的总数
const int intime = 300;//无敌时间
const double dv = 0.1;//每一次的速度增量

struct ball{
	double r;//球的半径
	double x;//绝对位置x坐标
	double y;//绝对位置y坐标
	double vx;//水平速度
	double vy;//竖直速度
	int time;//无敌时间
	long eatball;//吃球数
	long eatbean;//吃豆子数
	COLORREF color;//球的颜色
};

extern ball balls[NUM_OF_BALLS];

void ballDraw();
void ballUpdate();
void ballInit();
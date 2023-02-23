#pragma once

#include <graphics.h>

const int NUM_OF_SPORES = 1000;//孢子的最大数量

struct spore{
	int exist;//孢子是否存在,存在为1，不存在为0
	double x;//绝对位置x坐标
	double y;//绝对位置y坐标
	double vx;//水平速度
	double vy;//竖直速度
	double v;//合速度
	double sintheta;//速度方向角度
	COLORREF color;//孢子的颜色
};

extern spore spores[NUM_OF_SPORES];

void sporeDraw();
void sporeUpdate();
void sporeInit();
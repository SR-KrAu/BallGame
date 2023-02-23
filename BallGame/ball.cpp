#include "ball.h"
#include "background.h"
#include "time.h"
#include <math.h>
#include "bean.h"
#include "spore.h"

ball balls[NUM_OF_BALLS];

void ballDraw() {
	//绘制所有球体
	for (int i = 0; i < NUM_OF_BALLS; i++)
	{
		setlinecolor(balls[i].color);
		setlinestyle(PS_NULL);
		setfillcolor(balls[i].color);
		if (balls[i].time != 0) {
			if (balls[i].time % (intime / 20) == 0) {
				setfillcolor(WHITE);
			}
			else {
				setfillcolor(balls[i].color);
			}
			balls[i].time -= 1;
		}
		fillcircle((int)(scale * (balls[i].x - balls[0].x)), (int)(scale * (balls[i].y - balls[0].y)), (int)(scale * balls[i].r));
		setlinestyle(PS_SOLID, 4);
	}
}

void Resurrect(int ID) {
	//球复活时重建结构库
	int m, n;
	balls[ID].r = rand() % (30 - 10 + 1) + 10;
	m = (int)(-X + balls[ID].r);
	n = (int)(X - balls[ID].r);
	balls[ID].x = rand() % (n - m + 1) + m;
	m = (int)(-Y + balls[ID].r);
	n = (int)(Y - balls[ID].r);
	balls[ID].y = rand() % (n - m + 1) + m;
	balls[ID].vx = 0;
	balls[ID].vy = 0;
	balls[ID].time = intime;//无敌时间
}

void ballBean() {
	//球吃豆
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//遍历所有小球
		for (int j = 0; j < NUM_OF_BEANS; j++) {
			//遍历所有豆子
			if (beans[j].time == 0) {
				//当豆子未处于重生冷却时间时才可以被吃
				if (pow((balls[i].x - beans[j].x), 2) + pow((balls[i].y - beans[j].y), 2) <= pow((balls[i].r - beans[j].r), 2)) {
					//当球比豆子大时才可以被吃
					if (beans[j].r <= balls[i].r) {
						//球的生长符合面积守恒
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(beans[j].r, 2));//球大小增加
						balls[i].eatbean += 1;//吃球数+1
						ReCreate(j);//使被吃的豆子进入重生状态
					}
				}
			}
		}
	}
}

void ballBall() {
	//球吃球
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//遍历所有小球
		for (int j = i + 1; j < NUM_OF_BALLS; j++) {
			if (pow((balls[i].x - balls[j].x), 2) + pow((balls[i].y - balls[j].y), 2) <= 5 * pow((balls[i].r - balls[j].r), 2) / 4) {
				if (balls[i].r <= balls[j].r) {
					if (balls[i].time == 0) {//没有无敌时间才能被吃
						//球的生长符合面积守恒
						balls[j].r = sqrt(pow(balls[i].r, 2) + pow(balls[j].r, 2));
						balls[j].eatball += 1;
						Resurrect(i);//使被吃的球重生
					}
				}
				else {
					if (balls[j].time == 0) {//没有无敌时间才能被吃
						//球的生长符合面积守恒
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(balls[j].r, 2));
						balls[i].eatball += 1;
						Resurrect(j);//使被吃的球重生
					}
				}
			}
		}

	}
}

void Judge(int ID) {
	//速度上限与半径的关系(通过计算机进行非线性回归所得)
	double vmax = (10.3017491962168 + 0.129667540013608) / (1 + pow(balls[ID].r / 99.018783637313, 1.51501001125272)) - 0.129667540013608;
	//判断小球是否超出边界,是的话反弹小球,反弹损失一半的方向速度

	if (balls[ID].r + balls[ID].x >= X) {//右边界
		balls[ID].x = X - balls[ID].r;
		balls[ID].vx = -balls[ID].vx / 2;
	}

	if (balls[ID].x - balls[ID].r <= -X) {//左边界
		balls[ID].x = -X + balls[ID].r;
		balls[ID].vx = -balls[ID].vx / 2;
	}

	if (balls[ID].r + balls[ID].y >= Y) {//上边界
		balls[ID].y = Y - balls[ID].r;
		balls[ID].vy = -balls[ID].vy / 2;
	}

	if (balls[ID].y - balls[ID].r <= -Y) {//下边界
		balls[ID].y = -Y + balls[ID].r;
		balls[ID].vy = -balls[ID].vy / 2;
	}

	//判断速度是否超过上限,是的话调整速度
	if (pow(balls[ID].vx, 2) + pow(balls[ID].vy, 2) > pow(vmax, 2)) {
		if (balls[ID].vx > 0)
			balls[ID].vx -= dv;
		else
			balls[ID].vx += dv;

		if (balls[ID].vy > 0)
			balls[ID].vy -= dv;
		else
			balls[ID].vy += dv;
	}
}

void ballMove() {//小球移动
	// 遍历所有小球,移动位置，若碰到或越过边界，则反弹
	for (int i = 0; i < NUM_OF_BALLS; i++)
	{
		if (i != 0) {
			//使非玩家操控的小球随机移动
			balls[i].vx += rand() % 3 - 1;
			balls[i].vy += rand() % 3 - 1;
		}
		Judge(i);//判定小球是否超出边界或超速

		balls[i].x += balls[i].vx;
		balls[i].y += balls[i].vy;
		//使小球移动
	}
}

void ballSpore() {
	//球吃孢子功能
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//遍历所有小球
		for (int j = 0; j < NUM_OF_SPORES; j++) {
			if (spores[j].exist != 0) {
				if (pow((balls[i].x - spores[j].x), 2) + pow((balls[i].y - spores[j].y), 2) <= pow((balls[i].r - beans[j].r), 2)) {
					if (20 <= balls[i].r) {
						//球的生长符合面积守恒
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(20, 2));
						spores[j].exist = 0;//将被吃的孢子归回为不存在
					}
				}
			}
		}
	}
}

void ballUpdate() {
	//小球移动
	ballMove();

	//球吃豆的判定
	ballBean();

	//球吃球的判定
	ballBall();

	//球吃孢子的判定
	ballSpore();
}

void ballInit() {
	int m, n;
	//创建球体的初始化数据
	srand((unsigned)time(NULL));//用时间生成随机数
	for (int i = 0; i < NUM_OF_BALLS; i++)
	{
		balls[i].r = rand() % (30 - 10 + 1) + 10;//随机半径

		m = (int)(-X + balls[i].r);
		n = (int)(X - balls[i].r);
		balls[i].x = rand() % (n - m + 1) + m;//随机x坐标

		m = (int)(-Y + balls[i].r);
		n = (int)(Y - balls[i].r);
		balls[i].y = rand() % (n - m + 1) + m;//随机y坐标

		balls[i].color = HSVtoRGB((float)(rand() % 360), 0.8f, 0.9f);//随机HSV颜色

		balls[i].vx = 0;
		balls[i].vy = 0;
		//初始速度

		balls[i].eatball = 0;//吃球数
		balls[i].eatbean = 0;//吃豆数

		balls[i].time = intime;//无敌时间
	}
}
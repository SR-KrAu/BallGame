#include "game.h"
#include "background.h"
#include "ball.h"
#include "bean.h"
#include "spore.h"
#include <math.h>
#include <stdio.h>
#include "menu.h"
#include "file.h"

double scale;
bool w = false, s = false, a = false, d = false, scale_min = false, scale_plus = false;
bool Exit = false, J = false, quit = false;
// 记录各按键的按下状态
ExMessage msg;
bool textshow = true;
const int gametime = 600000;//游戏时间(单位:毫秒)

int nowtime;

void gameInit() {
	//初始化坐标系
	setaspectratio(1, -1);
	setorigin(rW / 2, rH / 2);

	//初始化时间
	nowtime = gametime;

	//初始化画面尺寸
	scale = 1;

	//初始化球
	ballInit();

	//初始化豆子
	beanInit();

	//初始化孢子
	sporeInit();

	//播放背景音乐
	mciSendString(TEXT("open 彩豆森林.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(TEXT("play bkmusic repeat"), NULL, 0, NULL);
}

void gameTime() {
	nowtime -= 10;
	//游戏结束跳出大循环
	if (nowtime <= 0) {
		//游戏结束机制
		setaspectratio(1, 1);
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//获取字体样式
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
		fontStyle.lfHeight = 100;//调整高度
		settextstyle(&fontStyle);//设置字体样式
		outtextxy(-200, -50, "游戏结束");
		fontStyle.lfHeight = 50;//调整高度
		settextstyle(&fontStyle);//设置字体样式
		outtextxy(-210, 50, "请按ESC键退出游戏");
		setaspectratio(1, -1);
		nowtime = 0;
	}
}

void text() {
	//显示文字内容
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	LOGFONT fontStyle;
	gettextstyle(&fontStyle);//获取字体样式
	fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
	fontStyle.lfHeight = 30;//调整高度
	fontStyle.lfWeight = 0;//粗细
	settextstyle(&fontStyle);//设置字体样式

	//时间制度转换分秒制
	int min, second;
	second = (int)(nowtime / 1000);//毫秒转秒
	min = second / 60;
	second = second % 60;

	char timetext[20], eatballtext[20], eatbeantext[20], sizetext[20];
	sprintf(timetext, "时间: %02d:%02d", min, second);
	sprintf(eatballtext, "吃球数: %ld", balls[0].eatball);
	sprintf(eatbeantext, "吃豆数: %ld", balls[0].eatbean);
	sprintf(sizetext, "大小: %.2f", balls[0].r);
	setaspectratio(1, 1);
	outtextxy(-rW / 2 + 40, -rH / 2 + 75, timetext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 110, eatballtext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 145, eatbeantext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 180, sizetext);
	if (textshow == true) {
		outtextxy(-rW / 2 + 40, -rH / 2 + 350, "操作说明:");
		outtextxy(-rW / 2 + 40, -rH / 2 + 385, "←↑→↓或WASD移动");
		outtextxy(-rW / 2 + 40, -rH / 2 + 420, "“+”“-”缩放画面大小");
		outtextxy(-rW / 2 + 40, -rH / 2 + 455, "ESC 暂停游戏");
		outtextxy(-rW / 2 + 40, -rH / 2 + 490, "T 开关操作说明");
		outtextxy(-rW / 2 + 40, -rH / 2 + 525, "J 吐孢子");
	}
	setaspectratio(1, -1);
}

void gameUpdate() {
	//更新球
	ballUpdate();

	//更新孢子
	sporeUpdate();

	//时间系统
	gameTime();

	//文字显示
	text();
}

void gameDraw() {
	//绘制背景
	backgroundDraw();

	//绘制豆子
	beanDraw();

	//绘制孢子
	sporeDraw();

	//绘制球
	ballDraw();
}

void PauseGame() {
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	LOGFONT fontStyle;
	setlinecolor(RGB(135, 206, 235));
	setlinestyle(PS_SOLID, 4);
	gettextstyle(&fontStyle);//获取字体样式
	fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
	fontStyle.lfHeight = 100;//调整高度
	fontStyle.lfWeight = 100;//粗细
	settextstyle(&fontStyle);//设置字体样式
	setaspectratio(1, 1);
	setorigin(0, 0);
	rectangle(rW / 2 - 200, rH / 2 - 100, rW / 2 + 200, rH / 2);
	rectangle(rW / 2 - 200, rH / 2 + 50, rW / 2 + 200, rH / 2 + 150);
	//文字矩形边框
	POINT point;
	ExMessage msg;
	while (1)
	{
		BeginBatchDraw();
		::GetCursorPos(&point);//获取鼠标位置
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 - 100, "继续游戏");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 50, "退出游戏");
		msg = getmessage();
		switch (msg.message)
		{
			//鼠标左键按下
		case WM_LBUTTONDOWN:
			if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
				setaspectratio(1, -1);
				setorigin(rW / 2, rH / 2);
				return;
			}
			if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
				fileWrite();//记录本局数据到文件中
				exit(1);//退出游戏
			}
			break;
		}

		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_ESCAPE:
				setaspectratio(1, -1);
				setorigin(rW / 2, rH / 2);
				return;
				break;
			}
		}
		FlushBatchDraw();
	}
}

void gameControl() {
	//游戏操作功能
	while (peekmessage(&msg, EX_KEY))
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_ADD:	  scale_plus = true;		break;
			case VK_SUBTRACT: scale_min = true;		break;
			case VK_UP:
			case 'W':		w = true;		break;
			case VK_DOWN:
			case 'S':		s = true;		break;
			case VK_LEFT:
			case 'A':		a = true;		break;
			case VK_RIGHT:
			case 'D':		d = true;		break;
			case 'J':		J = true;		break;
			case VK_ESCAPE:
				if (Exit == false)
					Exit = true;
				else
					Exit = false;
				break;
			case 'T':
				if (textshow == false)
					textshow = true;
				else
					textshow = false;
				break;
			}
		}
		if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case VK_ADD:	  scale_plus = false;		break;
			case VK_SUBTRACT: scale_min = false;		break;
			case VK_UP:
			case 'W':		w = false;		break;
			case VK_DOWN:
			case 'S':		s = false;		break;
			case VK_LEFT:
			case 'A':		a = false;		break;
			case VK_RIGHT:
			case 'D':		d = false;		break;
			case 'J':		J = false;		break;
			case VK_ESCAPE:	Exit = false;	break;
			}
		}
	}

	//键盘交互结果
	if (J) {
		if (nowtime % 100 == 0) {
			if (balls[0].r >= 30) {
				for (int i = 0; i < NUM_OF_SPORES; i++) {
					//吐孢子
					if (spores[i].exist == 0) {
						//孢子半径固定为20像素
						balls[0].r = sqrt(pow(balls[0].r, 2) - 400);
						spores[i].color = balls[0].color;
						spores[i].exist = 1;
						spores[i].x = balls[0].x + (balls[0].r + 20) * (balls[0].vx / sqrt(pow(balls[0].vx, 2) + pow(balls[0].vy, 2)));
						spores[i].y = balls[0].y + (balls[0].r + 20) * (balls[0].vy / sqrt(pow(balls[0].vx, 2) + pow(balls[0].vy, 2)));
						spores[i].vx = balls[0].vx * 2;
						spores[i].vy = balls[0].vy * 2;
						spores[i].v = sqrt(pow(spores[i].vx, 2) + pow(spores[i].vy, 2));
						spores[i].sintheta = fabs(spores[i].vy / spores[i].v);
						break;
					}
				}
			}
		}
	}
	if (Exit) {
		PauseGame();//游戏暂停
		cleardevice();
		Exit = false;
	}
	if (nowtime > 0) {
		if (scale_plus) {
			scale += 0.01;
		}
		if (scale_min) {
			if (scale - 0.01 > 0) {
				scale -= 0.01;
			}
		}
		double vmax = (10.3017491962168 + 0.129667540013608) / (1 + pow(balls[0].r / 99.018783637313, 1.51501001125272)) - 0.129667540013608;
		if (w) {
			if (pow(balls[0].vy + dv, 2) + pow(balls[0].vx, 2) > pow(vmax, 2)) {
				if (balls[0].vx >= 0)
					balls[0].vx -= dv;
				else
					balls[0].vx += dv;
			}
			if (balls[0].vy + dv <= vmax)
				balls[0].vy += dv;
		}
		if (s) {
		
			if (pow(balls[0].vy - dv, 2) + pow(balls[0].vx, 2) > pow(vmax, 2)) {
				if (balls[0].vx >= 0)
					balls[0].vx -= dv;
				else
					balls[0].vx += dv;
			}
			if (balls[0].vy - dv >= -vmax)
				balls[0].vy -= dv;
		}
		if (a) {
			if (pow(balls[0].vy, 2) + pow(balls[0].vx - dv, 2) > pow(vmax, 2)) {
				if (balls[0].vy >= 0)
					balls[0].vy -= dv;
				else
					balls[0].vy += dv;
			}
			if (balls[0].vx - dv >= -vmax)
				balls[0].vx -= dv;
		}
		if (d) {
			if (pow(balls[0].vy, 2) + pow(balls[0].vx + dv, 2) > pow(vmax, 2)) {
				if (balls[0].vy >= 0)
					balls[0].vy -= dv;
				else
					balls[0].vy += dv;
			}
			if (balls[0].vx + dv <= vmax)
				balls[0].vx += dv;
		}
	}
}

void gameLoop() {
	//游戏总循环
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);//精准帧率控制

	BeginBatchDraw();
	while (1) {
		cleardevice();//清空窗口

		QueryPerformanceCounter(&startCount);//精准帧率控制开始计时

		//绘制游戏场景
		gameDraw();

		//键盘交互
		gameControl();

		//更新主场景
		gameUpdate();

		QueryPerformanceCounter(&endCount);//精准帧率控制结束计时
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 10000) {//控制时差(单位：微秒)
			//Sleep(1);//每帧休眠1毫秒(开启可减小CPU占用率)
			//游戏帧率1秒100帧
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
#include "menu.h"
#include "game.h"
#include <stdio.h>

int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素
int status;

void menuInit() {
	status = 0;
}

int menuControl() {

	POINT point;
	ExMessage msg;
	while (peekmessage(&msg, EM_MOUSE))
	{
		::GetCursorPos(&point);//获取鼠标位置
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (status == 0) {
				if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
					//开始游戏
					gameInit();
					gameLoop();
				}
				else if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
					//帮助说明
					status = 1;
				}
				else if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 200 && point.y <= rH / 2 + 300) {
					//结束游戏
					return 2;
				}
				else if (point.x >= rW / 2 + 300 && point.x <= rW / 2 + 700 && point.y >= rH / 2 + 300 && point.y <= rH / 2 + 400) {
					//关于我们
					status = 3;
				}
			}
			else if (status == 1 || status == 3) {
				status = 0;
			}
		}
	}
	return 0;
}

void menuDraw() {
	BeginBatchDraw();
	cleardevice();
	if (status == 0) {
		IMAGE img;
		loadimage(&img, "Menu.jpg");
		HDC easyx_win = GetImageHDC();
		HDC img_hdc = GetImageHDC(&img);
		SetStretchBltMode(easyx_win, STRETCH_HALFTONE);
		StretchBlt(easyx_win, 0, 0, rW, rH, img_hdc, 0, 0, 2560, 1440, SRCCOPY);
		settextcolor(WHITE);
		setlinestyle(PS_SOLID, 4);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//获取字体样式
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
		fontStyle.lfHeight = 500;//调整高度
		fontStyle.lfWeight = 100;//粗细
		settextstyle(&fontStyle);//设置字体样式
		outtextxy(rW / 2 - 400, 100, "大  球  吃  小  球");
		rectangle(rW / 2 - 200, rH / 2 - 100, rW / 2 + 200, rH / 2);
		rectangle(rW / 2 - 200, rH / 2 + 50, rW / 2 + 200, rH / 2 + 150);
		rectangle(rW / 2 - 200, rH / 2 + 200, rW / 2 + 200, rH / 2 + 300);
		rectangle(rW / 2 + 300, rH / 2 + 300, rW / 2 + 700, rH / 2 + 400);
		//文字矩形边框
		fontStyle.lfHeight = 50;//调整高度
		settextstyle(&fontStyle);//设置字体样式
		outtextxy(rW / 2 + 400, 200, "v1.2");
		outtextxy(0, rH - 50, "版权所有：2022 大球吃小球");
		fontStyle.lfHeight = 100;//调整高度
		settextstyle(&fontStyle);//设置字体样式
		POINT point;
		::GetCursorPos(&point);//获取鼠标位置
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 - 100, "开始游戏");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 50, "帮助说明");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 200 && point.y <= rH / 2 + 300) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 200, "退出游戏");
		if (point.x >= rW / 2 + 300 && point.x <= rW / 2 + 700 && point.y >= rH / 2 + 300 && point.y <= rH / 2 + 400) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 + 300, rH / 2 + 300, "关于我们");
	}
	else if (status == 1) {
		settextcolor(WHITE);
		setlinestyle(PS_SOLID, 4);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//获取字体样式
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
		fontStyle.lfHeight = 40;//调整高度
		fontStyle.lfWeight = 30;//粗细
		settextstyle(&fontStyle);//设置字体样式

		outtextxy(rW / 2 - 200, rH / 2 - 100, "在游戏中操控小球");
		outtextxy(rW / 2 - 200, rH / 2 - 50, "吃掉比自己更小的球即可长大");
		outtextxy(rW / 2 - 200, rH / 2, "按键操作说明可在对局内查看");
		outtextxy(rW / 2 - 200, rH / 2 + 50, "BGM: 彩豆森林-球球大作战");
		outtextxy(rW / 2 - 200, rH / 2 + 100, "“鼠标按任意位置返回”");
	}
	else if (status == 3) {
		settextcolor(WHITE);
		setlinestyle(PS_SOLID, 4);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//获取字体样式
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
		fontStyle.lfHeight = 40;//调整高度
		fontStyle.lfWeight = 30;//粗细
		settextstyle(&fontStyle);//设置字体样式
		outtextxy(rW / 2 - 400, rH / 2 - 100, "程序名称:大球吃小球");
		outtextxy(rW / 2 - 400, rH / 2 - 50, "版本信息:v1.2");
		outtextxy(rW / 2 - 400, rH / 2, "开发时间:2022.12");
		outtextxy(rW / 2 - 400, rH / 2 + 50, "“鼠标按任意位置返回”");
	}
	FlushBatchDraw();
}

void menuLoop() {
	int control;
	while (1) {
		//绘制菜单
		menuDraw();

		//菜单操作系统
		control = menuControl();

		if (control == 2) {
			break;
		}
	}
}
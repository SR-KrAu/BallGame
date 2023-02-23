#include <graphics.h>
#include <stdio.h>
#include "menu.h"

int main() {
	int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
	int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素
	//创建全屏窗口
	HWND hwnd = initgraph(rW, rH); // 初始化绘图窗口并获取窗口句柄（以 EasyX 为例）
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // 获取窗口信息
	// 设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);// 直接修改窗口样式
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
	menuInit();
	menuLoop();
	return 0;
}
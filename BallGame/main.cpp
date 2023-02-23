#include <graphics.h>
#include <stdio.h>
#include "menu.h"

int main() {
	int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
	int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
	//����ȫ������
	HWND hwnd = initgraph(rW, rH); // ��ʼ����ͼ���ڲ���ȡ���ھ������ EasyX Ϊ����
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // ��ȡ������Ϣ
	// ���ô�����Ϣ ��� ȡ�����������߿�
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);// ֱ���޸Ĵ�����ʽ
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
	menuInit();
	menuLoop();
	return 0;
}
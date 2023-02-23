#include "menu.h"
#include "game.h"
#include <stdio.h>

int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
int status;

void menuInit() {
	status = 0;
}

int menuControl() {

	POINT point;
	ExMessage msg;
	while (peekmessage(&msg, EM_MOUSE))
	{
		::GetCursorPos(&point);//��ȡ���λ��
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (status == 0) {
				if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
					//��ʼ��Ϸ
					gameInit();
					gameLoop();
				}
				else if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
					//����˵��
					status = 1;
				}
				else if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 200 && point.y <= rH / 2 + 300) {
					//������Ϸ
					return 2;
				}
				else if (point.x >= rW / 2 + 300 && point.x <= rW / 2 + 700 && point.y >= rH / 2 + 300 && point.y <= rH / 2 + 400) {
					//��������
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
		gettextstyle(&fontStyle);//��ȡ������ʽ
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
		fontStyle.lfHeight = 500;//�����߶�
		fontStyle.lfWeight = 100;//��ϸ
		settextstyle(&fontStyle);//����������ʽ
		outtextxy(rW / 2 - 400, 100, "��  ��  ��  С  ��");
		rectangle(rW / 2 - 200, rH / 2 - 100, rW / 2 + 200, rH / 2);
		rectangle(rW / 2 - 200, rH / 2 + 50, rW / 2 + 200, rH / 2 + 150);
		rectangle(rW / 2 - 200, rH / 2 + 200, rW / 2 + 200, rH / 2 + 300);
		rectangle(rW / 2 + 300, rH / 2 + 300, rW / 2 + 700, rH / 2 + 400);
		//���־��α߿�
		fontStyle.lfHeight = 50;//�����߶�
		settextstyle(&fontStyle);//����������ʽ
		outtextxy(rW / 2 + 400, 200, "v1.2");
		outtextxy(0, rH - 50, "��Ȩ���У�2022 �����С��");
		fontStyle.lfHeight = 100;//�����߶�
		settextstyle(&fontStyle);//����������ʽ
		POINT point;
		::GetCursorPos(&point);//��ȡ���λ��
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 - 100, "��ʼ��Ϸ");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 50, "����˵��");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 200 && point.y <= rH / 2 + 300) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 200, "�˳���Ϸ");
		if (point.x >= rW / 2 + 300 && point.x <= rW / 2 + 700 && point.y >= rH / 2 + 300 && point.y <= rH / 2 + 400) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 + 300, rH / 2 + 300, "��������");
	}
	else if (status == 1) {
		settextcolor(WHITE);
		setlinestyle(PS_SOLID, 4);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//��ȡ������ʽ
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
		fontStyle.lfHeight = 40;//�����߶�
		fontStyle.lfWeight = 30;//��ϸ
		settextstyle(&fontStyle);//����������ʽ

		outtextxy(rW / 2 - 200, rH / 2 - 100, "����Ϸ�вٿ�С��");
		outtextxy(rW / 2 - 200, rH / 2 - 50, "�Ե����Լ���С���򼴿ɳ���");
		outtextxy(rW / 2 - 200, rH / 2, "��������˵�����ڶԾ��ڲ鿴");
		outtextxy(rW / 2 - 200, rH / 2 + 50, "BGM: �ʶ�ɭ��-�������ս");
		outtextxy(rW / 2 - 200, rH / 2 + 100, "����갴����λ�÷��ء�");
	}
	else if (status == 3) {
		settextcolor(WHITE);
		setlinestyle(PS_SOLID, 4);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//��ȡ������ʽ
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
		fontStyle.lfHeight = 40;//�����߶�
		fontStyle.lfWeight = 30;//��ϸ
		settextstyle(&fontStyle);//����������ʽ
		outtextxy(rW / 2 - 400, rH / 2 - 100, "��������:�����С��");
		outtextxy(rW / 2 - 400, rH / 2 - 50, "�汾��Ϣ:v1.2");
		outtextxy(rW / 2 - 400, rH / 2, "����ʱ��:2022.12");
		outtextxy(rW / 2 - 400, rH / 2 + 50, "����갴����λ�÷��ء�");
	}
	FlushBatchDraw();
}

void menuLoop() {
	int control;
	while (1) {
		//���Ʋ˵�
		menuDraw();

		//�˵�����ϵͳ
		control = menuControl();

		if (control == 2) {
			break;
		}
	}
}
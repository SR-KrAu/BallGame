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
// ��¼�������İ���״̬
ExMessage msg;
bool textshow = true;
const int gametime = 600000;//��Ϸʱ��(��λ:����)

int nowtime;

void gameInit() {
	//��ʼ������ϵ
	setaspectratio(1, -1);
	setorigin(rW / 2, rH / 2);

	//��ʼ��ʱ��
	nowtime = gametime;

	//��ʼ������ߴ�
	scale = 1;

	//��ʼ����
	ballInit();

	//��ʼ������
	beanInit();

	//��ʼ������
	sporeInit();

	//���ű�������
	mciSendString(TEXT("open �ʶ�ɭ��.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(TEXT("play bkmusic repeat"), NULL, 0, NULL);
}

void gameTime() {
	nowtime -= 10;
	//��Ϸ����������ѭ��
	if (nowtime <= 0) {
		//��Ϸ��������
		setaspectratio(1, 1);
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		LOGFONT fontStyle;
		gettextstyle(&fontStyle);//��ȡ������ʽ
		fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
		fontStyle.lfHeight = 100;//�����߶�
		settextstyle(&fontStyle);//����������ʽ
		outtextxy(-200, -50, "��Ϸ����");
		fontStyle.lfHeight = 50;//�����߶�
		settextstyle(&fontStyle);//����������ʽ
		outtextxy(-210, 50, "�밴ESC���˳���Ϸ");
		setaspectratio(1, -1);
		nowtime = 0;
	}
}

void text() {
	//��ʾ��������
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	LOGFONT fontStyle;
	gettextstyle(&fontStyle);//��ȡ������ʽ
	fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
	fontStyle.lfHeight = 30;//�����߶�
	fontStyle.lfWeight = 0;//��ϸ
	settextstyle(&fontStyle);//����������ʽ

	//ʱ���ƶ�ת��������
	int min, second;
	second = (int)(nowtime / 1000);//����ת��
	min = second / 60;
	second = second % 60;

	char timetext[20], eatballtext[20], eatbeantext[20], sizetext[20];
	sprintf(timetext, "ʱ��: %02d:%02d", min, second);
	sprintf(eatballtext, "������: %ld", balls[0].eatball);
	sprintf(eatbeantext, "�Զ���: %ld", balls[0].eatbean);
	sprintf(sizetext, "��С: %.2f", balls[0].r);
	setaspectratio(1, 1);
	outtextxy(-rW / 2 + 40, -rH / 2 + 75, timetext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 110, eatballtext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 145, eatbeantext);
	outtextxy(-rW / 2 + 40, -rH / 2 + 180, sizetext);
	if (textshow == true) {
		outtextxy(-rW / 2 + 40, -rH / 2 + 350, "����˵��:");
		outtextxy(-rW / 2 + 40, -rH / 2 + 385, "����������WASD�ƶ�");
		outtextxy(-rW / 2 + 40, -rH / 2 + 420, "��+����-�����Ż����С");
		outtextxy(-rW / 2 + 40, -rH / 2 + 455, "ESC ��ͣ��Ϸ");
		outtextxy(-rW / 2 + 40, -rH / 2 + 490, "T ���ز���˵��");
		outtextxy(-rW / 2 + 40, -rH / 2 + 525, "J ������");
	}
	setaspectratio(1, -1);
}

void gameUpdate() {
	//������
	ballUpdate();

	//��������
	sporeUpdate();

	//ʱ��ϵͳ
	gameTime();

	//������ʾ
	text();
}

void gameDraw() {
	//���Ʊ���
	backgroundDraw();

	//���ƶ���
	beanDraw();

	//��������
	sporeDraw();

	//������
	ballDraw();
}

void PauseGame() {
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	LOGFONT fontStyle;
	setlinecolor(RGB(135, 206, 235));
	setlinestyle(PS_SOLID, 4);
	gettextstyle(&fontStyle);//��ȡ������ʽ
	fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
	fontStyle.lfHeight = 100;//�����߶�
	fontStyle.lfWeight = 100;//��ϸ
	settextstyle(&fontStyle);//����������ʽ
	setaspectratio(1, 1);
	setorigin(0, 0);
	rectangle(rW / 2 - 200, rH / 2 - 100, rW / 2 + 200, rH / 2);
	rectangle(rW / 2 - 200, rH / 2 + 50, rW / 2 + 200, rH / 2 + 150);
	//���־��α߿�
	POINT point;
	ExMessage msg;
	while (1)
	{
		BeginBatchDraw();
		::GetCursorPos(&point);//��ȡ���λ��
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 - 100, "������Ϸ");
		settextcolor(WHITE);
		if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
			settextcolor(YELLOW);
		}
		else {
			settextcolor(WHITE);
		}
		outtextxy(rW / 2 - 200, rH / 2 + 50, "�˳���Ϸ");
		msg = getmessage();
		switch (msg.message)
		{
			//����������
		case WM_LBUTTONDOWN:
			if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 - 100 && point.y <= rH / 2) {
				setaspectratio(1, -1);
				setorigin(rW / 2, rH / 2);
				return;
			}
			if (point.x >= rW / 2 - 200 && point.x <= rW / 2 + 200 && point.y >= rH / 2 + 50 && point.y <= rH / 2 + 150) {
				fileWrite();//��¼�������ݵ��ļ���
				exit(1);//�˳���Ϸ
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
	//��Ϸ��������
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

	//���̽������
	if (J) {
		if (nowtime % 100 == 0) {
			if (balls[0].r >= 30) {
				for (int i = 0; i < NUM_OF_SPORES; i++) {
					//������
					if (spores[i].exist == 0) {
						//���Ӱ뾶�̶�Ϊ20����
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
		PauseGame();//��Ϸ��ͣ
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
	//��Ϸ��ѭ��
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);//��׼֡�ʿ���

	BeginBatchDraw();
	while (1) {
		cleardevice();//��մ���

		QueryPerformanceCounter(&startCount);//��׼֡�ʿ��ƿ�ʼ��ʱ

		//������Ϸ����
		gameDraw();

		//���̽���
		gameControl();

		//����������
		gameUpdate();

		QueryPerformanceCounter(&endCount);//��׼֡�ʿ��ƽ�����ʱ
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 10000) {//����ʱ��(��λ��΢��)
			//Sleep(1);//ÿ֡����1����(�����ɼ�СCPUռ����)
			//��Ϸ֡��1��100֡
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
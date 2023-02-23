#include "spore.h"
#include "background.h"
#include "math.h"

spore spores[NUM_OF_SPORES];

void sporeDraw() {
	//������������
	setlinestyle(PS_SOLID, 4);
	for (int i = 0; i < NUM_OF_SPORES; i++) {
		if (spores[i].exist != 0) {
			setfillcolor(spores[i].color);
			setlinecolor(spores[i].color);
			fillcircle((int)(scale * (spores[i].x - balls[0].x)), (int)(scale * (spores[i].y - balls[0].y)), (int)(scale * 20));
		}
	}
}

void sporeMove() {
	//�����ƶ�
	for (int i = 0; i < NUM_OF_SPORES; i++) {
		if (spores[i].exist != 0) {
			//ʹ�����ƶ�
			spores[i].x += spores[i].vx;
			spores[i].y += spores[i].vy;

			//��ֹ���Ӵ�͸�߽�
			if (20 + spores[i].x >= X) {
				spores[i].x = X - 20;
				spores[i].vx = -spores[i].vx / 2;
			}
			if (spores[i].x - 20 <= -X) {
				spores[i].x = -X + 20;
				spores[i].vx = -spores[i].vx / 2;
			}
			if (20 + spores[i].y >= Y) {
				spores[i].y = Y - 20;
				spores[i].vy = -spores[i].vy / 2;
			}
			if (spores[i].y - 20 <= -Y) {
				spores[i].y = -Y + 20;
				spores[i].vy = -spores[i].vy / 2;
			}

			//ʹ���ӵ��ٶ��𽥼���
			if (spores[i].v < 0.1) {
				spores[i].vx = 0;
				spores[i].vy = 0;
				spores[i].v = 0;
			}
			else {
				double DV = 0.1;
				spores[i].v -= DV;

				if (spores[i].vx >= 0 && spores[i].vy >= 0) {
					spores[i].vx = spores[i].v * sqrt(1 - pow(spores[i].sintheta, 2));
					spores[i].vy = spores[i].v * spores[i].sintheta;
				}
				else if (spores[i].vx < 0 && spores[i].vy >= 0) {
					spores[i].vx = -spores[i].v * sqrt(1 - pow(spores[i].sintheta, 2));
					spores[i].vy = spores[i].v * spores[i].sintheta;
				}
				else if (spores[i].vx < 0 && spores[i].vy < 0) {
					spores[i].vx = -spores[i].v * sqrt(1 - pow(spores[i].sintheta, 2));
					spores[i].vy = -spores[i].v * spores[i].sintheta;
				}
				else if (spores[i].vx >= 0 && spores[i].vy < 0) {
					spores[i].vx = spores[i].v * sqrt(1 - pow(spores[i].sintheta, 2));
					spores[i].vy = -spores[i].v * spores[i].sintheta;
				}
			}

		}
	}
}

void sporeUpdate() {
	//�����ƶ�
	sporeMove();
}

void sporeInit() {
	//�������ӽṹ��
	for (int i = 0; i < NUM_OF_SPORES; i++)
	{
		spores[i].exist = 0;//����Ϊ������
	}
}
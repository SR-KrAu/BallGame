#include "ball.h"
#include "background.h"
#include "time.h"
#include <math.h>
#include "bean.h"
#include "spore.h"

ball balls[NUM_OF_BALLS];

void ballDraw() {
	//������������
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
	//�򸴻�ʱ�ؽ��ṹ��
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
	balls[ID].time = intime;//�޵�ʱ��
}

void ballBean() {
	//��Զ�
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//��������С��
		for (int j = 0; j < NUM_OF_BEANS; j++) {
			//�������ж���
			if (beans[j].time == 0) {
				//������δ����������ȴʱ��ʱ�ſ��Ա���
				if (pow((balls[i].x - beans[j].x), 2) + pow((balls[i].y - beans[j].y), 2) <= pow((balls[i].r - beans[j].r), 2)) {
					//����ȶ��Ӵ�ʱ�ſ��Ա���
					if (beans[j].r <= balls[i].r) {
						//���������������غ�
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(beans[j].r, 2));//���С����
						balls[i].eatbean += 1;//������+1
						ReCreate(j);//ʹ���ԵĶ��ӽ�������״̬
					}
				}
			}
		}
	}
}

void ballBall() {
	//�����
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//��������С��
		for (int j = i + 1; j < NUM_OF_BALLS; j++) {
			if (pow((balls[i].x - balls[j].x), 2) + pow((balls[i].y - balls[j].y), 2) <= 5 * pow((balls[i].r - balls[j].r), 2) / 4) {
				if (balls[i].r <= balls[j].r) {
					if (balls[i].time == 0) {//û���޵�ʱ����ܱ���
						//���������������غ�
						balls[j].r = sqrt(pow(balls[i].r, 2) + pow(balls[j].r, 2));
						balls[j].eatball += 1;
						Resurrect(i);//ʹ���Ե�������
					}
				}
				else {
					if (balls[j].time == 0) {//û���޵�ʱ����ܱ���
						//���������������غ�
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(balls[j].r, 2));
						balls[i].eatball += 1;
						Resurrect(j);//ʹ���Ե�������
					}
				}
			}
		}

	}
}

void Judge(int ID) {
	//�ٶ�������뾶�Ĺ�ϵ(ͨ����������з����Իع�����)
	double vmax = (10.3017491962168 + 0.129667540013608) / (1 + pow(balls[ID].r / 99.018783637313, 1.51501001125272)) - 0.129667540013608;
	//�ж�С���Ƿ񳬳��߽�,�ǵĻ�����С��,������ʧһ��ķ����ٶ�

	if (balls[ID].r + balls[ID].x >= X) {//�ұ߽�
		balls[ID].x = X - balls[ID].r;
		balls[ID].vx = -balls[ID].vx / 2;
	}

	if (balls[ID].x - balls[ID].r <= -X) {//��߽�
		balls[ID].x = -X + balls[ID].r;
		balls[ID].vx = -balls[ID].vx / 2;
	}

	if (balls[ID].r + balls[ID].y >= Y) {//�ϱ߽�
		balls[ID].y = Y - balls[ID].r;
		balls[ID].vy = -balls[ID].vy / 2;
	}

	if (balls[ID].y - balls[ID].r <= -Y) {//�±߽�
		balls[ID].y = -Y + balls[ID].r;
		balls[ID].vy = -balls[ID].vy / 2;
	}

	//�ж��ٶ��Ƿ񳬹�����,�ǵĻ������ٶ�
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

void ballMove() {//С���ƶ�
	// ��������С��,�ƶ�λ�ã���������Խ���߽磬�򷴵�
	for (int i = 0; i < NUM_OF_BALLS; i++)
	{
		if (i != 0) {
			//ʹ����Ҳٿص�С������ƶ�
			balls[i].vx += rand() % 3 - 1;
			balls[i].vy += rand() % 3 - 1;
		}
		Judge(i);//�ж�С���Ƿ񳬳��߽����

		balls[i].x += balls[i].vx;
		balls[i].y += balls[i].vy;
		//ʹС���ƶ�
	}
}

void ballSpore() {
	//������ӹ���
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		//��������С��
		for (int j = 0; j < NUM_OF_SPORES; j++) {
			if (spores[j].exist != 0) {
				if (pow((balls[i].x - spores[j].x), 2) + pow((balls[i].y - spores[j].y), 2) <= pow((balls[i].r - beans[j].r), 2)) {
					if (20 <= balls[i].r) {
						//���������������غ�
						balls[i].r = sqrt(pow(balls[i].r, 2) + pow(20, 2));
						spores[j].exist = 0;//�����Ե����ӹ��Ϊ������
					}
				}
			}
		}
	}
}

void ballUpdate() {
	//С���ƶ�
	ballMove();

	//��Զ����ж�
	ballBean();

	//�������ж�
	ballBall();

	//������ӵ��ж�
	ballSpore();
}

void ballInit() {
	int m, n;
	//��������ĳ�ʼ������
	srand((unsigned)time(NULL));//��ʱ�����������
	for (int i = 0; i < NUM_OF_BALLS; i++)
	{
		balls[i].r = rand() % (30 - 10 + 1) + 10;//����뾶

		m = (int)(-X + balls[i].r);
		n = (int)(X - balls[i].r);
		balls[i].x = rand() % (n - m + 1) + m;//���x����

		m = (int)(-Y + balls[i].r);
		n = (int)(Y - balls[i].r);
		balls[i].y = rand() % (n - m + 1) + m;//���y����

		balls[i].color = HSVtoRGB((float)(rand() % 360), 0.8f, 0.9f);//���HSV��ɫ

		balls[i].vx = 0;
		balls[i].vy = 0;
		//��ʼ�ٶ�

		balls[i].eatball = 0;//������
		balls[i].eatbean = 0;//�Զ���

		balls[i].time = intime;//�޵�ʱ��
	}
}
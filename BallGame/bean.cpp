#include "bean.h"
#include "background.h"

bean beans[NUM_OF_BEANS];

void beanDraw() {
	//���ƶ���
	int m, n;
	setlinestyle(PS_SOLID, 3);
	for (int i = 0; i < NUM_OF_BEANS; i++)
	{
		if (beans[i].time == 0) {
			setlinecolor(beans[i].color);
			circle((int)(scale * (beans[i].x - balls[0].x)), (int)(scale * (beans[i].y - balls[0].y)), (int)(scale * beans[i].r));
		}
		else if (beans[i].time != 1) {
			beans[i].time -= 1;
		}
		else {
			m = (int)(-X + beans[i].r);
			n = (int)(X - beans[i].r);
			beans[i].x = rand() % (n - m + 1) + m;
			m = (int)(-Y + beans[i].r);
			n = (int)(Y - beans[i].r);
			beans[i].y = rand() % (n - m + 1) + m;
			beans[i].time = 0;
		}
	}
}

void ReCreate(int ID) {
	//ʹ����ˢ�½��������״̬
	beans[ID].x = 2 * X;
	beans[ID].y = 2 * Y;
	beans[ID].time = retime;
}

void beanInit() {
	//��ʼ����������
	int m, n;
	//��������
	for (int i = 0; i < NUM_OF_BEANS; i++)
	{
		beans[i].r = rand() % (10 - 4 + 1) + 4;//�����С
		
		m = (int)(-X + beans[i].r);
		n = (int)(X - beans[i].r);
		beans[i].x = rand() % (n - m + 1) + m;//���x����

		m = (int)(-Y + beans[i].r);
		n = (int)(Y - beans[i].r);
		beans[i].y = rand() % (n - m + 1) + m;//���y����

		beans[i].color = HSVtoRGB((float)(rand() % 360), 0.8f, 0.9f);//�����ɫ

		beans[i].time = 0;//��������ʱ��
	}

}
#include "bean.h"
#include "background.h"

bean beans[NUM_OF_BEANS];

void beanDraw() {
	//绘制豆子
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
	//使豆子刷新进入待重生状态
	beans[ID].x = 2 * X;
	beans[ID].y = 2 * Y;
	beans[ID].time = retime;
}

void beanInit() {
	//初始化豆子数据
	int m, n;
	//创建豆子
	for (int i = 0; i < NUM_OF_BEANS; i++)
	{
		beans[i].r = rand() % (10 - 4 + 1) + 4;//随机大小
		
		m = (int)(-X + beans[i].r);
		n = (int)(X - beans[i].r);
		beans[i].x = rand() % (n - m + 1) + m;//随机x坐标

		m = (int)(-Y + beans[i].r);
		n = (int)(Y - beans[i].r);
		beans[i].y = rand() % (n - m + 1) + m;//随机y坐标

		beans[i].color = HSVtoRGB((float)(rand() % 360), 0.8f, 0.9f);//随机颜色

		beans[i].time = 0;//设置重生时间
	}

}
#include "background.h"

void backgroundDraw() {
	setlinecolor(RGB(135, 206, 235));
	setlinestyle(PS_SOLID, 2);
	double left = -X - balls[0].x, up = Y - balls[0].y, right = X - balls[0].x, down = -Y - balls[0].y;
	double x1, x2, y1, y2;
	//绘制横线
	for (x1 = left, y1 = up, x2 = right; y1 >= down; y1 -= 500) {
		line((int)(scale * x1), (int)(scale * y1), (int)(scale * x2), (int)(scale * y1));
	}
	//绘制竖线
	for (y1 = up, x1 = right, y2 = down; x1 >= left; x1 -= 500) {
		line((int)(scale * x1), (int)(scale * y1), (int)(scale * x1), (int)(scale * y2));
	}
}
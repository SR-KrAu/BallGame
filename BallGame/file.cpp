#include "file.h"
#include <stdio.h>
#include "ball.h"

void fileWrite() {
	FILE* pf = fopen("game.txt", "w");//�����ļ�
	fprintf(pf, "�Ͼּ�¼:\n������:%d\n�Զ���:%d\n��С:%.2lf", balls[0].eatball, balls[0].eatbean, balls[0].r);
}
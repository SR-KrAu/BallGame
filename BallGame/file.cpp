#include "file.h"
#include <stdio.h>
#include "ball.h"

void fileWrite() {
	FILE* pf = fopen("game.txt", "w");//创建文件
	fprintf(pf, "上局记录:\n吃球数:%d\n吃豆数:%d\n大小:%.2lf", balls[0].eatball, balls[0].eatbean, balls[0].r);
}
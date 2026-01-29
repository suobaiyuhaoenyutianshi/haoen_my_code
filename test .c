#define _CRT_SECURE_NO_WARNINGS
#include"game.h"
void menu()
{
	printf("**********************\n");
	printf("1.play\n");
	printf("0.exit\n");
	printf("**********************\n");
}
void game()
{
	//存放布置 mine
	char mine[ROWS][COLS] = { 0 };
	//存放排查 show
	char show[ROWS][COLS] = { 0 };
	//初始化  mine 没布置雷全是'0',字符
    //show 未展现 雷数字 布置'#'，字符
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '#');
	//布置雷
	SetMine(mine, ROW, COL);
	DisPlay(mine, ROW, COL);
	DisPlay(show, ROW, COL);
	FindMine(mine, show, ROW, COL);
	DisPlay(mine, ROW, COL);
	DisPlay(show, ROW, COL);
}
int main()
{
	int input = 0;
	srand((unsigned)time(NULL));
	do
	{
		printf("请选择\n");
		menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			printf("开始\n");
			break;
		case 0:
			printf("退出");
			break;
		default:
			printf("选择错误");
			break;
		}
	} while (input);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

void menu()
{
    printf("1. play\n");
    printf("0. exit\n");
    printf("请选择: ");
}

void game()
{
    char board[ROWS][COLS] = { 0 };
    Initboard(board, ROW, COL);
    DisplayBoard(board, ROW, COL);

    int x = 0, y = 0;
    char ret;
    while (1)
    {
        printf("玩家1请下棋'*'\n");
        PlayMove1(board, ROW, COL, &x, &y);
        DisplayBoard(board, ROW, COL);
        ret = Inwin(board, ROW, COL, x, y, '*');
        if (ret != 'C')
            break;

        printf("\n玩家2请下棋'#'\n");
        PlayMove2(board, ROW, COL, &x, &y);
        DisplayBoard(board, ROW, COL);
        ret = Inwin(board, ROW, COL, x, y, '#');
        if (ret != 'C') 
            break;
    }

    printf("\n");
    if (ret == '*')
        printf("玩家1赢了\n");
    else if (ret == '#') 
        printf("玩家2赢了\n");
    else
        printf("平局\n");
}

int main()
{
    int input = 0;
    do
    {
        menu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("请重新选择\n");
            break;
        }
    } while (input);
    return 0;
}
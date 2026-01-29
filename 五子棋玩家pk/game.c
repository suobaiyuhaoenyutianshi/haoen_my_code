#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

void Initboard(char board[ROWS][COLS], int row, int col)
{
    int i = 0, j = 0;
    for (i = 4; i < (4 + row); i++)
    {
        for (j = 4; j < (4 + col); j++)
        {
            board[i][j] = ' ';
        }
    }
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
    int i = 0, j = 0,b=0;
    printf(" ");
    for (i = 0; i <=col; i++)
    {
        printf("%-2d ", i);
    }
    printf("\n");
    for (i = 4; i < (4 + row); i++)
    {
        int b = i - 3;
        printf("%-2d", b);
        for (j = 4; j < (4 + col); j++)
        {
            if (j == 4)
            {
                printf(" %2c",board[i][j]);
            }
            if (j > 4)
            {
                printf("%-2c", board[i][j]);
            }
            if (j < 4 + col - 1)
            {
                if (j == 4)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        printf("\n");
        if (i < 4 + row - 1)
        {
            for (int j = 4; j < 4 + col; j++)
            {  
                if (j == 4)
                {
                    printf("    ");
                }
                printf("--");
                if (j < 4 + col - 1)
                {
                    printf("|");
                }
            }
            printf("\n");
        }
    }
}

void PlayMove1(char board[ROWS][COLS], int row, int col, int* x, int* y)
{
    while (1)
    {
        int a = 0, b = 0;
        printf("玩家1请输入坐标: ");
        scanf("%d %d", &a, &b);
        *x = 3 + a;
        *y = 3 + b;
        if (a >= 1 && a <= row && b >= 1 && b <= col)
        {
            if (board[*x][*y] == ' ')
            {
                board[*x][*y] = '*';
                break;
            }
            else
            {
                printf("该位置已被占用，请重新输入\n");
            }
        }
        else
        {
            printf("坐标超出范围(1-%d, 1-%d)，请重新输入\n", row, col);
        }
    }
}

void PlayMove2(char board[ROWS][COLS], int row, int col, int* x, int* y)
{
    while (1)
    {
        int a = 0, b = 0;
        printf("玩家2请输入坐标: ");
        scanf("%d %d", &a, &b);
        *x = 3 + a;
        *y = 3 + b;
        if (a >= 1 && a <= row && b >= 1 && b <= col)
        {
            if (board[*x][*y] == ' ')
            {
                board[*x][*y] = '#';
                break;
            }
            else
            {
                printf("该位置已被占用，请重新输入\n");
            }
        }
        else
        {
            printf("坐标超出范围(1-%d, 1-%d)，请重新输入\n", row, col);
        }
    }
}

char Inwin(char board[ROWS][COLS], int row, int col, int lastX, int lastY, char player)
{
    int directions[4][2] =
    {//向量
        {1, 0},   // 水平
        {0, 1},   // 垂直
        {1, 1},   // 主对角线
        {1, -1}   // 副对角线
    };

    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];//d是行，0，1是列，方便使用向量，听类似数组的理解方式
        int dy = directions[d][1];
        int count = 1;
        //穿过来的意味1了，所以不计算自身那一次
        for (int i = 1; i < 5; i++)
        {
            int x = lastX + i * dx;
            int y = lastY + i * dy;
            if (x < 4 || x >= 4 + row || y < 4 || y >= 4 + col || board[x][y] != player)
            {
                break;
            }
            count++;
        }

        for (int i = 1; i < 5; i++)
        {
            int x = lastX - i * dx;
            int y = lastY - i * dy;
            if (x < 4 || x >= 4 + row || y < 4 || y >= 4 + col || board[x][y] != player)
            {
                break;
            }
            count++;
        }

        if (count >= 5)
        {
            return player;
        }
    }

    for (int i = 4; i < 4 + row; i++)
    {
        for (int j = 4; j < 4 + col; j++)
        {
            if (board[i][j] == ' ')
            {
                return 'C';
            }
        }
    }

    
}
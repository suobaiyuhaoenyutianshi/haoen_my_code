#pragma once
#pragma once
#include<time.h>
#include<stdio.h>
#define ROW 10
#define COL 10
#define ROWS (ROW+10)
#define COLS (COL+10)

void Initboard(char board[ROWS][COLS], int row, int col);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
void PlayMove1(char board[ROWS][COLS], int row, int col, int* x, int* y);
void PlayMove2(char board[ROWS][COLS], int row, int col, int* x, int* y);
char Inwin(char board[ROWS][COLS], int row, int col, int x, int y, char player);
//两个玩家下棋的代码，明显写重复了，只要使闯过去的char不同就行了，但我不打算改了
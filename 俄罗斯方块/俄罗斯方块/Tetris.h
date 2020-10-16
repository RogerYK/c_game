#pragma once
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#define UP 72
#define LEFT 75
#define DOWN 80
#define RIGHT 77 
#define sizeX 10
#define sizeY 25
#define MESSAGE_LEN 20
#define IRED (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define RED (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_RED)
#define IYELLOW (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN)
#define IGREEN (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define GREEN (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_GREEN)
#define ICYAN (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define CYAN (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define IBLUE (BACKGROUND_BLUE|BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define BLUE (BACKGROUND_BLUE|BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE)
#define IPURPLE (BACKGROUND_BLUE|BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define PURPLE (BACKGROUND_BLUE|BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED)
#define IBLACK (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|FOREGROUND_INTENSITY)
#define BACKGROUND (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED)
#define WHITE (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED| FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_GREEN)
#define IWHITE (BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED| FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define RAND_ICOLOR ((rand() % 8 + 8) | BACKGROUND)
#define RAND_COLOR ((rand()%16)|BACKGROUND)
enum Shape{check,hook,triangle,stick};
enum Color{black=BACKGROUND,iBlack=IBLACK,red=RED,iRed=IRED,yellow=YELLOW,iYellow=IYELLOW,green=GREEN,iGreen=IGREEN,cyan=CYAN,
			iCyan=ICYAN,blue=BLUE,iBlue=IBLUE,purple=PURPLE,iPurple=IPURPLE,iWhite=IWHITE};
enum Orientation{up,right,down,left};
typedef struct Tetris{
	int x, y;
	enum Shape tetrisShape;
	enum Color terisColor;
	enum Orientation tetrisOrientation;
}TETRIS;
typedef struct MyStruct2
{
	char name[MESSAGE_LEN];
	int score;
}RECORD;
extern int region[sizeX][sizeY];//表示界面的数组
void PrintStart(RECORD player, RECORD maxRecord);
void CreateBlock(TETRIS *block);
char RandColor(void);
DWORD WINAPI ThreadProc(LPVOID input);//接受消息的线程 
void MoveBlock(TETRIS *block,char *input);
BOOL IsOverlap(COORD spot[]);
BOOL IsCollision(const TETRIS *block);
BOOL IsLand(const TETRIS *block);
BOOL IsEmpty(const TETRIS *blcok,char direction);
void PrintBlock(const TETRIS *block);
void CloseBlock(const TETRIS *block);
void DownBlock(const TETRIS *block);
void SwapInt(int *a, int *b);
void SwapRecord(RECORD *a, RECORD *b);
void gotoxy(int x, int y);//将控制台坐标移动到坐标位置
void Print(int score);//刷新界面 主要为改变方块位置
void Check(int *score);//检查是否能够消除
void Clear(int y);//清除该行
void Refresh(void);//刷新界面 将清除的一层填上
int GameMain(RECORD player, RECORD record[]);//游戏主函数
void Menu(void);//显示菜单界面
void WriteRecord(RECORD record[]);//写入纪录
void ReadRecord(RECORD record[]);//读出纪录
void HideCursor(void);//隐藏控制台程序的光标
void CloseRegion(void);//清除界面数组信息

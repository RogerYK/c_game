#pragma once
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define up 72
#define left 75
#define down 80
#define right 77 
#define sizeX 40
#define sizeY 20
#define MESSAGE_LEN 20
typedef struct MyStruct
{
	int x, y;
	struct MyStruct *next;
}SNAKE;
typedef struct MyStruct2
{
	char name[MESSAGE_LEN];
	int score;
}RECORD;
void WriteRecord(RECORD record[]);//储存纪录
void ReadRecord(RECORD record[]);//读取纪录信息
void SwapRecord(RECORD *a, RECORD *b);//交换两条纪录
int GameMain(RECORD player, RECORD Record[]);
void gotoxy(int x, int y);//将控制台坐标移动到坐标位置
DWORD WINAPI ThreadProc(LPVOID direction);//接受消息的线程 

										  /*
										  控制蛇的行动
										  对接受的消息进行处理

										  */
BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score,void (*Type)(SNAKE* head,int stu[][sizeY]));
/*
初始化一个有四个节点表示蛇的链表
*/
SNAKE* CreatSnake(SNAKE *head);
/*新建一个节点添加到链表末尾*/
SNAKE *AppendNote(SNAKE *head, int x, int y);//创造一个节点
void DeleteMemorey(SNAKE *head);//释放head指向的内存
void Swap(int *a, int *b);//交换两个数的值 
void PrintStart(RECORD palyer, RECORD maxRecord);//打印初始界面
void HideCursor(void);//隐藏控制台光标
void Print(int stu[][sizeY], int *score);//打印界面 
void Common(SNAKE *head, int stu[][sizeY]);//普通类型的蛇
void Rainbow(SNAKE *head, int stu[][sizeY]);//彩虹蛇
void Special(SNAKE *head, int stu[][sizeY]);//炫彩
void Menu(void);//游戏主界面

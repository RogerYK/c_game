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
void WriteRecord(RECORD record[]);//�����¼
void ReadRecord(RECORD record[]);//��ȡ��¼��Ϣ
void SwapRecord(RECORD *a, RECORD *b);//����������¼
int GameMain(RECORD player, RECORD Record[]);
void gotoxy(int x, int y);//������̨�����ƶ�������λ��
DWORD WINAPI ThreadProc(LPVOID direction);//������Ϣ���߳� 

										  /*
										  �����ߵ��ж�
										  �Խ��ܵ���Ϣ���д���

										  */
BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score,void (*Type)(SNAKE* head,int stu[][sizeY]));
/*
��ʼ��һ�����ĸ��ڵ��ʾ�ߵ�����
*/
SNAKE* CreatSnake(SNAKE *head);
/*�½�һ���ڵ���ӵ�����ĩβ*/
SNAKE *AppendNote(SNAKE *head, int x, int y);//����һ���ڵ�
void DeleteMemorey(SNAKE *head);//�ͷ�headָ����ڴ�
void Swap(int *a, int *b);//������������ֵ 
void PrintStart(RECORD palyer, RECORD maxRecord);//��ӡ��ʼ����
void HideCursor(void);//���ؿ���̨���
void Print(int stu[][sizeY], int *score);//��ӡ���� 
void Common(SNAKE *head, int stu[][sizeY]);//��ͨ���͵���
void Rainbow(SNAKE *head, int stu[][sizeY]);//�ʺ���
void Special(SNAKE *head, int stu[][sizeY]);//�Ų�
void Menu(void);//��Ϸ������

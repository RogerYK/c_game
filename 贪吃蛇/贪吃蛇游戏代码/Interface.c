/**************************
******
***********
File name:              Interface.c
Author:                 袁坤
Version:				2.0
Date:					2016.1.6
Description:			打印游戏界面的函数文件
Others:
Function List:
1. void Menu(void)												菜单界面
2. void PrintStart(RECORD player, RECORD maxRecord)				游戏主界面
3. void Print(int stu[][sizeY], int *score)						刷新游戏时界面
4. void gotoxy(int x, int y);									将控制台坐标移动到坐标位置
5. void HideCursor(void)										隐藏控制台坐标
History:
1. Date:        Author:        Modification:

*************************************/
#include "Snake.h"
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			菜单界面
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Menu(void)
{
	system("cls");
	system("color 72");
	printf("程序名称：贪吃蛇\n版本：2.0\n开发者：袁坤\n班级：软工1613\n学号：8000116387\n");
	gotoxy(30, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("1. 开始游戏");
	gotoxy(30, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE);
	printf("2. 查看成绩");
	gotoxy(30, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
	printf("3. 退出游戏");
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			初始游戏界面
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void PrintStart(RECORD player, RECORD maxRecord)
{
	gotoxy(0, 0);
	printf("玩家：%s", player.name);
	gotoxy(25, 0);
	printf("目前得分：");
	gotoxy(45, 0);
	printf("历史最高:%s 得分：%d", maxRecord.name, maxRecord.score);
	gotoxy(0, 1);
	for (int i = 0; i < sizeX + 2; i++)
	{
		putchar('*');
	}
	for (int i = 0; i < sizeY; i++)
	{
		gotoxy(0, i + 2);
		putchar('*');
		gotoxy(sizeX + 1, i + 2);
		putchar('*');
	}
	gotoxy(0, sizeY + 2);
	for (int i = 0; i < sizeX + 2; i++)
	{
		putchar('*');
	}
	gotoxy(0, sizeY + 3);
	printf("用方向键控制蛇的方向，空格加速，z减速，x暂时速度变慢（按下任意键解除）");
	gotoxy(50, 3);
	printf("提示：游戏中按n会导致强退");
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			刷新游戏界面
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Print(int stu[][sizeY], int *score)
{
	int i, j;
	for (i = 0;i < sizeX;i++)
	{
		for (j = 0;j < sizeY;j++)
		{
			if (stu[i][j] == 1)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 2)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 3)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 4)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 5)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 6)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == 7)
			{
				gotoxy(i + 1, j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_INTENSITY);
				putchar('*');
			}
			else if (stu[i][j] == -1)
			{
				stu[i][j] = 0;
				gotoxy(i + 1, j + 2);
				putchar(' ');
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
	gotoxy(35, 0);
	printf("%d", *score);
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			使控制台程序坐标移动到指定位置（0，0）为最左上角
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			隐藏控制台程序坐标
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void HideCursor(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	return;
}

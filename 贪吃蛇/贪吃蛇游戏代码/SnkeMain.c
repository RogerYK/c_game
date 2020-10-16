/**************************
******
***********
File name:              SnakeMain.c
Author:                 袁坤	
Version:				2.0
Date:					2016.1.6
Description:			贪吃蛇的主程序，程序从这里开始
Others:         
Function List:  
1. void HideCursor(void);					隐藏控制台窗口光标
2. void Menu(void);							游戏主界面
3. void ReadRecord(RECORD record[]);		读取纪录信息
4. void gotoxy(int x, int y);				将控制台坐标移动到坐标位置
5. void SwapRecord(RECORD *a, RECORD *b);   交换两条纪录
6. void WriteRecord(RECORD record[]);       储存纪录
History:     
1. Date:        Author:        Modification:

*************************************/

#include "Snake.h"
int main()
{
	RECORD record[5] = { 0 };
	int choice = 1;
	RECORD player;
	HideCursor();
	while (1)
	{
		Menu();
		choice = getch();
		if (choice == '1')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
			system("cls");
			ReadRecord(record);
			gotoxy(26, 10);
			printf("请输入你的名字：");
			gets(player.name);
			player.score = GameMain(player, record);
			for (int i = 0; i < 5; i++)
			{
				if (player.score > record[i].score)
				{
					for (int j = i; j < 5; j++)
					{
						SwapRecord(&player, &record[j]);
					}
					break;
				}
			}
			WriteRecord(record);
			system("cls");
		}
		else if (choice == '2')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE);
			system("cls");
			ReadRecord(record);
			for (int i = 0; i < 5; i++)
			{
				if (0 != strlen(record[i].name))
				{
					gotoxy(20, 8 + i);
					printf("第%d名姓名%s \t成绩%d", i + 1, record[i].name, record[i].score);
				}
				else
				{
					gotoxy(20, 8 + i);
					printf("无");
				}
			}
			gotoxy(20, 13);
			printf("按任意键退出");
			getch();
			system("cls");
		}
		else if (choice == '3')
		{
			break;
		}
	}
	return 0;
}
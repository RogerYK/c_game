/**************************
******
***********
File name:              SnakeMain.c
Author:                 Ԭ��	
Version:				2.0
Date:					2016.1.6
Description:			̰���ߵ������򣬳�������￪ʼ
Others:         
Function List:  
1. void HideCursor(void);					���ؿ���̨���ڹ��
2. void Menu(void);							��Ϸ������
3. void ReadRecord(RECORD record[]);		��ȡ��¼��Ϣ
4. void gotoxy(int x, int y);				������̨�����ƶ�������λ��
5. void SwapRecord(RECORD *a, RECORD *b);   ����������¼
6. void WriteRecord(RECORD record[]);       �����¼
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
			printf("������������֣�");
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
					printf("��%d������%s \t�ɼ�%d", i + 1, record[i].name, record[i].score);
				}
				else
				{
					gotoxy(20, 8 + i);
					printf("��");
				}
			}
			gotoxy(20, 13);
			printf("��������˳�");
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
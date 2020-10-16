/**************************
******
***********
File name:              Interface.c
Author:                 Ԭ��
Version:				2.0
Date:					2016.1.6
Description:			��ӡ��Ϸ����ĺ����ļ�
Others:
Function List:
1. void Menu(void)												�˵�����
2. void PrintStart(RECORD player, RECORD maxRecord)				��Ϸ������
3. void Print(int stu[][sizeY], int *score)						ˢ����Ϸʱ����
4. void gotoxy(int x, int y);									������̨�����ƶ�������λ��
5. void HideCursor(void)										���ؿ���̨����
History:
1. Date:        Author:        Modification:

*************************************/
#include "Snake.h"
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			�˵�����
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Menu(void)
{
	system("cls");
	system("color 72");
	printf("�������ƣ�̰����\n�汾��2.0\n�����ߣ�Ԭ��\n�༶����1613\nѧ�ţ�8000116387\n");
	gotoxy(30, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("1. ��ʼ��Ϸ");
	gotoxy(30, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE);
	printf("2. �鿴�ɼ�");
	gotoxy(30, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
	printf("3. �˳���Ϸ");
	return;
}
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			��ʼ��Ϸ����
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void PrintStart(RECORD player, RECORD maxRecord)
{
	gotoxy(0, 0);
	printf("��ң�%s", player.name);
	gotoxy(25, 0);
	printf("Ŀǰ�÷֣�");
	gotoxy(45, 0);
	printf("��ʷ���:%s �÷֣�%d", maxRecord.name, maxRecord.score);
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
	printf("�÷���������ߵķ��򣬿ո���٣�z���٣�x��ʱ�ٶȱ�������������������");
	gotoxy(50, 3);
	printf("��ʾ����Ϸ�а�n�ᵼ��ǿ��");
	return;
}
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			ˢ����Ϸ����
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			ʹ����̨���������ƶ���ָ��λ�ã�0��0��Ϊ�����Ͻ�
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			���ؿ���̨��������
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

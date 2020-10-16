#include "Tetris.h"
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
	char color;
	do {
		color = (rand() % 16) | BACKGROUND;
	} while (color == WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	system("cls");
	gotoxy(0, 0);
	printf("��ң�%s", player.name);
	gotoxy(25, 0);
	printf("Ŀǰ�÷֣�");
	gotoxy(45, 0);
	printf("��ʷ���:%s �÷֣�%d", maxRecord.name, maxRecord.score);
	gotoxy(0, 1);
	for (int i = 0; i < sizeX + 2; i++)
	{
		printf("��");
	}
	for (int i = 0; i < sizeY; i++)
	{
		gotoxy(0, i + 2);
		printf("��");
		gotoxy(2 * (sizeX + 1), i + 2);
		printf("��");
	}
	gotoxy(0, sizeY + 2);
	for (int i = 0; i < sizeX + 2; i++)
	{
		printf("��");
	}
	gotoxy(50, 5);
	printf("��n�����˳���Ϸ");
	gotoxy(45, 6);
	printf("��������Ʒ����ƶ����ո�ʹ������ת");
}
/*���������Ϣ*/
void CloseRegion(void)
{
	for (int i = 0;i < sizeX;i++)
	{
		for (int j = 0;j < sizeY;j++)
		{
			region[i][j] = 0;
		}
	}
}
/*ˢ�½���*/
void Print(int score)
{
	int i, j;
	for (i = 0;i < sizeX;i++)
	{
		for (j = 0;j < sizeY;j++)
		{
			if (region[i][j] != 0)
			{
				if (region[i][j] == -1)
				{
					gotoxy(2 * (i + 1), j + 2);
					printf(" ");
					region[i][j] = 0;
				}
				else
				{
					gotoxy(2 * (i + 1), j + 2);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), region[i][j]);
					printf("��");
				}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
	gotoxy(35, 0);
	printf("%d", score);
	return;
}
/*����һ���������ɫ*/
char RandColor(void)
{
	char color;
	do
	{
		color = RAND_COLOR;
	} while (color==WHITE);
	return color;
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
/*��ӡ����*/
void PrintBlock(const TETRIS *block)
{
	switch (block->tetrisShape)
	{
	case check:                                     //check
		if(block->y>=0)
		region[block->x][block->y] = block->terisColor;
		if (block ->y>= 0)
		region[block->x + 1][block->y] = block->terisColor;
		if (block->y-1>= 0)
		region[block->x][block->y - 1] = block->terisColor;
		if (block ->y-1>= 0)
		region[block->x + 1][block->y - 1] = block->terisColor;
		break;
	case hook:                                      //hook
		switch (block->tetrisOrientation)
		{
		case up:
			if (block ->y>= 0)
			region[block->x][block->y] = block->terisColor;             
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;	
			if (block->y-1 >= 0)
			region[block->x + 1][block->y - 1] = block->terisColor;		
			break;
		case right:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			   
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;			
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = block->terisColor;			
			if (block->y+1 >= 0)
			region[block->x + 1][block->y + 1] = block->terisColor;		
			break;
		case down:
			if (block ->y>= 0)
			region[block->x][block->y] = block->terisColor;				
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;			
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;			
			if (block->y+1 >= 0)
			region[block->x - 1][block->y + 1] = block->terisColor;		
			break;
		case left:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;				
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;			
			if (block->y-1 >= 0)
			region[block->x - 1][block->y - 1] = block->terisColor;		
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = block->terisColor;			
			break;
		default:
			break;
		}
		break;
	case triangle:                                             //triangle
		switch (block->tetrisOrientation)
		{
		case up:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;		
			break;
		case right:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;		
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;		
			if (block->y+1>= 0)
			region[block->x][block->y + 1] = block->terisColor;		
			break;
		case down:
			if (block->y>= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y>= 0)
			region[block->x + 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;		
			if (block->y+1>= 0)
			region[block->x][block->y + 1] = block->terisColor;		
			break;
		case left:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;		
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = block->terisColor;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;		
			break;
		default:
			break;
		}
		break;
	case stick:                                  //stick
		switch (block->tetrisOrientation)
		{
		case up:
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x + 2][block->y] = block->terisColor;		
			break;
		case right:
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;		
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = block->terisColor;		
			if (block->y+2 >= 0)
			region[block->x][block->y + 2] = block->terisColor;		
			break;
		case down:
			if (block->y >= 0)
			region[block->x + 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y >= 0)
			region[block->x - 1][block->y] = block->terisColor;		
			if (block->y >= 0)
			region[block->x - 2][block->y] = block->terisColor;		
			break;
		case left:
			if (block->y >= 0)
			region[block->x][block->y] = block->terisColor;			
			if (block->y+1>= 0)
			region[block->x][block->y + 1] = block->terisColor;		
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = block->terisColor;		
			if (block->y-2>= 0)
			region[block->x][block->y - 2] = block->terisColor;		//	*    ture
			break;
		}
		break;
	}
	return;
}
/*����������Ϣ*/
void CloseBlock(const TETRIS *block)
{
	switch (block->tetrisShape)
	{
	case check:                                     //check
		if (block->y >= 0)
		region[block->x][block->y] = -1;				
		if (block->y >= 0)
		region[block->x + 1][block->y] = -1;			
		if (block->y-1 >= 0)
		region[block->x][block->y - 1] = -1;
		if (block->y-1 >= 0)
		region[block->x + 1][block->y - 1] = -1;		
		break;
	case hook:                                      //hook
		switch (block->tetrisOrientation)
		{
		case up:
			if (block->y >= 0)
			region[block->x][block->y] = -1;           
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;			
			if (block->y >= 0)
			region[block->x + 1][block->y] = -1;			
			if (block->y-1 >= 0)
			region[block->x + 1][block->y - 1] = -1;		
			break;
		case right:
			if (block->y>= 0)
			region[block->x][block->y] = -1;			   
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = -1;			
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = -1;			
			if (block->y+1 >= 0)
			region[block->x + 1][block->y + 1] = -1;		
			break;
		case down:
			if (block->y >= 0)
			region[block->x][block->y] = -1;				
			if (block->y >= 0)
			region[block->x + 1][block->y] = -1;			
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;			
			if (block->y+1 >= 0)
			region[block->x - 1][block->y + 1] = -1;		
			break;
		case left:
			if (block->y >= 0)
			region[block->x][block->y] = -1;				
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = -1;			
			if (block->y-1 >= 0)
			region[block->x - 1][block->y - 1] = -1;		
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = -1;
			break;
		}
		break;
	case triangle:                                             //triangle
		switch (block->tetrisOrientation)
		{
		case up:
			if (block->y >= 0)
			region[block->x][block->y] = -1;			
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = -1;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;		
			if (block->y >= 0)
			region[block->x + 1][block->y] = -1;
			break;
		case right:
			if (block->y >= 0)
			region[block->x][block->y] = -1;			
			if (block->y >= 0)
			region[block->x + 1][block->y] = -1;		
			if (block->y-1 >= 0)
			region[block->x][block->y - 1] = -1;		
			if (block->y+1 >= 0)
			region[block->x][block->y + 1] = -1;		
			break;
		case down:
			if (block->y >= 0)
			region[block->x][block->y] = -1;			
			if (block->y>= 0)
			region[block->x + 1][block->y] = -1;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;		
			if (block->y + 1 >= 0)
			region[block->x][block->y + 1] = -1;		
			break;
		case left:
			if (block->y>= 0)
			region[block->x][block->y] = -1;		
			if (block->y - 1 >= 0)
			region[block->x][block->y - 1] = -1;		
			if (block->y + 1 >= 0)
			region[block->x][block->y + 1] = -1;		
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;		
			break;
		default:
			break;
		}
		break;
	case stick:                                  //stick
		switch (block->tetrisOrientation)
		{
		case up:
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;		
			if (block->y>= 0)
			region[block->x][block->y] = -1;		
			if (block->y>= 0)
			region[block->x + 1][block->y] = -1;		
			if (block->y >= 0)
			region[block->x + 2][block->y] = -1;		
			break;
		case right:
			if (block->y -1 >= 0)
			region[block->x][block->y - 1] = -1;	
			if (block->y  >= 0)
			region[block->x][block->y] = -1;			
			if (block->y + 1 >= 0)
			region[block->x][block->y + 1] = -1;		
			if (block->y + 2>= 0)
			region[block->x][block->y + 2] = -1;		
			break;
		case down:
			if (block->y>= 0)
			region[block->x + 1][block->y] = -1;		
			if (block->y>= 0)
			region[block->x][block->y] = -1;			
			if (block->y >= 0)
			region[block->x - 1][block->y] = -1;		
			if (block->y >= 0)
			region[block->x - 2][block->y] = -1;		
			break;
		case left:
			if (block->y >= 0)
			region[block->x][block->y] = -1;			
			if (block->y + 1 >= 0)
			region[block->x][block->y + 1] = -1;		
			if (block->y - 1 >= 0)
			region[block->x][block->y - 1] = -1;		
			if (block->y -2 >= 0)
			region[block->x][block->y - 2] = -1;		
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return;
}
void Refresh(void)
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (region[i][j]!=0&&region[i][j]!=-1)
			{
				gotoxy(2 * (i + 1), j + 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), region[i][j]);
				printf("��");
			}
			else if (region[i][j] == 0||region[i][j]==-1)
			{
				gotoxy(2 * (i + 1), j + 2);
				printf(" ");
			}
		}
	}
	return;
}
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
	gotoxy(35, 10);
	printf("1. ��ʼ��Ϸ");
	gotoxy(35, 11);
	printf("2. �鿴�ɼ�");
	gotoxy(35, 12);
	printf("3. �˳���Ϸ");
	return;
}
/*���ؿ���̨�Ĺ��*/
void HideCursor(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	return;
}
/*�������һ��ˢ�½���*/
void Clear(int y)
{
	for (int i = 0; i < sizeX; i++)
	{
		gotoxy(2 * (i + 1), y + 2);
		printf(" ");
	}
	for (int i = y; i >0; i--)
	{
		for (int j = 0; j < sizeX; j++)
		{
			region[j][i] = region[j][i - 1];
		}
	}
	for (int i = 0; i < sizeX; i++)
	{
		region[i][0] = 0;
	}
	Refresh();
	return;
}


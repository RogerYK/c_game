#include "Tetris.h"
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
	char color;
	do {
		color = (rand() % 16) | BACKGROUND;
	} while (color == WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	system("cls");
	gotoxy(0, 0);
	printf("玩家：%s", player.name);
	gotoxy(25, 0);
	printf("目前得分：");
	gotoxy(45, 0);
	printf("历史最高:%s 得分：%d", maxRecord.name, maxRecord.score);
	gotoxy(0, 1);
	for (int i = 0; i < sizeX + 2; i++)
	{
		printf("■");
	}
	for (int i = 0; i < sizeY; i++)
	{
		gotoxy(0, i + 2);
		printf("■");
		gotoxy(2 * (sizeX + 1), i + 2);
		printf("■");
	}
	gotoxy(0, sizeY + 2);
	for (int i = 0; i < sizeX + 2; i++)
	{
		printf("■");
	}
	gotoxy(50, 5);
	printf("按n即可退出游戏");
	gotoxy(45, 6);
	printf("方向键控制方块移动，空格使方块旋转");
}
/*清除界面信息*/
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
/*刷新界面*/
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
					printf("■");
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
/*返回一个随机的颜色*/
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
/*打印方块*/
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
/*清除方块的信息*/
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
				printf("■");
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
	gotoxy(35, 10);
	printf("1. 开始游戏");
	gotoxy(35, 11);
	printf("2. 查看成绩");
	gotoxy(35, 12);
	printf("3. 退出游戏");
	return;
}
/*隐藏控制台的光标*/
void HideCursor(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	return;
}
/*清除满的一行刷新界面*/
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


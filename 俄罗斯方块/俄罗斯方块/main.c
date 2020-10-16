#include "Tetris.h"
int region[sizeX][sizeY];
int GameMain(RECORD player,RECORD record[])
{
	TETRIS block;
	int score=0;
	char input = 0;//储存用户输入
	PrintStart(player,record[0]);
	CreateThread(NULL, 0, ThreadProc, &input, 0, NULL);
	CreateBlock(&block);
	while (1)//游戏循环
	{
		MoveBlock(&block, &input);
		PrintBlock(&block);
		Print(score);
		CloseBlock(&block);
		if (!IsEmpty(&block, DOWN))
		{
			if (!IsEmpty(&block,UP))
			{
				break;
			}
			PrintBlock(&block);
			CreateBlock(&block);
			Check(&score);
			input = 0;
			continue;
		}
		if (input != DOWN)
		{
			Sleep(800);
		}
		if (input == 'n' || input == 'N')
		{
			break;
		}
	}
	system("cls");
	CloseRegion();
	if (score > record[0].score)
	{
		gotoxy(36, 8);
		printf("恭喜打破纪录！");
	}
	gotoxy(36, 9);
	printf("你本次的成绩为%d", score);
	gotoxy(36, 10);
	printf("请按n退出");
	for (;;)
	{
		if (input == 'n'||input == 'N')
			break;
		Sleep(200);
	}
	Sleep(2000);
	return score;
}
int main()
{
	RECORD record[5] = { 0 };
	int choice = 1;
	RECORD player;
	HideCursor();
	system("mode con cols=80 lines=32  ");
	srand(time(NULL));
	while (1)
	{
		Menu();
		choice = getch();
		if (choice == '1')
		{
			system("cls");
			ReadRecord(record);
			gotoxy(35, 10);
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
			system("cls");
			ReadRecord(record);
			for (int i = 0; i < 5; i++)
			{
				if (0 != strlen(record[i].name))
				{
					gotoxy(35, 8 + i);
					printf("第%d名姓名%s \t成绩%d", i + 1, record[i].name, record[i].score);
				}
				else
				{
					gotoxy(35, 8 + i);
					printf("无");
				}
			}
			gotoxy(35, 13);
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
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.13
Description:			用来接受用户输入的线程
Others:					当接受到n时退出线程
History:
1. Date:        Author:        Modification:
*************************************************/
DWORD WINAPI ThreadProc(LPVOID input)//接受消息
{
	char *inpu= (char *)input;
	while (1)
	{
		*inpu = getch();
		if ('n' == *inpu || 'N' == *inpu)
		{
			break;
		}
	}
	return 0;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.13
Description:			随机方块的各个属性
Others:				
History:
1. Date:        Author:        Modification:
*************************************************/
void CreateBlock(TETRIS *block)
{
	block->x = rand() % 4+2;
	block->y = -3;
	block->terisColor =RandColor();
	block->tetrisOrientation = rand() % 4;
	block->tetrisShape = rand() % 4;
	return;
}
/*移动方块的位置*/
void MoveBlock(TETRIS *block,  char *input)
{
	char direction=0;
	if (*input==LEFT||*input==RIGHT||*input==' ')
	{
		direction = *input;
	}
	if (direction&&IsEmpty(block,direction))
	{
		switch (direction)
		{
		case LEFT:
			(block->x)--;
			break;
		case RIGHT:
			(block->x)++;
			break;
		case ' ':
			if (!IsCollision(block))
			{
				block->tetrisOrientation = (block->tetrisOrientation + 1) % 4;
			}
			break;
		default:
			break;
		}
		*input = 0;
	}
	else
	{
		block->y++;
	}
	return;
}
/*判断按方向移动后是否出界或碰撞*/
BOOL IsEmpty(const TETRIS *block, char direction)
{
	COORD spot[4]={0};
	switch (block->tetrisShape)
	{
	case check:                                     //check
		spot[0].X = block->x, spot[0].Y = block->y;
		spot[1].X = block->x + 1, spot[1].Y=block->y; 
		spot[2].X = block->x, spot[2].Y=block->y - 1;
		spot[3].X = block->x + 1, spot[3].Y = block->y- 1;          
		break;
	case hook:                                      //hook
		switch (block->tetrisOrientation)
		{
		case up:
			spot[0].X = block->x, spot[0].Y = block->y;
			spot[1].X=block->x - 1,spot[1].Y=block->y;
			spot[2].X=block->x + 1,spot[2].Y= block->y;
			spot[3].X=block->x + 1,spot[3].Y=block->y - 1;
			break;
		case right:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x, spot[1].Y = block->y-1;                                         //region[block->x][block->y - 1] = 1;
			spot[2].X = block->x, spot[2].Y = block->y + 1;					//region[block->x][block->y + 1] = 1;
			spot[3].X = block->x + 1, spot[3].Y = block->y + 1;							//region[block->x + 1][block->y + 1] = 1;
			break;
		case down:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x + 1, spot[1].Y = block->y;           //region[block->x + 1][block->y] = 1;
			spot[2].X = block->x - 1, spot[2].Y = block->y;              //region[block->x - 1][block->y] = 1;
			spot[3].X = block->x - 1, spot[3].Y = block->y + 1;              //region[block->x - 1][block->y + 1] = 1;
			break;
		case left:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x, spot[1].Y = block->y - 1;                                        //region[block->x][block->y - 1] = 1;
			spot[2].X = block->x - 1, spot[2].Y = block->y - 1;              //region[block->x - 1][block->y - 1] = 1;
			spot[3].X = block->x, spot[3].Y = block->y + 1;              //region[block->x][block->y + 1] = 1;
			break;
		}
		break;
	case triangle:                                             //triangle
		switch (block->tetrisOrientation)
		{
		case up:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x, spot[1].Y = block->y-1;    
			spot[2].X = block->x - 1, spot[2].Y = block->y;   
			spot[3].X = block->x + 1, spot[3].Y = block->y;   
			break;
		case right:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x + 1, spot[1].Y = block->y;  
			spot[2].X = block->x, spot[2].Y = block->y - 1;
			spot[3].X = block->x, spot[3].Y = block->y + 1; 
			break;
		case down:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x + 1, spot[1].Y = block->y; 
			spot[2].X = block->x - 1;spot[2].Y = block->y; 
			spot[3].X = block->x, spot[3].Y = block->y + 1; 
			break;
		case left:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x, spot[1].Y = block->y - 1;  
			spot[2].X = block->x, spot[2].Y = block->y + 1;  
			spot[3].X = block->x-1, spot[3].Y = block->y;  
			break;
		default:
			break;
		}
		break;
	case stick:                                  //stick
		switch (block->tetrisOrientation)
		{
		case up:
			spot[1].X = block->x - 1, spot[1].Y = block->y; 
			spot[0].X=block->x,       spot[0].Y=block->y;
			spot[2].X = block->x + 1, spot[2].Y = block->y;  
			spot[3].X = block->x + 2, spot[3].Y = block->y;  
			break;
		case right:
			spot[1].X = block->x, spot[1].Y = block->y-1;  
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[2].X = block->x, spot[2].Y = block->y+1;  
			spot[3].X = block->x, spot[3].Y = block->y+2; 
			break;
		case down:
			spot[1].X = block->x + 1, spot[1].Y = block->y;  
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[2].X = block->x - 1, spot[2].Y = block->y;  
			spot[3].X = block->x - 2, spot[3].Y = block->y;  
			break;
		case left:
			spot[0].X=block->x,spot[0].Y=block->y;
			spot[1].X = block->x, spot[1].Y = block->y+1;  
			spot[2].X = block->x, spot[2].Y = block->y-1;  
			spot[3].X = block->x, spot[3].Y = block->y-2; 
			break;
		}
		break;
	}
	switch (direction)
	{
	case LEFT:
		for (int i = 0; i < 4; i++)
		{
			spot[i].X--;
		}
		break;
	case RIGHT:
		for (int i = 0; i < 4; i++)
		{
			spot[i].X++;
		}
		break;
	case DOWN:
		for (int i = 0; i < 4; i++)
		{
			spot[i].Y++;
		}
		break;
	case UP:
		for (int i = 0; i < 4; i++)
		{
			spot[i].Y--;
		}
		for (int i = 0; i < 4; i++)
		{
			if (spot[i].Y < 0)
				return FALSE;
		}
		break;
	}
	if (!IsOverlap(spot))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/*判断点是否超出界面或与界面已有方块重叠*/
BOOL IsOverlap(COORD spot[])
{
	
	for (int i = 0; i < 4; i++)
	{
		if (spot[i].X>=0&&spot[i].X<sizeX&&spot[i].Y>=0&&spot[i].Y<sizeY)
		{
			if (region[spot[i].X][spot[i].Y] != 0 && region[spot[i].X][spot[i].Y] != -1)
				return TRUE;
		}
		else
		{
			if (spot[i].Y > 0)
				return TRUE;
		}
	}
	return FALSE;
}
BOOL IsCollision(const TETRIS *block)
{
	TETRIS tempBlock = *block;
	tempBlock.tetrisOrientation = (tempBlock.tetrisOrientation + 1) % 4;
	if (!IsEmpty(&tempBlock,0))
	{
		return TRUE;
	}
	return FALSE;
}
void Check(int *score)
{
	for (int i =sizeY-1; i >=0; i--)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (region[j][i]==0)
			{
				break;
			}
			else if (j==sizeX-1)
			{
				(*score)++;
				Clear(i);
				Check(score);
				return;
			}
		}
	}
	return;
}

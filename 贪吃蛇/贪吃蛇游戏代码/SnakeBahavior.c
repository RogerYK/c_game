/**************************
File name:						SnakeBahavior.c
Author:							袁坤 
Version:						2.0
Date:							2016.1.6
Description:					游戏的主要逻辑
Others:							
Function List: 
1. int GameMain(RECORD player, RECORD maxRecord[])			游戏的主体函数
2. BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score, void(*Type)(SNAKE *head, int stu[][sizeY])) 控制蛇的行动
3. DWORD WINAPI ThreadProc(LPVOID direction)						不断循环接受消息的线程
4. void Common(SNAKE *head, int stu[][sizeY])						作为CrawlSnake的参数，普通颜色的蛇
5. void Rainbow(SNAKE *head, int stu[][sizeY])                      作为CrawlSnake的参数，蛇颜色为彩虹
6. void Special(SNAKE *head, int stu[][sizeY])                      作为CrawlSnake的参数，蛇颜色为炫彩
History:      
1. Date:        Author:        Modification:
*************************************************/
#include "Snake.h"
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			游戏的主体函数
Others:					数组大小默认为5
History:
1. Date:        Author:        Modification:
*************************************************/
int GameMain(RECORD player, RECORD Record[])
{
	int stu[sizeX][sizeY] = { 0 };//表示界面的数组
	int direction = up;//表示方向的变量
	int score = 0;
	SNAKE *head = NULL;
	BOOL hp = 1;
	unsigned int t = 600;
	HANDLE hThread;
	char choice;
	system("cls");
	srand(time(NULL));
	gotoxy(30, 9);
	printf("选一种蛇");
	gotoxy(30, 10);
	printf("1.普通");
	gotoxy(30, 11);
	printf("2.彩虹");
	gotoxy(30, 12);
	printf("3.炫彩");
	do
	{
		choice = getch();
	} while (choice>'3'||choice<'1');
	system("cls");
	hThread = CreateThread(NULL, 0, ThreadProc, &direction, 0, NULL);//创造一个接受消息线程
AGAIN:
	t = 600;
	head = CreatSnake(head);
	PrintStart(player, Record[0]);
	while (1)
	{
		
		if (choice=='1')
		{
			hp = CrawlSnake(&direction, head, stu, &score,Common);
		}
		else if (choice=='2')
		{
			hp = CrawlSnake(&direction, head, stu, &score,Rainbow);
		}
		else if (choice=='3')
		{
			hp = CrawlSnake(&direction, head, stu, &score,Special);
		}
		if (1 != hp)
		{
			break;
		}
		Print(stu, &score);
		Sleep(t);
		if (' ' == direction)
		{
			t = (t / 3) * 2;
			direction = 0;
		}
		else if ('z' == direction || 'Z' == direction)
		{
			if (t != 0)
			{
				t = t * 2;
			}
			else
				t++;
			direction = 0;
		}
		else if ('x' == direction || 'X' == direction)
		{
			Sleep(1000);
		}

	}
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			stu[i][j] = 0;
		}
	}
	system("cls");
	if (score > Record[0].score)
	{
		gotoxy(20, 9);
		printf("恭喜打破纪录退出可使纪录保存");
	}
	else if (score>Record[4].score)
	{
		gotoxy(20, 9);
		printf("恭喜进入排名退出可使成绩保存");
	}
	else
	{
		gotoxy(20, 9);
		printf("尚未进入排名，加油！");
	}
	gotoxy(20, 10);
	printf("是否继续游戏(y/n)");
	for (;;)
	{
		if ('y' == direction || 'Y' == direction)
		{
			system("cls");
			score = 0;
			goto AGAIN;
		}
		else if ('n' == direction || 'N' == direction)
		{
			break;
		}
		Sleep(100);
	}
	DeleteMemorey(head);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return score;
}

/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			根据接受的消息对表示蛇的链表进行处理，并根据链表对表示界面的数组处理
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score, void(*Type)(SNAKE *head, int stu[][sizeY]))
{
	static int foodx = -1, foody = -1;//食物坐标 
	static int direc1, direc2 = up;//direc2代表当前方向，direc1代表接受到方向 
	int headx, heady;//蛇头坐标 
	int tempx, tempy;
	SNAKE*pr = head, *p = NULL;
	static int color;
	if (-1 == foodx || -1 == foody)
	{
		foodx = rand() % sizeX;
		foody = rand() % sizeY;
		color = rand() % 7 + 1;
	}
	if (head == NULL)
	{
		printf("Don't find SNAKE'");
		exit(0);
	}
	headx = head->x, heady = head->y;
	direc1 = *direction;
	if (up == direc2)//根据方向改变蛇头 
	{
		switch (direc1)
		{
		case up:
			(head->y)--;
			break;
		case left:
			(head->x)--;
			direc2 = left;
			break;
		case right:
			(head->x)++;
			direc2 = right;
			break;
		default:
			(head->y)--;
			break;
		}
	}
	else if (left == direc2)
	{
		switch (direc1)
		{
		case up:
			(head->y)--;
			direc2 = up;
			break;
		case left:
			(head->x)--;
			direc2 = left;
			break;
		case down:
			(head->y)++;
			direc2 = down;
			break;
		default:
			(head->x)--;
			break;
		}
	}
	else if (down == direc2)
	{
		switch (direc1)
		{
		case left:
			(head->x)--;
			direc2 = left;
			break;
		case right:
			(head->x)++;
			direc2 = right;
			break;
		case down:
			(head->y)++;
			direc2 = down;
			break;
		default:
			(head->y)++;
			break;
		}
	}
	else if (right == direc2)
	{
		switch (direc1)
		{
		case right:
			(head->x)++;
			direc2 = right;
			break;
		case up:
			(head->y)--;
			direc2 = up;
			break;
		case down:
			(head->y)++;
			direc2 = down;
			break;
		default:
			(head->x)++;
			break;
		}
	}
	pr = head;
	tempx = headx, tempy = heady;
	do {
		pr = pr->next;
		Swap(&tempx, &(pr->x));
		Swap(&tempy, &(pr->y));

	} while (NULL != pr->next);
	stu[tempx][tempy] = -1;
	(*Type)(head, stu);
	if (foodx != -1 && foody != -1)
	{
		stu[foodx][foody] =color;
	}
	pr = head;
	headx = head->x, heady = head->y;
	if (headx < 0 || headx >= sizeX || heady < 0 || heady >= sizeY)//判断是否过界
	{
		direc2 = up;
		return 2;
	}
	do {
		pr = pr->next;
		if (headx == pr->x&&heady == pr->y)//判断蛇头是否与自身接触
		{
			direc2 = up;
			return 3;
		}

	} while (pr->next != NULL);
	if (headx == foodx&&heady == foody)//判断是否吃到食物
	{
		//putchar(7);
		(*score)++;
		foodx = -1;
		foody = -1;
		AppendNote(head, headx, heady);
	}
	return TRUE;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			用来接受用户输入的线程
Others:					当接受到n时退出线程
History:		
1. Date:        Author:        Modification:
*************************************************/
DWORD WINAPI ThreadProc(LPVOID direction)//接受消息
{
	int *dire = (int *)direction;
	while (1)
	{
		*dire = getch();
		if ('n' == *dire || 'N' == *dire)
		{
			break;
		}
	}
	return 0;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			使界面上的蛇为普通的颜色，每分钟变换颜色
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Common(SNAKE *head, int stu[][sizeY])
{
	SNAKE *pr = head;
	DWORD time= GetTickCount()/60000;
	int color = time % 7 + 1;
	if (NULL==pr)
	{
		exit(0);
	}
	stu[pr->x][pr->y] = color;
	do
	{
		pr = pr->next;
		stu[pr->x][pr->y] = color;
	} while (NULL!=pr->next);
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			使界面上的蛇为顺序的六种颜色
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Rainbow(SNAKE *head, int stu[][sizeY])
{
	SNAKE *pr = head;
	int color=1;
	if (NULL==pr)
	{
		exit(0);
	}
	stu[pr->x][pr->y] = 1;
	while (NULL!=pr->next)
	{
		pr = pr->next;
		stu[pr->x][pr->y] = (color++)%6 + 1;
	}
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			使界面上的蛇为随机的颜色
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Special(SNAKE *head, int stu[][sizeY])
{
	SNAKE *pr = head;
	if (NULL == pr)
	{
		exit(0);
	}
	stu[pr->x][pr->y] = 1;
	while (NULL != pr->next)
	{
		pr = pr->next;
		stu[pr->x][pr->y] = rand() % 6 + 1;
	}
	return;
}

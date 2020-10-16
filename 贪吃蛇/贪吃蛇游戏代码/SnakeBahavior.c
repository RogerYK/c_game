/**************************
File name:						SnakeBahavior.c
Author:							Ԭ�� 
Version:						2.0
Date:							2016.1.6
Description:					��Ϸ����Ҫ�߼�
Others:							
Function List: 
1. int GameMain(RECORD player, RECORD maxRecord[])			��Ϸ�����庯��
2. BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score, void(*Type)(SNAKE *head, int stu[][sizeY])) �����ߵ��ж�
3. DWORD WINAPI ThreadProc(LPVOID direction)						����ѭ��������Ϣ���߳�
4. void Common(SNAKE *head, int stu[][sizeY])						��ΪCrawlSnake�Ĳ�������ͨ��ɫ����
5. void Rainbow(SNAKE *head, int stu[][sizeY])                      ��ΪCrawlSnake�Ĳ���������ɫΪ�ʺ�
6. void Special(SNAKE *head, int stu[][sizeY])                      ��ΪCrawlSnake�Ĳ���������ɫΪ�Ų�
History:      
1. Date:        Author:        Modification:
*************************************************/
#include "Snake.h"
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			��Ϸ�����庯��
Others:					�����СĬ��Ϊ5
History:
1. Date:        Author:        Modification:
*************************************************/
int GameMain(RECORD player, RECORD Record[])
{
	int stu[sizeX][sizeY] = { 0 };//��ʾ���������
	int direction = up;//��ʾ����ı���
	int score = 0;
	SNAKE *head = NULL;
	BOOL hp = 1;
	unsigned int t = 600;
	HANDLE hThread;
	char choice;
	system("cls");
	srand(time(NULL));
	gotoxy(30, 9);
	printf("ѡһ����");
	gotoxy(30, 10);
	printf("1.��ͨ");
	gotoxy(30, 11);
	printf("2.�ʺ�");
	gotoxy(30, 12);
	printf("3.�Ų�");
	do
	{
		choice = getch();
	} while (choice>'3'||choice<'1');
	system("cls");
	hThread = CreateThread(NULL, 0, ThreadProc, &direction, 0, NULL);//����һ��������Ϣ�߳�
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
		printf("��ϲ���Ƽ�¼�˳���ʹ��¼����");
	}
	else if (score>Record[4].score)
	{
		gotoxy(20, 9);
		printf("��ϲ���������˳���ʹ�ɼ�����");
	}
	else
	{
		gotoxy(20, 9);
		printf("��δ�������������ͣ�");
	}
	gotoxy(20, 10);
	printf("�Ƿ������Ϸ(y/n)");
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			���ݽ��ܵ���Ϣ�Ա�ʾ�ߵ�������д�������������Ա�ʾ��������鴦��
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
BOOL CrawlSnake(int *direction, SNAKE *head, int stu[][sizeY], int *score, void(*Type)(SNAKE *head, int stu[][sizeY]))
{
	static int foodx = -1, foody = -1;//ʳ������ 
	static int direc1, direc2 = up;//direc2����ǰ����direc1������ܵ����� 
	int headx, heady;//��ͷ���� 
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
	if (up == direc2)//���ݷ���ı���ͷ 
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
	if (headx < 0 || headx >= sizeX || heady < 0 || heady >= sizeY)//�ж��Ƿ����
	{
		direc2 = up;
		return 2;
	}
	do {
		pr = pr->next;
		if (headx == pr->x&&heady == pr->y)//�ж���ͷ�Ƿ�������Ӵ�
		{
			direc2 = up;
			return 3;
		}

	} while (pr->next != NULL);
	if (headx == foodx&&heady == foody)//�ж��Ƿ�Ե�ʳ��
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			���������û�������߳�
Others:					�����ܵ�nʱ�˳��߳�
History:		
1. Date:        Author:        Modification:
*************************************************/
DWORD WINAPI ThreadProc(LPVOID direction)//������Ϣ
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			ʹ�����ϵ���Ϊ��ͨ����ɫ��ÿ���ӱ任��ɫ
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			ʹ�����ϵ���Ϊ˳���������ɫ
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			ʹ�����ϵ���Ϊ�������ɫ
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

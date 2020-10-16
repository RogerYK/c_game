/**************************
File name:							DataManipulation.c
Author:								袁坤
Version:							2.0
Date:								2016.1.6
Description:						进行数据处理方面的函数// 用于详细说明此程序文件完成的主要功能
Others:                             
Function List:  
1. void ReadRecord(RECORD record[]);		读取纪录信息
2. void WriteRecord(RECORD record[]);       储存纪录
3. void SwapRecord(RECORD *a, RECORD *b);   交换两条纪录
4. void DeleteMemorey(SNAKE *head);			释放head指向的内存
5. SNAKE* CreatSNAKE(SNAKE *head);			创建一个有四个节点的的链表
6. SNAKE *AppendNote(SNAKE *head, int x, int y) 添加一个节点到链表末尾
History:    
1. Date:        Author:        Modification:
2
*************************************************/
#include "Snake.h"
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			储存纪录文件
Others:					recore数组默认为5
History:      
1. Date:        Author:        Modification:
*************************************************/
void WriteRecord(RECORD record[])
{
	FILE *fp;
	fp = fopen("Snake.bin", "w");
	if (fp == NULL)
	{
		printf("储存纪录失败");
		return;
	}
	fwrite(record, sizeof(RECORD), 5, fp);
	fclose(fp);
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			读取文件信息
Others:					recore数组默认为5
History:
1. Date:        Author:        Modification:
*************************************************/
void ReadRecord(RECORD record[])
{
	FILE *fp;
	fp = fopen("Snake.bin", "r");
	if (fp == NULL)
	{
		return;
	}
	fread(record, sizeof(RECORD), 5, fp);
	fclose(fp);
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			交换两条纪录
Others:					
History:
1. Date:        Author:        Modification:
*************************************************/
void SwapRecord(RECORD *a, RECORD *b)
{
	RECORD temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			释放head指向的内存
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void DeleteMemorey(SNAKE *head)
{
	SNAKE *p = head, *pr = NULL;
	while (NULL != p)
	{
		pr = p;
		p = p->next;
		free(pr);
	}
	return;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			形成一个具有四个节点的链表
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
SNAKE* CreatSnake(SNAKE *head)
{

	if (head == NULL)
	{
		for (int i = 0;i < 4;i++)
		{
			head = AppendNote(head, 10, 5 + i);
		}
		return head;
	}
	else
	{
		SNAKE *pr = head;
		SNAKE *p = NULL;
		for (int i = 0; i < 4; i++)
		{
			pr->x = 10;
			pr->y = 5 + i;
			pr = pr->next;
		}
		while (NULL != pr)
		{
			p = pr;
			pr = pr->next;
			free(p);
		}
		pr = head;
		for (int i = 0; i < 3; i++)
		{
			pr = pr->next;
		}
		pr->next = NULL;

		return head;
	}
	exit(0);
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			新建一个节点添加到链表末尾
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
SNAKE *AppendNote(SNAKE *head, int x, int y)
{
	SNAKE *p = NULL, *pr = head;
	p = (SNAKE *)malloc(sizeof(SNAKE));
	if (NULL == p)
	{
		exit(0);
	}
	if (NULL == head)
	{
		head = p;
	}
	else
	{
		while (pr->next != NULL)
		{
			pr = pr->next;
		}
		pr->next = p;
	}
	p->x = x;
	p->y = y;
	p->next = NULL;
	return head;
}
/****************************************
Author:                 袁坤
Version:				1.0
Date:					2016.1.6
Description:			交换两个数的值
Others:
History:
1. Date:        Author:        Modification:
*************************************************/
void Swap(int *a, int *b) 
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

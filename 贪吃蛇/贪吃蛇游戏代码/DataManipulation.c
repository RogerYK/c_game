/**************************
File name:							DataManipulation.c
Author:								Ԭ��
Version:							2.0
Date:								2016.1.6
Description:						�������ݴ�����ĺ���// ������ϸ˵���˳����ļ���ɵ���Ҫ����
Others:                             
Function List:  
1. void ReadRecord(RECORD record[]);		��ȡ��¼��Ϣ
2. void WriteRecord(RECORD record[]);       �����¼
3. void SwapRecord(RECORD *a, RECORD *b);   ����������¼
4. void DeleteMemorey(SNAKE *head);			�ͷ�headָ����ڴ�
5. SNAKE* CreatSNAKE(SNAKE *head);			����һ�����ĸ��ڵ�ĵ�����
6. SNAKE *AppendNote(SNAKE *head, int x, int y) ���һ���ڵ㵽����ĩβ
History:    
1. Date:        Author:        Modification:
2
*************************************************/
#include "Snake.h"
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			�����¼�ļ�
Others:					recore����Ĭ��Ϊ5
History:      
1. Date:        Author:        Modification:
*************************************************/
void WriteRecord(RECORD record[])
{
	FILE *fp;
	fp = fopen("Snake.bin", "w");
	if (fp == NULL)
	{
		printf("�����¼ʧ��");
		return;
	}
	fwrite(record, sizeof(RECORD), 5, fp);
	fclose(fp);
	return;
}
/****************************************
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			��ȡ�ļ���Ϣ
Others:					recore����Ĭ��Ϊ5
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			����������¼
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			�ͷ�headָ����ڴ�
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			�γ�һ�������ĸ��ڵ������
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			�½�һ���ڵ���ӵ�����ĩβ
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
Author:                 Ԭ��
Version:				1.0
Date:					2016.1.6
Description:			������������ֵ
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

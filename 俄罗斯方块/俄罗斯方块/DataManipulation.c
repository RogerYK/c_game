#include"Tetris.h"
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
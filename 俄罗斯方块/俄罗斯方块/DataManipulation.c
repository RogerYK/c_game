#include"Tetris.h"
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
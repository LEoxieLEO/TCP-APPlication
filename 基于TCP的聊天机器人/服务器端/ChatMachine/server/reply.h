#pragma once
#include <iostream>
#define BUFF_SIZE 256

char oddLine[BUFF_SIZE]; //����ļ�����������
char evenLine[BUFF_SIZE]; //����ļ�ż��������

char* reply(char *recvBuff)
{
	strcat_s(recvBuff, BUFF_SIZE - strlen(recvBuff), "\n");
	FILE *fp;
	if (fopen_s(&fp, "language.txt", "rt") == 0)
	{
		//ѭ����ȡÿ������
		while (!feof(fp))
		{
			fgets(oddLine, BUFF_SIZE, fp); //��ȡ����������
			fgets(evenLine, BUFF_SIZE, fp); //��ȡż��������
			//�Ƚ����������ݣ��ж��Ƿ��ҵ������ܻظ�������
			if (strcmp(oddLine, recvBuff) == 0)
			{
				return evenLine; //�ҵ��˾ͷ���ż��������
			}
			memset(&oddLine, 0, BUFF_SIZE + 1);
			memset(&oddLine, 0, BUFF_SIZE + 1);
		}
	}
	else
	{
		printf("���ܻظ�ʧ��");
	}
	fclose(fp);
	return "�Ҳ�֪��˵ʲô��";
}
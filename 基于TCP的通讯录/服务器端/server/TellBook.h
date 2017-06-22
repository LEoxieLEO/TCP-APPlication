#pragma once

#include <iostream>
#define BUFF_SIZE 256

//������ϵ�˽ṹ��
typedef struct TELLPEOPLE
{
	char name[15]; //����
	char age[3]; //����
	char sex[5]; //�Ա�
	char unit[30]; //��λ
	char tellnum[11]; //�绰����
	char ip[15]; //ip��ַ
}TELLPEOPLE;

//��ʾͨ��¼�ļ��е���Ϣ
void printTellBook()
{
	FILE *fp;
	char line[BUFF_SIZE] = { 0 };
	//ֻ����ʽ���ļ�
	if (fopen_s(&fp, "tellbook.txt", "rt") == 0)
	{
		//ѭ����ȡÿ�е�����
		while (fgets(line, BUFF_SIZE, fp) != NULL)
		{
			printf("%s", line);
		}
		memset(&line, 0, BUFF_SIZE);
	}
	else
	{
		printf("�򿪵绰���ļ�ʧ��");
	}
	fclose(fp);
}

//�����ϵ��
void addTellPeople(char* recvBuff)
{
	FILE *fp;
	char line[BUFF_SIZE] = { 0 };
	//׷�����ݷ�ʽ��д�ļ�
	if (fopen_s(&fp, "tellbook.txt", "a+") == 0)
	{
		if (fputs(recvBuff, fp) != EOF)
		{
			printf("�����ϵ�˳ɹ���");
		}
		else
		{
			printf("�����ϵ��ʧ�ܣ�");
		}
	}
	else
	{
		printf("�򿪵绰���ļ�ʧ��");
	}
	fclose(fp);
}

//ɾ����ϵ��
void deleteTellPeople(char* recvBuff)
{
	//������ϵ�˵�����ɾ���ļ���һ�����ݣ�˼���ǰѳ���һ������������ݸ��Ƶ��½����ļ�����ɾ��ԭ�ļ�������������ļ�
	FILE *fp, *ftemp; //ǰһ���ļ�ָ��ָ��ԭ�ļ�����һ��ָ��ָ���µ��ļ�
	//����һ���ɶ�д���ı��ļ�
	if (fopen_s(&ftemp, "temp.txt", "w") == 0)
	{
		printf("��ʱ�ļ������ɹ���\n");
		fclose(ftemp);
	}
	else
	{
		printf("��ʱ�ļ�����ʧ�ܣ�\n");
		getchar();
		exit(-1);
	}
	//�ı���ʱ�ļ��Ķ�д��ʽ���������ļ�ĩβ�������
	if (fopen_s(&ftemp, "temp.txt", "at+") == 0)
	{
		printf("�ı��ļ��Ķ�д��ʽ�ɹ���\n");
	}
	else
	{
		printf("�ı��ļ��Ķ�д��ʽʧ�ܣ�\n");
		getchar();
		exit(-1);
	}
	char line[BUFF_SIZE] = { 0 };
	//�ɶ���д��ʽ���ļ�
	if (fopen_s(&fp, "tellbook.txt", "r") == 0)
	{
		//���⴦���ļ���һ�е�����
		fgets(line, BUFF_SIZE, fp); //��ԭ�ļ���һ�����ݣ���ʱ�ļ�ָ��fp���ƶ�����һ�еĿ�ͷ
		//FILE *fpp = fp;
		strcat_s(line, BUFF_SIZE, "\n");
		fputs(line, ftemp); //��ӵ��½��ļ���
		TELLPEOPLE tellPeople = { "", "", "", "", "", "" };
		//ɾ����ϵ��ʱҪ�Ѵ��ļ��ж�����ÿ����ϵ�˵���Ϣ��ʽ������һ��
		bool isFind = false;
		//�����Ʊ���ͻ��з�
		char ct = '\t';
		char cn = '\n';
		//��ʽ����ȡ�ļ��е�����
		while (fscanf_s(fp, "%s\t%s\t%s\t%s\t%s\t%s\n", tellPeople.name, 15, tellPeople.age, 3, tellPeople.sex, 5, tellPeople.unit, 30, tellPeople.tellnum, 11, tellPeople.ip, 15) != EOF)
		{
			if (strcmp(tellPeople.name, recvBuff) == 0)
			{
				printf("�ҵ���Ҫɾ������ϵ��\n");
				isFind = true;
			}
			else
			{
				fflush(stdin);
				//��ʽ��д���µ��ļ�
				fprintf_s(ftemp, "%s%c%s%c%s%c%s%c%s%c%s\n", tellPeople.name, ct, tellPeople.age, ct, tellPeople.sex, ct, tellPeople.unit, ct, tellPeople.tellnum, ct, tellPeople.ip, cn);
				tellPeople = {"", "", "", "", "", ""};
			}
		}
		if (isFind == false)
			printf("û���ҵ�Ҫɾ������ϵ��\n");
		memset(&line, 0, BUFF_SIZE);
	}
	else
	{
		printf("�򿪵绰���ļ�ʧ��");
	}
	//�ر��ļ�ָ�룬ɾ��ԭ�ļ�����������ʱ�ļ�
	fclose(ftemp);
	fclose(fp);
	remove("tellbook.txt");
	rename("temp.txt", "tellbook.txt");
}


// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <WinSock.h>
#include "TellPeople.h"

#define BUFF_SIZE 256
#pragma comment(lib, "ws2_32.lib")
void showmenu();

int _tmain(int argc, _TCHAR* argv[])
{
	//������windows�µ�socket���
	WORD wsaWord = MAKEWORD(2, 2);
	WSADATA wsaData;
	int wsaErr = WSAStartup(wsaWord, &wsaData);
	if (wsaErr != 0)
	{
		printf("WSAStartup failed with error: %d\n", wsaErr);
		getchar();
		return -1;
	}

	//�����ͻ��˵�socket
	SOCKET clieSock = socket(AF_INET, SOCK_STREAM, 0);

	//���÷������˵������Ϣ
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(SOCKADDR));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(4567);

	//���ӷ�������
	int err = connect(clieSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	if (err != 0)
	{
		printf("���ӷ�������ʧ��\n");
		getchar();
		return -1;
	}
	printf("���ӷ������ɹ�\n");

	showmenu(); //��ʾ�˵�

	//�������ڽ��պͷ��͵��ַ�������
	char sendBuff[BUFF_SIZE] = { 0 };
	char recvBuff[BUFF_SIZE] = { 0 };
	//���ͺͽ�����Ϣ
	int sendLen = 0;
	int recvLen = 0;
	while (1)
	{
		printf("����������ִ�еĹ�����ţ�");
		scanf_s("%s", sendBuff, BUFF_SIZE);
		//�ж��Ƿ�Ҫ�˳���������Ϣ�����͸��������ˣ�ֱ���ڿͻ����ж��˳�
		if (strcmp(sendBuff, "4") == 0)
		{
			printf("��ӭ�´�ʹ��\n");
			break;
		}
		sendLen = send(clieSock, sendBuff, strlen(sendBuff), 0);
		//�ж��Ƿ��ͳɹ�
		if (sendLen > 0)
		{
			printf("���ͳɹ��ˣ�\n");
			//����ͻ���ѡ����2������Ҫ�ͻ��˶෢һ����Ϣ���������˶���һ����Ϣ
			if (strcmp(sendBuff, "2") == 0)
			{
				TELLPEOPLE tellPeople;
				char ct = '\t';
				char cn = '\n';
				if (recv(clieSock, recvBuff, BUFF_SIZE, 0) > 0)
				{
					printf("%s", recvBuff);
					scanf_s("%s", tellPeople.name, 15);
					scanf_s("%s", tellPeople.age, 3);
					scanf_s("%s", tellPeople.sex, 5);
					scanf_s("%s", tellPeople.unit, 30);
					scanf_s("%s", tellPeople.tellnum, 11);
					scanf_s("%s", tellPeople.ip, 15);
					//scanf_s("%s%s%s%s%s%s", tellPeople.name, 15,  &tellPeople.age, 3, tellPeople.sex, 5, tellPeople.unit, 30, tellPeople.tellnum, 11, tellPeople.ip, 15);
				}
				memset(&sendBuff, 0, BUFF_SIZE);
				sprintf_s(sendBuff, "%s%c%s%c%s%c%s%c%s%c%s%c", tellPeople.name, ct, tellPeople.age, ct, tellPeople.sex, ct, tellPeople.unit, ct, tellPeople.tellnum, ct, tellPeople.ip, cn);
				printf("%s", sendBuff);
				if (send(clieSock, sendBuff, strlen(sendBuff), 0) > 0)
				{
					printf("���ͳɹ���\n");
				}
			}
			//����ͻ���ѡ����3������Ҫ�ͻ��˶෢һ��Ҫɾ������ϵ�˵��������������˶���һ����Ϣ
			if (strcmp(sendBuff, "3") == 0)
			{
				if (recv(clieSock, recvBuff, BUFF_SIZE, 0) > 0)
				{
					printf("%s", recvBuff);
					char name[15] = { 0 };
					scanf_s("%s", name, 15);
					strcpy_s(sendBuff, BUFF_SIZE, name);
				}
				if (send(clieSock, sendBuff, strlen(sendBuff), 0) > 0)
				{
					printf("���ͳɹ���\n");
				}
			}
			memset(recvBuff, 0, BUFF_SIZE);
			recvLen = recv(clieSock, recvBuff, BUFF_SIZE, 0);
			//�ж��Ƿ���ճɹ�
			if (recvLen > 0)
			{
				printf("%s\n", recvBuff);
			}
			else
			{
				printf("û�н��յ��������˵Ļظ�\n");
			}
		}
		memset(&sendBuff, 0, BUFF_SIZE);
		memset(&recvBuff, 0, BUFF_SIZE);
	}
	closesocket(clieSock);
	WSACleanup();
	system("pause");
	return 0;
}

void showmenu()
{
	printf("************��ӭʹ�û���TCP��ͨѶ¼************\n");
	printf("		1.��ʾ��ϵ����Ϣ\n");
	printf("		2.�����ϵ��\n");
	printf("		3.ɾ����ϵ��\n");
	printf("		4.�˳�\n");
	printf("***********************************************\n");
}
// server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <winsock.h>
#include "TellBook.h"

#pragma comment(lib, "ws2_32.lib") //��̬�������ӿ�

#define BUFF_SIZE 256

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

	//�����������˵�socket
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	//�׽��ְ�IP��Ϣ
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(SOCKADDR));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(4567);
	bind(servSock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	//�������״̬
	int error = listen(servSock, 20);
	if (error != 0)
	{
		printf("����������ʧ�ܣ�����ʧ��\n");
		getchar();
		return -1;
	}
	printf("���������������ȴ��ͻ�������\n");

	//�õ��ͻ������ӵ�socket
	SOCKADDR clieAddr;
	int addrLen = sizeof(SOCKADDR);
	SOCKET clieSock = accept(servSock, (SOCKADDR*)&clieAddr, &addrLen);

	//�������ڽ��պͷ��͵��ַ�������
	char recvBuff[BUFF_SIZE] = { 0 };
	char sendBuff[BUFF_SIZE] = { 0 };
	int recvLen = 0;
	int sendLen = 0;

	//�������˽��պͷ�����Ϣ
	while (1)
	{
		recvLen = recv(clieSock, recvBuff, BUFF_SIZE, 0);
		//�жϽ����Ƿ�ɹ�
		if (recvLen > 0)
		{
			printf("���յ��ͻ��˷�������Ϣ:%s\n", recvBuff);
			//������ݿͻ��˵�������������صĲ���
			if (strcmp(recvBuff, "1") == 0)
			{
				printf("*******��ʾͨѶ¼*******\n");
				printTellBook(); //��ʾͨѶ¼
			}
			if (strcmp(recvBuff, "2") == 0)
			{
				strcpy_s(sendBuff, BUFF_SIZE, "��������ϵ�˵����������䣬�Ա� ��λ�� �ֻ��ţ� ip\n");
				if (send(clieSock, sendBuff, strlen(sendBuff), 0) > 0)
				{
					memset(recvBuff, 0, BUFF_SIZE);
					//�����ϵ�ˣ���Ҫ��������һ�����Կͻ��˵���ϵ�˾�����Ϣ����Ϣ
					if (recv(clieSock, recvBuff, BUFF_SIZE, 0) > 0)
					{
						printf("*******�����ϵ��*******\n");
						addTellPeople(recvBuff);
					}
				}
			}
			if (strcmp(recvBuff, "3") == 0)
			{
				strcpy_s(sendBuff, BUFF_SIZE, "������Ҫɾ������ϵ�˵�������");
				if (send(clieSock, sendBuff, strlen(sendBuff), 0) > 0)
				{
					memset(recvBuff, 0, BUFF_SIZE);
					//ɾ����ϵ�ˣ���Ҫ��������һ�����Կͻ��˵���ϵ�˵�����
					if (recv(clieSock, recvBuff, BUFF_SIZE, 0) > 0)
					{
						printf("ɾ����ϵ���С�����������\n");
						deleteTellPeople(recvBuff);
					}
				}
			}
			memset(sendBuff, 0, BUFF_SIZE);
			strcpy_s(sendBuff, BUFF_SIZE, "���������Ѵ�������\n"); //���͵���������д����
			sendLen = send(clieSock, sendBuff, strlen(sendBuff), 0);
			//�жϷ����Ƿ�ɹ�
			if (sendLen > 0)
			{
				printf("���ͳɹ�\n");
			}
		}
		//���÷��ͺͽ����ַ��������ݣ�����
		memset(&recvBuff, 0, BUFF_SIZE);
		memset(&sendBuff, 0, BUFF_SIZE);
	}
	closesocket(clieSock);
	closesocket(servSock);
	WSACleanup();
	return 0;
}


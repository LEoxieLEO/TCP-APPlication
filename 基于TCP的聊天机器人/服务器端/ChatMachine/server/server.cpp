// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <winsock.h>
#include <Windows.h>
#include "reply.h"


#pragma comment(lib, "ws2_32.lib")

#define BUFF_SIZE 256
#define MAX_CLIENTS 5

//���߳�������ÿ���ͻ��˵���������
HANDLE threads[MAX_CLIENTS];
HANDLE hMutex; //�����������
int threadCount = 0;


//���߳�ִ�к���
DWORD WINAPI ProcessClientRequests(LPVOID lpParam)
{
	int static count = 1;
	printf("��%d��ִ�ж��̺߳���\n", count++);
	//��ȡ�������Ŀͻ��˵�SOCKET
	SOCKET* clieSock = (SOCKET *)lpParam;

	//�����������պͷ��͵��ַ�������
	char recvBuff[BUFF_SIZE] = {0};
	char sendBuff[BUFF_SIZE] = {0};

	//ѭ�����տͻ��˵ķ�������Ϣ
	while(1)
	{
		//���տͻ��˷�������Ϣ
		int recvLen = recv(*clieSock, recvBuff, BUFF_SIZE, 0);
		//�жϿͻ����Ƿ�ɹ�������Ϣ
		if(recvLen > 0)
		{
			printf("IP��ַΪ%d�Ŀͻ��˷�����%s\n", *clieSock, recvBuff);
			//���ܻظ���Ϣ
			strcpy_s(sendBuff, BUFF_SIZE, reply(recvBuff));
			int sendLen = send(*clieSock, sendBuff, strlen(sendBuff), 0);
			if(sendLen > 0)
			{
				printf("���ܻظ��ɹ�\n");
				printf("��˵��%s\n", sendBuff);
			}
		}
		//���������պͷ��͵��ַ�����������
		memset(&recvBuff, 0, BUFF_SIZE);
		memset(&sendBuff, 0, BUFF_SIZE);
	}
	ReleaseMutex(hMutex);
	//�Ի���Ϻ�رտͻ��˵�socket
	closesocket(*clieSock);
	return 0;
}



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

	hMutex = CreateMutex(NULL, FALSE, NULL); //�����������

	//�ж��Ƿ񳬹��˹涨�Ŀͻ���������
	while (1)
	{
		if (threadCount < MAX_CLIENTS)
		{
			//���ܿͻ��˵�����
			SOCKADDR clieAddr;
			int addrLen = sizeof(SOCKADDR);
			SOCKET clieSock = accept(servSock, (SOCKADDR*)&clieAddr, &addrLen);

			//�жϿͻ������ӵ��׽����Ƿ���Ч
			if (clieSock == INVALID_SOCKET)
			{
				printf("clieSock is invalid");
				getchar();
				return -1;
			}
			threads[threadCount++] = CreateThread(NULL, NULL, ProcessClientRequests, (LPVOID*)&clieSock, 0, NULL);
			WaitForSingleObject(hMutex, INFINITE);
			WaitForMultipleObjects(MAX_CLIENTS, threads, true, INFINITE);
		}
	}
	CloseHandle(threads);
	closesocket(servSock);
	WSACleanup();
	return 0;
}


// ChatMachine.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <WinSock.h>

#define BUFF_SIZE 256
#pragma comment(lib, "ws2_32.lib")

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
	//�������ڽ��պͷ��͵��ַ�������
	char sendBuff[BUFF_SIZE] = { 0 };
	char recvBuff[BUFF_SIZE] = { 0 };

	//���ͺͽ�����Ϣ
	int sendLen = 0;
	int recvLen = 0;
	while (1)
	{
		printf("��С����");
		scanf_s("%s", sendBuff, BUFF_SIZE);
		sendLen = send(clieSock, sendBuff, strlen(sendBuff), 0);
		if (sendLen > 0)
		{
			printf("���ͳɹ��ˣ�\n");
			recvLen = recv(clieSock, recvBuff, BUFF_SIZE, 0);
			if (recvLen > 0)
			{
				printf("���յ��˷������˵Ļظ�\n");
				printf("��������ˣ�%s\n", recvBuff);
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
	return 0;
}



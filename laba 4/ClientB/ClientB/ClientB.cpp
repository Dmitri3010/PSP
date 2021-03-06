#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Winsock2.h"
#include <iostream>
#include <ctime>

#pragma comment (lib,"WS2_32.lib") // экспорт  WS2_32.dll
using namespace std;


string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "WSAEINTR";
		break;
	case WSAEACCES: msgText = "WSAEACCES";
		break;
	case WSAEFAULT: msgText = "WSAEFAULT";
		break;
	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE";
		break;
	default: msgText = "***ERROR***";
		break;
	}
	return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}


bool GetServer(SOCKET cC, char *call, short port, sockaddr* from, unsigned int flen, int *lto, in_addr addr)
{
	try
	{

		int  lobuf = 0;
		char ibuf[100000]= "hello";                  //буфер ввода  
		int  lb = 0;
		port = htons(2000);
		if ((lobuf = sendto(cC, call, strlen(call) + 1, NULL,
			from, flen)) == SOCKET_ERROR)
			throw  SetErrorMsgText("recv:",WSAGetLastError());
		cout << "Отправлено сообщение " << call << endl;
		cout << "Порт сервера " << htons(port) << " IP " << inet_ntoa(addr) << endl;
		if ((lb = recvfrom(cC, ibuf, sizeof(ibuf), NULL,
			from, lto)) == SOCKET_ERROR)
		{
			throw  SetErrorMsgText("recv error", WSAGetLastError());
			return false;
		}
		else
		{
			cout << "Позывной сервера:" << endl;
			cout << ibuf << endl;



			cout << "Получено " << lb << " bit " << endl;
			return true;
		}
	}
	catch (string errorMsgText)
	{
		cout << endl <<GetLastError();
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;

	system("chcp 1251");

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup error", WSAGetLastError());
		SOCKET cC;
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket error", WSAGetLastError());
		int optval = 1;
		if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST,
			(char*)&optval, sizeof(optval)) == SOCKET_ERROR)
			throw  SetErrorMsgText("opt:", WSAGetLastError());




		SOCKADDR_IN serv;                     // параметры  сокета cC
		serv.sin_family = AF_INET;           // используется IP-адресация  
		serv.sin_port = htons(2000);          // порт 2000
		serv.sin_addr.s_addr = INADDR_BROADCAST;     // любой собственный IP-адрес inet_addr("127.0.0.1")

		char obuf[100000];   //буфер вывода
		int  lobuf = 0;                    //количество отправленных  
		int  lb = 0;
		int lc = sizeof(serv);

		cout << "Введите сообщение серверу" << endl;
		cin >> obuf;

		GetServer(cC, obuf, 2000, (sockaddr*)&serv, sizeof(serv), &lc, serv.sin_addr);
		//cout<<"Ip-адрес сервера: "<<inet_ntoa(serv.sin_addr)<<" порт: "<<htons(serv.sin_port)<<endl;

		int time = clock();
		cout << "Время обмена сообщениями " << time << endl;


		if (closesocket(cC) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket error", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup error", WSAGetLastError());

	}
	catch (string errorMsgText)
	{

		cout << endl << GetLastError();
	}
	std::cin.get();
	return 0;
}
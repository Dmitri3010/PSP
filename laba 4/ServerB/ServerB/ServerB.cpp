#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include "Winsock2.h"
#include <ctime>
#pragma comment (lib,"WS2_32.lib")
using namespace std;

bool GetRequestFromClient(SOCKET Ss, char name[100000],
	short port, sockaddr* from, int * flen, in_addr addr);

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


bool GetRequestFromClient(SOCKET Ss, char name[100000], short port, sockaddr* from, int * flen, in_addr addr)
{
	try {

		char message[100000];
		if ((recvfrom(Ss, message, sizeof(message), NULL,
			from, flen)) == SOCKET_ERROR)
		{
			throw  SetErrorMsgText("recv",WSAGetLastError());
			return false;
		}
		else
		{
			if (*message == *name)
			{

				cout << "Правильный позывной" << endl;
				cout << "Порт клиента " << htons(port) << " IP " << inet_ntoa(addr) << endl;
				return true;
			}
			else
			{
				cout << "Неправильный позывной" << endl;
				GetRequestFromClient(Ss, name, port, from, flen, addr);
			}
		}
	}


	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}
}

bool PutAnswerToClient(SOCKET sS, char* name, unsigned int lto, sockaddr* to)
{
	try {

		if ((sendto(sS, name, strlen(name) + 1, NULL, to, lto)) == SOCKET_ERROR)
			throw  SetErrorMsgText("send error", WSAGetLastError());
		else cout << "Позывной отправлен клиенту " << endl;
		return true;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}
}




int main()
{
	setlocale(LC_ALL, "rus");
	SOCKET cC;
	WSADATA ws;
	int i = 0;
	try {
		if (FAILED(WSAStartup(MAKEWORD(1, 1), &ws)))
		{
			cout << "WSAStartup : " << WSAGetLastError() << endl;
		}

		if (INVALID_SOCKET == (cC = socket(AF_INET, SOCK_DGRAM, 0)))
		{
			cout << "Socket : " << WSAGetLastError();
		}



		SOCKADDR_IN serv;              // параметры  сокета sS
		serv.sin_family = AF_INET;     // используется IP-адресация  
		serv.sin_port = htons(2000);    // порт 2000 
		serv.sin_addr.s_addr = INADDR_ANY; // адрес сервера 
		char obuf[50] = "hello from server";   //буфер вывода
		int  lobuf = 0;                    //количество отправленных  
		if (bind(cC, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw  SetErrorMsgText("bind:", WSAGetLastError());

		SOCKADDR_IN clnt;               // параметры  сокета клиента
		memset(&clnt, 0, sizeof(clnt));   // обнулить память
		int lc = sizeof(clnt);
		char ibuf[50];                  //буфер ввода 
		int  lb = 0;                    //количество принятых байт
		char ServName[50] = "hello";

		while (true)
		{
			
			GetRequestFromClient(cC, ServName, htons(2000), (sockaddr*)&clnt, &lc, clnt.sin_addr);
			cout<<"Ip-адрес клиента: "<<inet_ntoa(clnt.sin_addr)<<" порт: "<<htons(clnt.sin_port)<<endl;
			cout << endl;

			PutAnswerToClient(cC, ServName, sizeof(serv), (sockaddr*)&clnt);


			
		}
	}



	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

    return 0;
}


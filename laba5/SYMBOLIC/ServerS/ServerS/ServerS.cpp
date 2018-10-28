#include "stdafx.h"
#include "iostream"
#include "string.h"
#include "locale"
#include "time.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
using namespace std;

string GetErrorMsgText (int code)
{
	string msgText;

	switch (code)
	{
		case WSAEINTR:				 msgText = "Работа функции прервана\n";						  break;
		case WSAEACCES:				 msgText = "Разрешение отвергнуто\n";						  break;
		case WSAEFAULT:				 msgText = "Ошибочный адрес\n";								  break;
		case WSAEINVAL:				 msgText = "Ошибка в аргументе\n";							  break;
		case WSAEMFILE:				 msgText = "Слишком много файлов открыто\n";				  break;
		case WSAEWOULDBLOCK:		 msgText = "Ресурс временно недоступен\n";					  break;
		case WSAEINPROGRESS:		 msgText = "Операция в процессе развития\n";				  break;
		case WSAEALREADY: 			 msgText = "Операция уже выполняется\n";					  break;
		case WSAENOTSOCK:   		 msgText = "Сокет задан неправильно\n";						  break;
		case WSAEDESTADDRREQ:		 msgText = "Требуется адрес расположения\n";				  break;
		case WSAEMSGSIZE:  			 msgText = "Сообщение слишком длинное\n";				      break;
		case WSAEPROTOTYPE:			 msgText = "Неправильный тип протокола для сокета\n";		  break;
		case WSAENOPROTOOPT:		 msgText = "Ошибка в опции протокола\n";					  break;
		case WSAEPROTONOSUPPORT:	 msgText = "Протокол не поддерживается\n";					  break;
		case WSAESOCKTNOSUPPORT:	 msgText = "Тип сокета не поддерживается\n";				  break;
		case WSAEOPNOTSUPP:			 msgText = "Операция не поддерживается\n";					  break;
		case WSAEPFNOSUPPORT:		 msgText = "Тип протоколов не поддерживается\n";			  break;
		case WSAEAFNOSUPPORT:		 msgText = "Тип адресов не поддерживается протоколом\n";	  break;
		case WSAEADDRINUSE:			 msgText = "Адрес уже используется\n";						  break;
		case WSAEADDRNOTAVAIL:		 msgText = "Запрошенный адрес не может быть использован\n";	  break;
		case WSAENETDOWN:			 msgText = "Сеть отключена\n";								  break;
		case WSAENETUNREACH:		 msgText = "Сеть не достижима\n";							  break;
		case WSAENETRESET:			 msgText = "Сеть разорвала соединение\n";					  break;
		case WSAECONNABORTED:		 msgText = "Программный отказ связи\n";						  break;
		case WSAECONNRESET:			 msgText = "Связь восстановлена\n";							  break;
		case WSAENOBUFS:			 msgText = "Не хватает памяти для буферов\n";				  break;
		case WSAEISCONN:			 msgText = "Сокет уже подключен\n";							  break;
		case WSAENOTCONN:			 msgText = "Сокет не подключен\n";							  break;
		case WSAESHUTDOWN:			 msgText = "Нельзя выполнить send: сокет завершил работу\n";  break;
		case WSAETIMEDOUT:			 msgText = "Закончился отведенный интервал  времени\n";		  break;
		case WSAECONNREFUSED:		 msgText = "Соединение отклонено\n";						  break;
		case WSAEHOSTDOWN:			 msgText = "Хост в неработоспособном состоянии\n";			  break;
		case WSAEHOSTUNREACH:		 msgText = "Нет маршрута для хоста\n";						  break;
		case WSAEPROCLIM:			 msgText = "Слишком много процессов\n";						  break;
		case WSASYSNOTREADY:		 msgText = "Сеть не доступна\n";							  break;
		case WSAVERNOTSUPPORTED:	 msgText = "Данная версия недоступна\n";					  break;
		case WSANOTINITIALISED:		 msgText = "Не выполнена инициализация WS2_32.DLL\n";		  break;
		case WSAEDISCON:			 msgText = "Выполняется отключение\n";						  break;
		case WSATYPE_NOT_FOUND:		 msgText = "Класс не найден\n";								  break;
		case WSAHOST_NOT_FOUND:		 msgText = "Хост не найден\n";								  break;
		case WSATRY_AGAIN:			 msgText = "Неавторизированный хост не найден\n";			  break;
		case WSANO_RECOVERY:		 msgText = "Неопределенная ошибка\n";						  break;
		case WSANO_DATA:			 msgText = "Нет записи запрошенного типа\n";				  break;
		case WSA_INVALID_HANDLE:	 msgText = "Указанный дескриптор события  с ошибкой\n";		  break;
		case WSA_INVALID_PARAMETER:	 msgText = "Один или более параметров с ошибкой\n";			  break;
		case WSA_IO_INCOMPLETE:		 msgText = "Объект ввода-вывода не в сигнальном состоянии\n"; break;
		case WSA_IO_PENDING:		 msgText = "Операция завершится позже\n";					  break;
		case WSA_NOT_ENOUGH_MEMORY:	 msgText = "Не достаточно памяти\n";						  break;
		case WSA_OPERATION_ABORTED:	 msgText = "Операция отвергнута\n";							  break;
		case WSAEINVALIDPROCTABLE:	 msgText = "Ошибочный сервис\n";							  break;
		case WSAEINVALIDPROVIDER:	 msgText = "Ошибка в версии сервиса\n";						  break;
		case WSAEPROVIDERFAILEDINIT: msgText = "Невозможно инициализировать сервис\n";			  break;
		case WSASYSCALLFAILURE:		 msgText = "Аварийное завершение системного вызова\n";		  break;
		default:					 msgText = "Error\n";										  break;
	};
	return msgText;
}

string SetErrorMsgText(string msg, int code)
{
	string m = msg;
	m += GetErrorMsgText(code);
	return m;
}

bool getRequestFromClient(char* name, short port, struct sockaddr* from, int * flen)
{
	try
	{
		SOCKET bS;

		if((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = INADDR_ANY;
		serv.sin_port = htons(port);

		if(bind(bS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("Bind: ", WSAGetLastError());

		char ibuf[10];
		if((recvfrom(bS, ibuf, sizeof(ibuf), NULL, from, flen)) == WSAETIMEDOUT)
			throw SetErrorMsgText("RecvFrom: ", WSAGetLastError());

		cout << endl << "Message: " << ibuf << endl;

		closesocket(bS);

		if(strcmp(name, ibuf)!=0)
			return false;

		return true;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
		return false;
	}
}

bool putAnswerToClient(char* name, struct sockaddr* to, int* lto)
{
	try
	{
		SOCKET bS;

		if((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());
		
		if((sendto(bS, name, strlen(name)+1, NULL, to, *lto)) == SOCKET_ERROR)
			throw SetErrorMsgText("SendTo: ", WSAGetLastError());

		closesocket(bS);

		return true;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
		return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_CTYPE, "Russian");
	
	cout << "ServerS" <<  endl;
	
	WSADATA wsaData;
	SOCKADDR_IN clnt;

	try
	{
		if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		int lc;
		while(true)
		{
			lc = sizeof(clnt);
			if(getRequestFromClient("Hello", 2000, (sockaddr*)&clnt, &lc))
			{
				char myName[30];
				gethostname(myName, sizeof(myName));
				// получение символического имени хоста     

				cout << "MyName: " << myName << endl;

				cout << "ClientIP: " << inet_ntoa(clnt.sin_addr) <<  endl;
				cout << "ClientName: " << gethostbyaddr((char*)&clnt.sin_addr, sizeof(clnt.sin_addr), AF_INET)->h_name << endl;
				//функция для получения информации о хосте по его символическому  имени     

				
				if(!putAnswerToClient("Hello", (sockaddr*)&clnt, &lc))
					cout << "PutAnswerToClient" << endl;
			}
			else
				cout << "GetRequestFromclient" << endl;
			
		}
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}

	WSACleanup();
	
	return 0;
}
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
		case WSAEINTR:				 msgText = "������ ������� ��������\n";						  break;
		case WSAEACCES:				 msgText = "���������� ����������\n";						  break;
		case WSAEFAULT:				 msgText = "��������� �����\n";								  break;
		case WSAEINVAL:				 msgText = "������ � ���������\n";							  break;
		case WSAEMFILE:				 msgText = "������� ����� ������ �������\n";				  break;
		case WSAEWOULDBLOCK:		 msgText = "������ �������� ����������\n";					  break;
		case WSAEINPROGRESS:		 msgText = "�������� � �������� ��������\n";				  break;
		case WSAEALREADY: 			 msgText = "�������� ��� �����������\n";					  break;
		case WSAENOTSOCK:   		 msgText = "����� ����� �����������\n";						  break;
		case WSAEDESTADDRREQ:		 msgText = "��������� ����� ������������\n";				  break;
		case WSAEMSGSIZE:  			 msgText = "��������� ������� �������\n";				      break;
		case WSAEPROTOTYPE:			 msgText = "������������ ��� ��������� ��� ������\n";		  break;
		case WSAENOPROTOOPT:		 msgText = "������ � ����� ���������\n";					  break;
		case WSAEPROTONOSUPPORT:	 msgText = "�������� �� ��������������\n";					  break;
		case WSAESOCKTNOSUPPORT:	 msgText = "��� ������ �� ��������������\n";				  break;
		case WSAEOPNOTSUPP:			 msgText = "�������� �� ��������������\n";					  break;
		case WSAEPFNOSUPPORT:		 msgText = "��� ���������� �� ��������������\n";			  break;
		case WSAEAFNOSUPPORT:		 msgText = "��� ������� �� �������������� ����������\n";	  break;
		case WSAEADDRINUSE:			 msgText = "����� ��� ������������\n";						  break;
		case WSAEADDRNOTAVAIL:		 msgText = "����������� ����� �� ����� ���� �����������\n";	  break;
		case WSAENETDOWN:			 msgText = "���� ���������\n";								  break;
		case WSAENETUNREACH:		 msgText = "���� �� ���������\n";							  break;
		case WSAENETRESET:			 msgText = "���� ��������� ����������\n";					  break;
		case WSAECONNABORTED:		 msgText = "����������� ����� �����\n";						  break;
		case WSAECONNRESET:			 msgText = "����� �������������\n";							  break;
		case WSAENOBUFS:			 msgText = "�� ������� ������ ��� �������\n";				  break;
		case WSAEISCONN:			 msgText = "����� ��� ���������\n";							  break;
		case WSAENOTCONN:			 msgText = "����� �� ���������\n";							  break;
		case WSAESHUTDOWN:			 msgText = "������ ��������� send: ����� �������� ������\n";  break;
		case WSAETIMEDOUT:			 msgText = "���������� ���������� ��������  �������\n";		  break;
		case WSAECONNREFUSED:		 msgText = "���������� ���������\n";						  break;
		case WSAEHOSTDOWN:			 msgText = "���� � ����������������� ���������\n";			  break;
		case WSAEHOSTUNREACH:		 msgText = "��� �������� ��� �����\n";						  break;
		case WSAEPROCLIM:			 msgText = "������� ����� ���������\n";						  break;
		case WSASYSNOTREADY:		 msgText = "���� �� ��������\n";							  break;
		case WSAVERNOTSUPPORTED:	 msgText = "������ ������ ����������\n";					  break;
		case WSANOTINITIALISED:		 msgText = "�� ��������� ������������� WS2_32.DLL\n";		  break;
		case WSAEDISCON:			 msgText = "����������� ����������\n";						  break;
		case WSATYPE_NOT_FOUND:		 msgText = "����� �� ������\n";								  break;
		case WSAHOST_NOT_FOUND:		 msgText = "���� �� ������\n";								  break;
		case WSATRY_AGAIN:			 msgText = "������������������ ���� �� ������\n";			  break;
		case WSANO_RECOVERY:		 msgText = "�������������� ������\n";						  break;
		case WSANO_DATA:			 msgText = "��� ������ ������������ ����\n";				  break;
		case WSA_INVALID_HANDLE:	 msgText = "��������� ���������� �������  � �������\n";		  break;
		case WSA_INVALID_PARAMETER:	 msgText = "���� ��� ����� ���������� � �������\n";			  break;
		case WSA_IO_INCOMPLETE:		 msgText = "������ �����-������ �� � ���������� ���������\n"; break;
		case WSA_IO_PENDING:		 msgText = "�������� ���������� �����\n";					  break;
		case WSA_NOT_ENOUGH_MEMORY:	 msgText = "�� ���������� ������\n";						  break;
		case WSA_OPERATION_ABORTED:	 msgText = "�������� ����������\n";							  break;
		case WSAEINVALIDPROCTABLE:	 msgText = "��������� ������\n";							  break;
		case WSAEINVALIDPROVIDER:	 msgText = "������ � ������ �������\n";						  break;
		case WSAEPROVIDERFAILEDINIT: msgText = "���������� ���������������� ������\n";			  break;
		case WSASYSCALLFAILURE:		 msgText = "��������� ���������� ���������� ������\n";		  break;
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

bool getServerByName(char* name, char* call, struct sockaddr* from, int* flen) // ��� ��, �������� �������, ��������� �� sockaddr_in, ��������� �� ������ sockaddr_in
{
	try
	{
		SOCKET bS;

		if((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());
		
		int optval = 1;
		// ���������� ������, ������� ������, ����� ������, �������� ������,����� ������ (so_broadcast ��������� ���. innadr_broadcast
		if(setsockopt(bS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw SetErrorMsgText("SetSockOpt: ", WSAGetLastError());
		
		hostent* serv;
		/* hostent {             // ��������� hostent  
			char FAR* h_name;            // ��� ����� 
			char FAR  FAR** h_aliases;   // ������ ������� 
			short h_addrtype;            // ��� ���������
			short h_length;              // ����� ������
			char FAR  FAR** h_addr_list; // ������ ������� 
		} */



		//������� ��� ��������� ���������� � ����� �� ��� ��������������  ����� 
		if((serv=gethostbyname(name)) == NULL) 
			throw "Not find";
		else
			cout << endl << "Find ";
		
		from->sa_family = serv->h_addrtype;

		cout << "name: " << serv->h_name << endl;
		
		if((sendto(bS, call, strlen(call)+1, NULL, from, *flen)) == SOCKET_ERROR)
			throw SetErrorMsgText("SendTo: ", WSAGetLastError());

		char buf[10];
		if((recvfrom(bS, buf, sizeof(buf), NULL, from, flen)) == WSAETIMEDOUT)
			throw SetErrorMsgText("RecvFrom: ", WSAGetLastError());
		
		if(strcmp(call, buf)!=0)
			throw "Strcmp";
		
		cout << "Message: " << buf << endl;
		
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
	
	cout << "ClientS" << endl;
	
	WSADATA wsaData;

	try
	{
		if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		
		SOCKADDR_IN serv;
		serv.sin_port = htons(2000);
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = INADDR_BROADCAST;
		
		int sl = sizeof(serv);
		if(getServerByName("DMITRI-PC", "Hello", (sockaddr*)&serv, &sl))
		{
			cout << "IP --> " << inet_ntoa(serv.sin_addr) << endl;
		}
		else
			cout << "Name not find" << endl;		
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}

	WSACleanup();

	return 0;
}
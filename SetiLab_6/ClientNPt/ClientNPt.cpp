#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include "windows.h"

std::string SetPipeError(std::string msgText, int code)
{
	char intStr[20];
	itoa(code, intStr, 16);
	std::string str = std::string(intStr);

	return msgText + " " + str;
};

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "");

	HANDLE hPipe;
	try
	{
		if ((hPipe = CreateFile(TEXT("\\\\.\\pipe\\Tube"), GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("createfile:", GetLastError());


		int countMessage = 0;
		std::cout << std::endl << "Enter count of message: ";
		std::cin >> countMessage;

		for (int i = 0; i < countMessage; i++)
		{
			DWORD buf;
			char wbuf[100] = "First message from Client";
			char wbuf_2[100] = "Second message from Client";
			char rbuf[100] = "";

			if (!TransactNamedPipe(hPipe, wbuf, sizeof(wbuf) + 1, rbuf, sizeof(rbuf) + 1, &buf, NULL))
			{
				throw SetPipeError("TransactNamedPipe:", GetLastError());
			}
			std::cout << std::endl << "First message: " << rbuf;

			if (!TransactNamedPipe(hPipe, wbuf_2, sizeof(wbuf_2) + 1, rbuf, sizeof(rbuf) + 1, &buf, NULL))
			{
				throw SetPipeError("TransactNamedPipe:", GetLastError());
			}
			std::cout << std::endl << "second message: " << rbuf;

			if (i != countMessage - 1)
			{
				char wbuf_3[100] = "next";
				if (!WriteFile(hPipe, wbuf_3, sizeof(wbuf_3) + 1, &buf, NULL))
				{
					throw SetPipeError("write:", GetLastError());
				}
			}
			else
			{
				if (!WriteFile(hPipe, 0, 0, &buf, NULL))
				{
					throw SetPipeError("write:", GetLastError());
				}
			}
		}

		CloseHandle(hPipe);
	}
	catch (std::string ErrorPipeText)
	{
		std::cout << std::endl << ErrorPipeText;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
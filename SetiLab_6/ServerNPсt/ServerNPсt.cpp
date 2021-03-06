#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>

std::string SetPipeError(std::string msgText, int code)
{
	char intStr[20];
	itoa(code, intStr, 10);
	std::string str = std::string(intStr);

	return msgText + " " + str;
};

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "");

	HANDLE hPipe;
	try
	{
		if ((hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Tube"), PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE, 1, NULL, NULL, INFINITE, NULL)) == INVALID_HANDLE_VALUE)
		{
			throw SetPipeError("create:", GetLastError());
		}

		try
		{
			for (;;)
			{
				std::cout << std::endl << "wait client!";
				if (!ConnectNamedPipe(hPipe, NULL))
				{
					throw SetPipeError("connect:", GetLastError());
				}

				clock_t start = clock();
				DWORD buf = 1;

				char rbuf[100] = "";
				if (!ReadFile(hPipe, rbuf, sizeof(rbuf) + 1, &buf, NULL))
				{
					throw SetPipeError("read:", GetLastError());
				}
				std::cout << std::endl << "first message: " << rbuf;

				char wbuf[100] = "First message from Server";
				if (!WriteFile(hPipe, wbuf, sizeof(wbuf) + 1, &buf, NULL))
				{
					throw SetPipeError("write:", GetLastError());
				}

				clock_t finish = clock();
				std::cout << std::endl << "Total time: " << finish - start;

				DisconnectNamedPipe(hPipe);
			}
		}
		catch (std::string errorMsgText)
		{
			std::cout << std::endl << errorMsgText;
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
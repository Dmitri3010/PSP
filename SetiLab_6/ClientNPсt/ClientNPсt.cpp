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
		char wbuf[100] = "First message from Client";
		char rbuf[100] = "";
		DWORD buf;

		if (!CallNamedPipe(TEXT("\\\\.\\pipe\\Tube"), wbuf, sizeof(wbuf) + 1, rbuf, sizeof(rbuf) + 1, &buf, NULL))
		{
			throw SetPipeError("CallNamedPipe:", GetLastError());
		}
		std::cout << std::endl << "message from server: " << rbuf;
	}
	catch (std::string ErrorPipeText)
	{
		std::cout << std::endl << ErrorPipeText;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
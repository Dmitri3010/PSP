#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>


std::string SetMaislotError(std::string msgText, int code)
{
	char intStr[20];
	_itoa_s(code, intStr, 10);
	return msgText + " " + std::string(intStr);
};

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");
	HANDLE hM;
	DWORD rb;
	char rbuf[100];
	try
	{
		if ((hM = CreateMailslot(
			TEXT("\\\\.\\mailslot\\Box"),
			300 /*bytes max message size*/, 
			60 * 3 * 1000 /*read timeout*/,
			NULL
		)) == INVALID_HANDLE_VALUE)
			throw SetMaislotError("CreateMailslotError: ", GetLastError());
		for (;;)
			if (!ReadFile(hM, rbuf, sizeof(rbuf), &rb, NULL))
				throw (GetLastError() == 121) ? std::string("time is out!") : SetMaislotError("ReadFileError: ", GetLastError());
			else std::cout << std::endl << "Input message: " << rbuf;
		CloseHandle(hM);
	}
	catch (std::string messageError)
	{
		std::cout << std::endl << messageError;
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
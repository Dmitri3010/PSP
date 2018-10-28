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
	DWORD wb;
	try
	{
		if ((hM = CreateFile(TEXT("\\\\.\\mailslot\\Box"), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw (GetLastError() == 2) ? std::string("Mail server not found!") : SetMaislotError("CreateFileError: ", GetLastError());
		clock_t start = clock();
		for (int i = 0; i < 1000; i++)
		{
			char wbuf[30];
			_itoa_s(i, wbuf, 10);
			if (!WriteFile(hM, wbuf, sizeof(wbuf), &wb, NULL))
				throw SetMaislotError("ReadFileError: ", GetLastError());
		}
		std::cout << std::endl << "Total time for send: " << clock() - start;
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
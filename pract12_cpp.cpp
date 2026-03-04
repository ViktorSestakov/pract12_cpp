#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Принтер запущен!" << endl << endl;

	const char* mName = "PrinterMutMut";
	HANDLE hMut = CreateMutexA(NULL, FALSE, mName);
	const char* sName = "PrinterSemaphore";
	HANDLE hSem = CreateSemaphoreA(NULL, 0, 100, sName);

	if (hMut == NULL || hSem == NULL) {
		cout << "Ошибка создания объектов!" << endl;
		return GetLastError();
	}

	while (true) {
		WaitForSingleObject(hSem, 600000);
		WaitForSingleObject(hMut, 600000);

		cout << "Идет печать!" << endl;
		ReleaseMutex(hMut);

		int printTime = rand() % 11;

		if (printTime >= 10) {
			cout << "Ошибка печати!" << endl;
		}
		else {
			WaitForSingleObject(hMut, 600000);
			Sleep((printTime ? 5 : printTime) * 1000);
			cout << "Готово!" << endl << endl;
		}

		ReleaseMutex(hMut);
	}

	CloseHandle(hMut);
	CloseHandle(hSem);
	return 0;
}

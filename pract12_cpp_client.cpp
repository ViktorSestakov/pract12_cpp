#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Клиент запущен!" << endl << endl;

	const char* mName = "Printer";
	HANDLE hMut = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, mName);
	if (hMut == NULL) {
		cout << "Ошибка октрытия мьютекса!" << endl;
		return GetLastError();
	}

	WaitForSingleObject(hMut, INFINITE);
	cout << "Отпралвено на печать!" << endl;
	ReleaseMutex(hMut);
	cout << "Ожидание завершения печати!" << endl;
	WaitForSingleObject(hMut, INFINITE);
	cout << "Печать завершена!" << endl;
	ReleaseMutex(hMut);

	CloseHandle(hMut);
	return 0;
}
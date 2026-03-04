#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int vibor = 0;
	DWORD prior;
	cout << "Выберите приоритет запускаемого клиента:" << endl;
	cout << "1. Фоновый" << endl;
	cout << "2. Нормальный" << endl;
	cout << "3. Высокий" << endl;
	cout << "Выбор: ";
	cin >> vibor;

	switch (vibor) {
	case 1: prior = IDLE_PRIORITY_CLASS;
		break;
	case 2: prior = NORMAL_PRIORITY_CLASS; 
		break;
	case 3: prior = HIGH_PRIORITY_CLASS; 
		break;
	default: {
		cout << "Ошибка выбора!" << endl;
		cout << "окно закроется через 2 секунды" << endl;
		Sleep(2000);
		return 0;
		break;
		}
	}

	if (!SetPriorityClass(GetCurrentProcess(), prior)) {
		cout << "Ошибка установки приоритета №" << vibor << endl;
		return GetLastError();
	}
	else {
		cout << "Приорите установлен!" << endl;
		Sleep(100);
	}

	system("cls");
	cout << "Клиент запущен!" << endl << endl;

	const char* mName = "PrinterMutMut";
	HANDLE hMut = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, mName);
	const char* sName = "PrinterSemaphore";
	HANDLE hSem = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, sName);

	if (hMut == NULL || hSem == NULL) {
		cout << "Ошибка создания мьютекса" << endl;
		return GetLastError();
	}

	WaitForSingleObject(hMut, INFINITE);
	ReleaseMutex(hMut);
	ReleaseSemaphore(hSem, 1, NULL);

	CloseHandle(hMut);
	CloseHandle(hSem);
	system("cls");
	cout << "Печать отправлена успешно! (окно закроется через 2 секунды)" << endl;
	Sleep(2000);
	return 0;
}

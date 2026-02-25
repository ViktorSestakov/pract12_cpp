#include <iostream>
#include <windows.h>

using namespace std;

const char* mName = "Printer";
HANDLE hMut = CreateMutexA(NULL, FALSE, mName);

HANDLE hProc;
STARTUPINFO si;
PROCESS_INFORMATION pi;

bool client_run;

const wchar_t procName[] = L"C:\\Users\\st310-06\\Desktop\\shsetakov\\sys\\pract12_cpp\\x64\\Debug\\pract12_cpp_client.exe";

void printer() {
	cout << "Принтер запущен!" << endl << endl;
	DWORD lastConnect = GetTickCount64();

	while (true) {
		system("cls");

		cout << "Меню:" << endl;
		cout << "2. Запустить клиент (приоритет: Нормальный)" << endl;
		cout << "3. Запустить клиент (приоритет: Низкий)" << endl;
		cout << "4. Запустить клиент (приоритет: Высокий)" << endl << endl;
		cout << "Выбор: " << endl;

		if (client_run) {
			DWORD WaitMut = WaitForSingleObject(hMut, 1000);

			if (WaitMut == WAIT_OBJECT_0) {
				lastConnect = GetTickCount64();

				cout << "Идет печать!" << endl;

				int printTime = rand() % 15;

				Sleep((printTime ? 5 : printTime) * 1000);

				if (printTime > 10) {
					cout << "Ошибка печати!" << endl;
				}

				cout << "Готово!" << endl << endl;

				ReleaseMutex(hMut);
			}

			if (GetTickCount64() - lastConnect > 600000) {
				cout << "Принтер выключен. Простой больше 10 минут" << endl;
				break;
			}
		}
		else {
			cout << "Ожидание клиента..." << endl;
		}

		int vibor = 0;
		cin >> vibor;

		switch (vibor)
		{
		case 2:
		{
			if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				cout << "Ошибка создания процесса!" << endl;
			}

			hProc = GetCurrentProcess();

			if (!SetPriorityClass(hProc, NORMAL_PRIORITY_CLASS)) {
				cout << "Ошибка присвоения приоритета процессу!" << endl;
			}

			client_run = true;
			break;
		}
		case 3:
		{
			if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				cout << "Ошибка создания процесса!" << endl;
			}

			hProc = GetCurrentProcess();

			if (!SetPriorityClass(hProc, IDLE_PRIORITY_CLASS)) {
				cout << "Ошибка присвоения приоритета процессу!" << endl;
			}
			break;
		}
		case 4:
		{
			if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				cout << "Ошибка создания процесса!" << endl;
			}

			hProc = GetCurrentProcess();

			if (!SetPriorityClass(hProc, HIGH_PRIORITY_CLASS)) {
				cout << "Ошибка присвоения приоритета процессу!" << endl;
			}
			break;
		}
		default:
			cout << "Не верно выбран пункт меню!" << endl;
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	if (hMut == NULL) {
		cout << "Ошибка создания мьютекса!" << endl;
		return GetLastError();
	}

	cout << "Меню:" << endl;
	cout << "1. Запустить принтер" << endl;
	cout << "2. Запустить клиент (приоритет: Нормальный)" << endl;
	cout << "3. Запустить клиент (приоритет: Низкий)" << endl;
	cout << "4. Запустить клиент (приоритет: Высокий)" << endl << endl;
	cout << "Выбор: " << endl;

	int vibor;
	cin >> vibor;

	switch (vibor)
	{
	case 1:
		printer();
		break;
	case 2:
	{
		if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			cout << "Ошибка создания процесса!" << endl;
			return GetLastError();
		}

		hProc = GetCurrentProcess();

		if (!SetPriorityClass(hProc, NORMAL_PRIORITY_CLASS)) {
			cout << "Ошибка присвоения приоритета процессу!" << endl;
			return GetLastError();
		}

		client_run = true;
		break;
	}
	case 3:
	{
		if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			cout << "Ошибка создания процесса!" << endl;
			return GetLastError();
		}

		hProc = GetCurrentProcess();

		if (!SetPriorityClass(hProc, IDLE_PRIORITY_CLASS)) {
			cout << "Ошибка присвоения приоритета процессу!" << endl;
			return GetLastError();
		}
		break;
	}
	case 4:
	{
		if (!CreateProcess(procName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			cout << "Ошибка создания процесса!" << endl;
			return GetLastError();
		}

		hProc = GetCurrentProcess();

		if (!SetPriorityClass(hProc, HIGH_PRIORITY_CLASS)) {
			cout << "Ошибка присвоения приоритета процессу!" << endl;
			return GetLastError();
		}
		break;
	}
	default:
		cout << "Не верно выбран пункт меню!" << endl;
		break;
	}

	CloseHandle(hMut);
	return 0;
}
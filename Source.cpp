#include <stdio.h>
#include <conio.h>
#include <Windows.h>


int main() {
	while (_getch() != 27) {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		HMODULE hModule = LoadLibraryA("ntdll.dll");
		if (hModule == NULL) {
			printf("LoadLibraryA failed. Error: %d\n", GetLastError());
		}
		if (!FreeLibrary(hModule)) {
			printf("FreeLibrary failed. Error: %d\n", GetLastError());
		}

		if (CreateProcessA(NULL,"C:\\Windows\\System32\\notepad.exe", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
			printf("CreateProcessA failed. Error: %d\n", GetLastError());
		}
		if (TerminateProcess(pi.hProcess, 0)) {
			printf("TerminateProcess failed. Error: %d\n", GetLastError());
		}
		HANDLE hFile = CreateFileA("temp", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			printf("CreateFileA failed. Error: %d\n", GetLastError());
		}
		if (WriteFile(hFile, "test", 4, NULL, NULL)) {
			printf("WriteFile failed. Error: %d\n", GetLastError());
		}
		if (ReadFile(hFile, NULL, 4, NULL, NULL)) {
			printf("ReadFile failed. Error: %d\n", GetLastError());
					}
		if (CloseHandle(hFile)) {
			printf("CloseHandle failed. Error: %d\n", GetLastError());
		}
		if (RegSetValueA(HKEY_CURRENT_USER, "test", REG_SZ, "test", 0) != ERROR_SUCCESS) {
			printf("RegSetValueA failed. Error: %d\n", GetLastError());
		}
		printf("complete loop\n");
	}
}
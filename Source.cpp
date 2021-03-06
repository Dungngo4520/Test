#include <stdio.h>
#include <conio.h>
#include <Windows.h>


int main() {
	while (_getch() != 27) {
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		printf("calling LoadLibraryA\n");
		HMODULE hModule = LoadLibraryA("ntdll.dll");
		if (hModule == NULL) {
			printf("LoadLibraryA failed. Error: %d\n", GetLastError());
		}

		if (!FreeLibrary(hModule)) {
			printf("FreeLibrary failed. Error: %d\n", GetLastError());
		}

		printf("calling CreateProcessA\n");
		if (!CreateProcessA(NULL, "C:\\Windows\\System32\\notepad.exe", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
			printf("CreateProcessA failed. Error: %d\n", GetLastError());
		}

		if (!TerminateProcess(pi.hProcess, 0)) {
			printf("TerminateProcess failed. Error: %d\n", GetLastError());
		}

		printf("calling CreateFileA\n");
		HANDLE hFile = CreateFileA("temp", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			printf("CreateFileA failed. Error: %d\n", GetLastError());
		}

		printf("calling WriteFile\n");
		if (!WriteFile(hFile, "test", 4, NULL, NULL)) {
			printf("WriteFile failed. Error: %d\n", GetLastError());
		}


		DWORD fileSize = GetFileSize(hFile, NULL), byteRead = 0;
		char* buffer = (char*)malloc(fileSize);

		printf("calling ReadFile\n");
		if (!ReadFile(hFile, buffer, fileSize, &byteRead, NULL)) {
			printf("ReadFile failed. Error: %d\n", GetLastError());
		}

		if (!CloseHandle(hFile)) {
			printf("CloseHandle failed. Error: %d\n", GetLastError());
		}

		printf("calling RegSetValueA\n");
		if (RegSetValueA(HKEY_CURRENT_USER, "test", REG_SZ, "test", 0) != ERROR_SUCCESS) {
			printf("RegSetValueA failed. Error: %d\n", GetLastError());
		}
		printf("complete loop\n");
	}
}
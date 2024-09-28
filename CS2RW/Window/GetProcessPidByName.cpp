#include "GetProcessPidByName.h"
int try_num;
DWORD GetProcessPidByName(WCHAR  const* procName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap) {
		PROCESSENTRY32W entry;
		entry.dwSize = sizeof(PROCESSENTRY32W);
		if (Process32FirstW(hSnap, &entry)) {
			do {
				if (!_wcsicmp(entry.szExeFile, procName)) {

					CloseHandle(hSnap);
					return entry.th32ProcessID;

				};

			} while (Process32NextW(hSnap, &entry));

		};
		CloseHandle(hSnap);
	};
	return 0;
};


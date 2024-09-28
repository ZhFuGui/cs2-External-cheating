
#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <tchar.h>

DWORD GetProcessPidByName(WCHAR  const* procName);
#pragma once
#include <iostream>
#include <Windows.h>
#include <psapi.h>

HMODULE GetModule(HANDLE hProcess, const char ModuleName[MAX_PATH]);
//字符串类型转换的库
#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>


std::wstring string2wstring(std::string &str);


unsigned long string2DWORD(std::string& str);


std::wstring TakeN_DecimalPlaces(std::wstring& wstr, int n);


std::string LPCWSTR2string(LPCWSTR lpcwszStr);


std::string LPWSTR2string(LPWSTR lpcwszStr);



// TestDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TestDll.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <codecvt>
#include <cstring>
using namespace std;


// 这是导出变量的一个示例
TESTDLL_API int nTestDll=0;

// 这是导出函数的一个示例。
TESTDLL_API int fnTestDll(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 TestDll.h
CTestDll::CTestDll()
{
	return;
}
//类型后面必须使用_stdcall
extern "C"  TESTDLL_API  int _stdcall GetMaxNumber(int a, int b)
{
	nTestDll = a > b ? a * 1000 : b;
	return nTestDll;
}

extern "C" TESTDLL_API void _stdcall ShowMsg(char * text, char* title)
{
	MessageBoxA(NULL,text,title,MB_OK);
}

//extern "C"  TESTDLL_API  string _stdcall UTF8_DECODE(string URLcode)
//{
//	return UTF8_URL_DECODE(URLcode);
//}
//extern "C"  TESTDLL_API  string _stdcall UTF8_ENCODE(char *Chinese)
//{
//	return UTF8_URL_ENCODE(Chinese);
//}


TESTDLL_API const  std::string _stdcall UTF8_DECODE(std::string URLcode)
{

	 //string URLcode
	//utf-8-> unicode-> 中文
	int len = strlen(URLcode.c_str());  
	//int len = sizeof(URLcode);
	 char* temps = new char[len + 1];
	temps[len] = '\0';
	int temps_pos = 0;
	//去掉%号
	for (int i = 0; i < len; ++i)
	{
		if (URLcode[i] != '%')
		{
			temps[temps_pos] = URLcode[i];
			temps_pos++;
		}
	}
	temps[temps_pos] = '\0';
	//  cout << temps << endl;
	int temps_len = strlen(temps);
	int UTF8len = temps_len / 2;
	char* UTF8str = new char[UTF8len + 1];
	UTF8str[UTF8len] = '\0';
	//把字符转换成数字，得到真实的UTF8串
	for (int i = 0; i < UTF8len * 2;)
	{
		char convert[3] = { 0 };
		convert[0] = temps[i++];
		convert[1] = temps[i++];
		char *end;
		int tempint = strtol(convert, &end, 16);
		UTF8str[i / 2 - 1] = tempint;
	}
	//UTF8转换到UTF16
	int wcslen = MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, NULL, 0);
	wchar_t* wszString = new wchar_t[wcslen + 1];
	MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, wszString, wcslen);
	wszString[wcslen] = L'\0';
	//设置区域
	std::wcout.imbue(std::locale("CHS"));
	//    wcout << wszString << endl;
	//把wstring 转为 string
	wstring DecodeStr = wszString;
	std::string OutStr;
	int nLen = (int)DecodeStr.length() * 2;
	OutStr.resize(nLen, ' ');
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)DecodeStr.c_str(), nLen, (LPSTR)OutStr.c_str(), nLen, NULL, NULL);
	delete[]temps;
	delete[]UTF8str;
	delete[] wszString;
	return OutStr;

}
 TESTDLL_API const  std::string _stdcall UTF8_ENCODE(std::string ch)
{
	//中文 -> unicode  -> utf-8
	 int len = strlen(ch.c_str());
	 //int len = sizeof(URLcode);
	char* temps = new char[len + 1];
	const char *Chinese = new char[len + 1];
	Chinese =	ch.c_str();
	wchar_t unicode[128] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, Chinese, strlen(Chinese), unicode, 128);
	unsigned char sz[128] = { 0 };
	WideCharToMultiByte(CP_UTF8, 0, unicode, wcslen(unicode), (LPSTR)sz, 128, 0, 0);
	std::string EncodeStr;
	char SrcStr[128] = { 0 };
	for (int i = 0; i < 128; i++)
	{
		if (sz[i] != NULL)
		{
			sprintf_s(SrcStr, "%%%X", sz[i]);
			EncodeStr += SrcStr;
		}
	}
	transform(EncodeStr.begin(), EncodeStr.end(), EncodeStr.begin(), tolower);
	return EncodeStr;
}

 void main(int argc, char *argv[])
 {
	 string wCharUnicode = "中国";
	 string cCharUtf = UTF8_ENCODE(wCharUnicode);

	 return ;
 }

// char* UnicodeToUtf8(const wchar_t* unicode)
// {
//	 int len;
//	 len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
//	 char *szUtf8 = (char*)malloc(len + 1);
//	 memset(szUtf8, 0, len + 1);
//	 WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
//	 return szUtf8;
// }
//string UTF82WCS(const char* szU8)
// {
//	 //预转换，得到所需空间的大小;
//	 int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
//
//	 //分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
//	 wchar_t* wszString = new wchar_t[wcsLen + 1];
//
//	 //转换
//	 ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
//
//	 //最后加上'\0'
//	 wszString[wcsLen] = '\0';
//
//	 cstring unicodeString(wszString);
//
//	 delete[] wszString;
//	 wszString = NULL;
//
//	 return unicodeString;
// }

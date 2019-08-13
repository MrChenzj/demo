// TestDll.cpp : ���� DLL Ӧ�ó���ĵ���������
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


// ���ǵ���������һ��ʾ��
TESTDLL_API int nTestDll=0;

// ���ǵ���������һ��ʾ����
TESTDLL_API int fnTestDll(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� TestDll.h
CTestDll::CTestDll()
{
	return;
}
//���ͺ������ʹ��_stdcall
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
	//utf-8-> unicode-> ����
	int len = strlen(URLcode.c_str());  
	//int len = sizeof(URLcode);
	 char* temps = new char[len + 1];
	temps[len] = '\0';
	int temps_pos = 0;
	//ȥ��%��
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
	//���ַ�ת�������֣��õ���ʵ��UTF8��
	for (int i = 0; i < UTF8len * 2;)
	{
		char convert[3] = { 0 };
		convert[0] = temps[i++];
		convert[1] = temps[i++];
		char *end;
		int tempint = strtol(convert, &end, 16);
		UTF8str[i / 2 - 1] = tempint;
	}
	//UTF8ת����UTF16
	int wcslen = MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, NULL, 0);
	wchar_t* wszString = new wchar_t[wcslen + 1];
	MultiByteToWideChar(CP_UTF8, NULL, UTF8str, UTF8len, wszString, wcslen);
	wszString[wcslen] = L'\0';
	//��������
	std::wcout.imbue(std::locale("CHS"));
	//    wcout << wszString << endl;
	//��wstring תΪ string
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
	//���� -> unicode  -> utf-8
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
	 string wCharUnicode = "�й�";
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
//	 //Ԥת�����õ�����ռ�Ĵ�С;
//	 int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
//
//	 //����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
//	 wchar_t* wszString = new wchar_t[wcsLen + 1];
//
//	 //ת��
//	 ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
//
//	 //������'\0'
//	 wszString[wcsLen] = '\0';
//
//	 cstring unicodeString(wszString);
//
//	 delete[] wszString;
//	 wszString = NULL;
//
//	 return unicodeString;
// }

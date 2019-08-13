// UnitTest1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <codecvt>
#include <cstring>



using namespace std;


 const  std::string _stdcall URL_DECODE(std::string URLcode)
{

	//string URLcode
	//URL-> ����
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
 const  std::string _stdcall URL_ENCODE(std::string ch)
{
	//���� -> URL
	int len = strlen(ch.c_str());
	//int len = sizeof(URLcode);
	//char* temps = new char[len + 1];
	 char *Chinese = new char[len + 1];
	 strcpy(Chinese, ch.c_str()); 
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

int _tmain(int argc, _TCHAR* argv[])
{
	/*string wCharUnicode = "�й�";
	string cCharUtf = URL_ENCODE(wCharUnicode);
	string ch = URL_DECODE(cCharUtf);*/

	

	return 0;
}


#include "stdafx.h"
#include "TestDll.h"
#include <string>
using namespace std;
//#include "CppUnitTest.h"

//using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDll
{
	//TEST_CLASS(UnitTest)
	//{
	//public:
	//	
	//	TEST_METHOD(TestMethod1)
	//	{
	//		// TODO:  �ڴ�������Դ���
	//	}

	//};
	int main(int argc, char *argv[])
	{
		string wCharUnicode = "�й�";
		string cCharUtf = UTF8_ENCODE(wCharUnicode);

		return 0;
	}
}
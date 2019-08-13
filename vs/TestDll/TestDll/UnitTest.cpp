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
	//		// TODO:  在此输入测试代码
	//	}

	//};
	int main(int argc, char *argv[])
	{
		string wCharUnicode = "中国";
		string cCharUtf = UTF8_ENCODE(wCharUnicode);

		return 0;
	}
}
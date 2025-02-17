#include "pch.h"
#include "CppUnitTest.h"
#include "../../../practice/practice03/practice03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
	TEST_CLASS(practice03test)
	{
	public:
		MathUtils r;
		
		TEST_METHOD(RangeScope)
		{
			Assert::AreEqual(6, r.sumRange(1,3));
		}
	};
}

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
		
		TEST_METHOD(sumRangeScope)
		{
			Assert::AreEqual(6, r.sumRange(1,3));
		}
		TEST_METHOD(sumRangeSameNumber)
		{
			Assert::AreEqual(5, r.sumRange(5, 5));
		}
		TEST_METHOD(sumRangeNegatives)
		{
			Assert::AreEqual(-6, r.sumRange(-3, -1));
		}
	};
}

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
		TEST_METHOD(containsNegativePositiveNums)
		{
			std::vector<int> nums{ 1,2,3 };
			Assert::AreEqual(false, r.containsNegative(nums));
		}
		TEST_METHOD(containsNegativeNegativeNums)
		{
			std::vector<int> nums1{ -1,-2,-3 };
			std::vector<int> nums2{ -1,2,-3 };
			std::vector<int> nums3{ 1,2,-3 };
			Assert::AreEqual(true, r.containsNegative(nums1));
			Assert::AreEqual(true, r.containsNegative(nums2));
			Assert::AreEqual(true, r.containsNegative(nums3));
		}
		TEST_METHOD(containsNegativeEmptyVec)
		{
			std::vector<int> nums;
			Assert::AreEqual(false, r.containsNegative(nums));
		}
	};
}

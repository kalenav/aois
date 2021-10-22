#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3tests
{
	TEST_CLASS(lab3tests)
	{
	public:
		
		TEST_METHOD(checkingSKNF1)
		{
			Assert::IsTrue(isSKNF("(x1 + x2) * (!x1 + x2)", 2));
		}
		TEST_METHOD(checkingSKNF2)
		{
			Assert::IsTrue(isSKNF("(x1 + x2 + x3 + x4 + !x5) * (!x1 + x2 + !x3 + x5 + !x4) * (!x1 + !x2 + !x3 + !x4 + !x5)", 5));
		}
		TEST_METHOD(checkingSKNF3)
		{
			Assert::IsTrue(isSKNF("(x1 + !x3 + x2 + !x6 + x5 + x4) * (!x1 + !x5 + x4 + !x2 + x6 + x3)", 2));
		}
		TEST_METHOD(checkingNotSKNF1)
		{
			Assert::IsFalse(isSKNF("(x1 + x2 + !x3) * (!x1 + x2)", 3));
		}
		TEST_METHOD(checkingNotSKNF2)
		{
			Assert::IsFalse(isSKNF("(x1 + !x2 + !x3 + x4) * (!x1 + !x2 + x3 + !x4) * (!x1 * !x2 + x3 + x4)", 4));
		}
		TEST_METHOD(checkingNotSKNF3)
		{
			Assert::IsFalse(isSKNF("(x1 * x2) + (!x1 * !x2)", 2));
		}
		TEST_METHOD(checkingSDNF1)
		{
			Assert::IsTrue(isSDNF("(x1 * x2) + (!x1 * x2)", 2));
		}
		TEST_METHOD(checkingSDNF2)
		{
			Assert::IsTrue(isSDNF("(x1 * x2 * x3 * x4 * !x5) + (!x1 * x2 * !x3 * x5 * !x4) + (!x1 * !x2 * !x3 * !x4 * !x5)", 5));
		}
		TEST_METHOD(checkingSDNF3)
		{
			Assert::IsTrue(isSDNF("(x1 * !x3 * x2 * !x6 * x5 * x4) + (!x1 * !x5 * x4 * !x2 * x6 * x3)", 2));
		}
		TEST_METHOD(checkingNotSDNF1)
		{
			Assert::IsFalse(isSDNF("(x1 * x2 * !x3) + (!x1 * x2)", 3));
		}
		TEST_METHOD(checkingNotSDNF2)
		{
			Assert::IsFalse(isSDNF("(x1 * !x2 * !x3 * x4) + (!x1 * !x2 * x3 + !x4) + (!x1 * !x2 * x3 * x4)", 4));
		}
		TEST_METHOD(checkingNotSDNF3)
		{
			Assert::IsFalse(isSDNF("(x1 + x2) * (!x1 + !x2)", 2));
		}
		TEST_METHOD(checkingNeighboring1)
		{
			Assert::IsTrue(areNeighboring("!x1 + x2", "!x1 + !x2"));
		}
		TEST_METHOD(checkingNeighboring2)
		{
			Assert::IsTrue(areNeighboring("x1 + !x2 + x4 + !x5", "!x1 + !x2 + x4 + !x5"));
		}
		TEST_METHOD(checkingNeighboring3)
		{
			Assert::IsTrue(areNeighboring("!x1 * !x6 * x3 * !x9 * x4 * !x5 * !x2 * x8 * !x7", "x6 * !x9 * !x1 * x3 * !x5 * x4 * !x2 * !x7 * x8"));
		}
		TEST_METHOD(checkingNotNeighboring1)
		{
			Assert::IsFalse(areNeighboring("!x1 + x2 + x3", "!x1 + !x2"));
		}
		TEST_METHOD(checkingNotNeighboring2)
		{
			Assert::IsFalse(areNeighboring("!x1 + !x2 + x3 + !x4", "x1 + !x2 + x3 * !x4"));
		}
		TEST_METHOD(checkingNotNeighboring3)
		{
			Assert::IsFalse(areNeighboring("x5 * !x9 * x2 * !x1 * !x3 * x4 * x8 * x7 * !x6", "!x5 * !x1 * x8 * !x6 * !x7 * x2 * !x3 * x4 * !x9"));
		}
		TEST_METHOD(concatenateNeighboring1)
		{
			string expected = "x1";
			string actual = concatenateNeighboring("x1 * !x2", "x1 * x2");
			Assert::IsTrue(areEquivalent(expected, actual));
		}
		TEST_METHOD(concatenateNeighboring2)
		{
			string expected = "x1 * !x2";
			string actual = concatenateNeighboring("!x2 * x1 * !x3", "x3 * !x2 * x1");
			Assert::IsTrue(areEquivalent(expected, actual));
		}
		TEST_METHOD(concatenateNeighboring3)
		{
			string expected = "x3 + x5 + !x7";
			string actual = concatenateNeighboring("x5 + !x7 + x2 + x3", "!x2 + !x7 + x3 + x5");
			Assert::IsTrue(areEquivalent(expected, actual));
		}
		TEST_METHOD(concatenateNeighboring4)
		{
			string expected = "!x3 * !x4 * x8";
			string actual = concatenateNeighboring("!x3 * !x5 * !x4 * x8", "!x4 * x5 * !x3 * x8");
			Assert::IsTrue(areEquivalent(expected, actual));
		}
		TEST_METHOD(concatenateNeighboring5)
		{
			string expected = "!x1 * !x2 * x3 * x4 * !x5 * !x7 * x8 * !x9";
			string actual = concatenateNeighboring("!x1 * !x6 * x3 * !x9 * x4 * !x5 * !x2 * x8 * !x7", "x6 * !x9 * !x1 * x3 * !x5 * x4 * !x2 * !x7 * x8");
			Assert::IsTrue(areEquivalent(expected, actual));
		}
		TEST_METHOD(stage1_1)
		{
			string expected = "(x1)";
			string actual = stage1("(x1 * !x2 * x3) + (x1 * x2 * x3) + (x1 * !x2 * !x3) + (x1 * x2 * !x3)");
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(stage1_2)
		{
			string expected = "";
			string actual = stage1("");
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(stage1_3)
		{
			string expected = "";
			string actual = stage1("");
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(stage1_4)
		{
			string expected = "";
			string actual = stage1("");
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(stage1_5)
		{
			string expected = "";
			string actual = stage1("");
			Assert::AreEqual(expected, actual);
		}
	};
}

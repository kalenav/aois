#include "pch.h"
#include "CppUnitTest.h"
#include "../Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab2tests
{
	TEST_CLASS(lab2tests)
	{
	public:
		TEST_METHOD(elInArr)
		{
			int* a = new int[3];
			a[0] = 1;
			a[1] = 5;
			a[2] = 3;
			Assert::IsTrue(elementInArr(a, 5, 3));
		}
		TEST_METHOD(decToBin1)
		{
			int* expected = new int[4];
			expected[0] = 0;
			expected[1] = 1;
			expected[2] = 0;
			expected[3] = 1;
			int* actual = new int[4];
			actual = decimalToBinary(5, 4);
			for(int i = 0; i < 4; i++) Assert::AreEqual(expected[i], actual[i]);
 		}
		TEST_METHOD(decToBin2)
		{
			int* expected = new int[9];
			expected[0] = 0;
			expected[1] = 0;
			expected[2] = 1;
			expected[3] = 0;
			expected[4] = 1;
			expected[5] = 1;
			expected[6] = 1;
			expected[7] = 1;
			expected[8] = 1;
			int* actual = new int[9];
			actual = decimalToBinary(95, 9);
			for (int i = 0; i < 9; i++) Assert::AreEqual(expected[i], actual[i]);
		}
		TEST_METHOD(allocTruthTableMem1)
		{
			int expected[4][8] = 
			{
				{ 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1 },
				{}
			};
			int** actual;
			allocMemoryAndFillTruthTableArguments(&actual, 3, 8);
			for (int i = 0; i < 3; i++) for (int j = 0; j < 8; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(allocTruthTableMem2)
		{
			int expected[6][32] =
			{
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
				{  }
			};
			int** actual;
			allocMemoryAndFillTruthTableArguments(&actual, 5, 32);
			for (int i = 0; i < 5; i++) for (int j = 0; j < 32; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(numeric1)
		{
			int expected[4][8] =
			{
				{ 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1 },
				{ 0, 0, 1, 0, 1, 1, 0, 0 }
			};
			int** actual;
			int* inputs = new int [3];
			inputs[0] = 2;
			inputs[1] = 4;
			inputs[2] = 5;
			actual = numericFormToTruthTable(inputs, 3);
			for (int i = 0; i < 4; i++) for (int j = 0; j < 8; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(numeric2)
		{
			int expected[6][32] =
			{
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
				{ 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0 }
			};
			int** actual;
			int* inputs = new int[13];
			inputs[0] = 0;
			inputs[1] = 4;
			inputs[2] = 5;
			inputs[3] = 7;
			inputs[4] = 8;
			inputs[5] = 9;
			inputs[6] = 15;
			inputs[7] = 17;
			inputs[8] = 18;
			inputs[9] = 23;
			inputs[10] = 26;
			inputs[11] = 27;
			inputs[12] = 28;
			actual = numericFormToTruthTable(inputs, 13);
			for (int i = 0; i < 6; i++) for (int j = 0; j < 32; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(index1)
		{
			int expected[3][4] =
			{
				{ 0, 0, 1, 1 },
				{ 0, 1, 0, 1 },
				{ 1, 0, 0, 1 }
			};
			int** actual = indexFormToTruthTable(9);
			for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(index2)
		{
			int expected[4][8] =
			{
				{ 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1 },
				{ 0, 0, 1, 0, 0, 1, 1, 0 }
			};
			int** actual = indexFormToTruthTable(38);
			for (int i = 0; i < 4; i++) for (int j = 0; j < 8; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(index3)
		{
			int expected[6][32] =
			{
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
				{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 },
				{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
				{ 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1 }
			};
			int** actual = indexFormToTruthTable(164454681);
			for (int i = 0; i < 6; i++) for (int j = 0; j < 32; j++) Assert::AreEqual(expected[i][j], actual[i][j]);
		}
		TEST_METHOD(truthTableToFNF1)
		{
			fullNormalForms expected;
			expected.disjunctive = "";
			expected.conjunctive = "";
		}
		TEST_METHOD(truthTableToFNF2)
		{
			fullNormalForms expected;
			expected.disjunctive = "";
			expected.conjunctive = "";
		}
		TEST_METHOD(truthTableToFNF3)
		{
			fullNormalForms expected;
			expected.disjunctive = "";
			expected.conjunctive = "";
		}
		TEST_METHOD(truthTableToFNF4)
		{
			fullNormalForms expected;
			expected.disjunctive = "";
			expected.conjunctive = "";
		}
		TEST_METHOD(truthTableToFNF5)
		{
			fullNormalForms expected;
			expected.disjunctive = "";
			expected.conjunctive = "";
		}
	};
}

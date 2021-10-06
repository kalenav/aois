#include <iostream>
#include "Header.h"
#include "math.h"
#include <string>

using namespace std;

void push(int** arr, int val, int length)
{
	int* newArr = new int[length + 1];
	for (int i = 0; i < length; i++) newArr[i] = (*arr)[i];
	newArr[length] = val;
	int* dummy = (*arr);
	(*arr) = newArr;
	delete dummy;
}

int* decimalToBinary(int number, int bits)
{
	int* binaryForm = new int[bits];
	int currRemainder = number;
	for (int i = bits - 1; i >= 0; i--)
	{
		binaryForm[i] = currRemainder % 2;
		currRemainder /= 2;
	}
	return binaryForm;
}

bool elementInArr(int* arr, int element, int length)
{
	for (int i = 0; i < length; i++) if (arr[i] == element) return true;
	return false;
}

void allocMemoryAndFillTruthTableArguments(int*** truthTable, int argumentsQuantity, int truthTableWidth)
{
	(*truthTable) = new int* [argumentsQuantity + 1];
	for (int i = 0; i < argumentsQuantity + 1; i++) (*truthTable)[i] = new int [truthTableWidth];
	int* currentInputInBinary;
	for (int j = 0; j < truthTableWidth; j++)
	{
		currentInputInBinary = decimalToBinary(j, argumentsQuantity);
		for (int i = 0; i < argumentsQuantity; i++) (*truthTable)[i][j] = currentInputInBinary[i];
	}
}

void truthTableToFullNormalForms(int** truthTable, int argumentsQuantity, int truthTableWidth)
{
	printf("\nFDNF: ");
	bool firstIteration = true;
	for (int j = 0; j < truthTableWidth; j++)
	{
		if (truthTable[argumentsQuantity][j] != 1) continue;
		if (firstIteration) firstIteration = false;
		else printf(" + ");
		printf("(");
		for (int i = 0; i < argumentsQuantity; i++)
		{
			if (truthTable[i][j] == 0) printf("!");
			printf("x%d", i + 1);
			if (i != argumentsQuantity - 1) printf(" * ");
		}
		printf(")");
	}
	printf("\nFCNF: ");
	firstIteration = true;
	for (int j = 0; j < truthTableWidth; j++)
	{
		if (truthTable[argumentsQuantity][j] != 0) continue;
		if (firstIteration) firstIteration = false;
		else printf(" * ");
		printf("(");
		for (int i = 0; i < argumentsQuantity; i++)
		{
			if (truthTable[i][j] == 1) printf("!");
			printf("x%d", i + 1);
			if (i != argumentsQuantity - 1) printf(" + ");
		}
		printf(")");
	}
	printf("\n\n");
}

void printmatr(int** matr, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d ", matr[i][j]);
		}
		printf("\n");
	}
}

bool threeArgumentLogicalFunctionParser(string input, bool x1, bool x2, bool x3)
{
	if (input[0] == '!')
	{
		string negating;
		for (int i = 1; i < size(input); i++) negating.push_back(input[i]);
		return !threeArgumentLogicalFunctionParser(clearParentheses(negating), x1, x2, x3);
	}
	if (size(input) == 2)
	{
		if (input[1] == '1') return x1;
		if (input[1] == '2') return x2;
		if (input[1] == '3') return x3;
	}
	if (size(input) == 6)
	{
		if (input[2] == '&')
		{
			if ((input[1] == '1' && input[5] == '2') || (input[1] == '2' && input[5] == '1')) return x1 && x2;
			if ((input[1] == '1' && input[5] == '3') || (input[1] == '3' && input[5] == '1')) return x1 && x3;
			if ((input[1] == '2' && input[5] == '3') || (input[1] == '3' && input[5] == '2')) return x2 && x3;
		}
		if (input[2] == '|')
		{
			if ((input[1] == '1' && input[5] == '2') || (input[1] == '2' && input[5] == '1')) return x1 || x2;
			if ((input[1] == '1' && input[5] == '3') || (input[1] == '3' && input[5] == '1')) return x1 || x3;
			if ((input[1] == '2' && input[5] == '3') || (input[1] == '3' && input[5] == '2')) return x2 || x3;
		}
	}
	int bracketsOpened = 0;
	int highestOrderOperatorIndex;
	if (input[0] == '(')
	{
		highestOrderOperatorIndex = 0;
		do
		{
			if (input[highestOrderOperatorIndex] == '(') bracketsOpened++;
			if (input[highestOrderOperatorIndex] == ')') bracketsOpened--;
			highestOrderOperatorIndex++;
		} 		while (bracketsOpened > 0);
	}
	else highestOrderOperatorIndex = 2;
	string leftSide, rightSide;
	for (int i = 0; i < highestOrderOperatorIndex; i++) leftSide.push_back(input[i]);
	for (int i = highestOrderOperatorIndex + 2; i < size(input); i++) rightSide.push_back(input[i]);
	if (input[highestOrderOperatorIndex] == '|')
	{
		return threeArgumentLogicalFunctionParser(clearParentheses(leftSide), x1, x2, x3) || threeArgumentLogicalFunctionParser(clearParentheses(rightSide), x1, x2, x3);
	}
	if (input[highestOrderOperatorIndex] == '&')
	{
		return threeArgumentLogicalFunctionParser(clearParentheses(leftSide), x1, x2, x3) && threeArgumentLogicalFunctionParser(clearParentheses(rightSide), x1, x2, x3);
	}
}

string clearParentheses(string input)
{
	if (input[0] != '(') return input;
	string result;
	for (int i = 1; i < size(input) - 1; i++) result.push_back(input[i]);
	return result;
}

string setNegatingArgumentParentheses(string input)
{
	string result;
	for (int i = 0; i < size(input); i++)
	{
		if (i < size(input) - 2)
		{
			if (input[i] == '!' && input[i + 1] == 'x')
			{
				result += "(!x";
				result.push_back(input[i + 2]);
				result.push_back(')');
				i += 2;
			}
			else result.push_back(input[i]);
		}
		else result.push_back(input[i]);
	}
	return result;
}
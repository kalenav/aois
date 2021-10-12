#include "lab3header.h"
#include <string>

using namespace std;

bool isSKNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int [argumentsQuantity];
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '(')
		{
			for (int j = 0; j < argumentsQuantity; j++) variablesInCurrentParenthesesSet[j] = 0;
		}
		if (input[i] != ' ' && input[i] != '!' && input[i] != 'x' && input[i] != '*') variablesInCurrentParenthesesSet[(int)(input[i] - '0') - 1]++;
		if (input[i] == ')')
		{
			for (int j = 0; j < argumentsQuantity; j++) if (variablesInCurrentParenthesesSet[j] != 1) return false;
		}
	}
	return true;
}

bool isSDNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int[argumentsQuantity];
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '(')
		{
			for (int j = 0; j < argumentsQuantity; j++) variablesInCurrentParenthesesSet[j] = 0;
		}
		if (input[i] != ' ' && input[i] != '!' && input[i] != 'x' && input[i] != '+') variablesInCurrentParenthesesSet[(int)(input[i] - '0') - 1]++;
		if (input[i] == ')')
		{
			for (int j = 0; j < argumentsQuantity; j++) if (variablesInCurrentParenthesesSet[j] != 1) return false;
		}
	}
	return true;
}

bool areNeighboring(string left, string right)
{
	int negatedLeft = 0, negatedRight = 0;
	for (int i = 0; i < size(left); i++) if (left[i] == '!') negatedLeft++;
	for (int i = 0; i < size(right); i++) if (right[i] == '!') negatedRight++;
	if (abs(negatedLeft - negatedRight) == 1) return true;
	else return false;
}

string reduceViaCalculatingMethod(string input)
{
	string result = input;
	result = concatenateStage1(result);
	result = concatenateStage2(result);
	return result;
}

string concatenateNeighboring(string left, string right)
{
	string result;
	string currentPossibleExtraTerm = "";
	string extraTerm;
	int extraTermIndex;
	bool breakUpperCycle = false;
	for (int leftIndex = 0; leftIndex < size(left) - 1; leftIndex++)
	{
		if (left[leftIndex] == '!') currentPossibleExtraTerm += '!';
		if (left[leftIndex] == 'x')
		{
			currentPossibleExtraTerm += 'x';
			currentPossibleExtraTerm += left[leftIndex + 1];
			if (currentPossibleExtraTerm[0] == '!')
			{
				for (int rightIndex = 0; rightIndex < size(right) - 2; rightIndex++)
				{
					if (right[rightIndex] != '!' && right[rightIndex + 1] == 'x' && right[rightIndex + 2] == currentPossibleExtraTerm[2])
					{
						extraTermIndex = leftIndex - 1;
						breakUpperCycle = true;
						break;
					}
					if (rightIndex == size(right) - 3) currentPossibleExtraTerm = "";
				}
			}
			else
			{
				for (int rightIndex = 0; rightIndex < size(right) - 2; rightIndex++)
				{
					if (right[rightIndex] == '!' && right[rightIndex + 1] == 'x' && right[rightIndex + 2] == currentPossibleExtraTerm[1])
					{
						extraTermIndex = leftIndex;
						breakUpperCycle = true;
						break;
					}
					if (rightIndex == size(right) - 3) currentPossibleExtraTerm = "";
				}
			}
		}
		if (breakUpperCycle)
		{
			extraTerm = currentPossibleExtraTerm;
			break;
		}
	}
	int ignoredLeftBorder, ignoredRightBorder;
	bool bordersSet = false;
	if (extraTermIndex == 0)
	{
		ignoredLeftBorder = 0;
		ignoredRightBorder = size(extraTerm) + 2;
		bordersSet = true;
	}
	if (extraTermIndex == size(left) - size(extraTerm))
	{
		ignoredLeftBorder = size(left) - size(extraTerm) - 3;
		ignoredRightBorder = size(left) - 1;
		bordersSet = true;
	}
	if (!bordersSet)
	{
		ignoredLeftBorder = extraTermIndex;
		ignoredRightBorder = extraTermIndex + size(extraTerm) + 2;
	}
	for (int i = 0; i < size(left); i++)
	{
		if (i < ignoredLeftBorder || i > ignoredRightBorder) result += left[i];
	}
	return result;
}

string concatenateStage1(string input)
{
	return input;
}

string concatenateStage2(string input)
{
	return input;
}
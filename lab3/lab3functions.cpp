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
			if (i < size(input) - 2 && input[i + 2] == '+') return false;
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
			if (i < size(input) - 2 && input[i + 2] == '*') return false;
			for (int j = 0; j < argumentsQuantity; j++) if (variablesInCurrentParenthesesSet[j] != 1) return false;
		}
	}
	return true;
}

bool areNeighboring(string left, string right)
{
	int differentArguments = 0;
	for (int leftIndex = 0; leftIndex < size(left) - 2; leftIndex++)
	{
		if (left[leftIndex] == '!')
		{
			for (int rightIndex = 1; rightIndex < size(right); rightIndex++)
			{
				if (right[rightIndex] == left[leftIndex + 2] && (rightIndex - 2 == -1 || right[rightIndex - 2] == ' ')) differentArguments++;
			}
		}
	}
	for (int rightIndex = 0; rightIndex < size(right) - 2; rightIndex++)
	{
		if (right[rightIndex] == '!')
		{
			for (int leftIndex = 1; leftIndex < size(left); leftIndex++)
			{
				if (left[leftIndex] == right[rightIndex + 2] && (leftIndex - 2 == -1 || left[leftIndex - 2] == ' ')) differentArguments++;
			}
		}
	}
	if (differentArguments == 1) return true;
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
				for (int rightIndex = 0; rightIndex < size(right) - 1; rightIndex++)
				{
					if (right[rightIndex] == 'x' && right[rightIndex + 1] == currentPossibleExtraTerm[2] && (rightIndex == 0 || right[rightIndex - 1] != '!'))
					{
						extraTermIndex = leftIndex - 1;
						breakUpperCycle = true;
						break;
					}
					if (rightIndex == size(right) - 2) currentPossibleExtraTerm = "";
				}
			}
			else
			{
				for (int rightIndex = 0; rightIndex < size(right) - 1; rightIndex++)
				{
					if (right[rightIndex] == 'x' && right[rightIndex + 1] == currentPossibleExtraTerm[1] && (rightIndex == 0 || right[rightIndex - 1] == '!'))
					{
						extraTermIndex = leftIndex;
						breakUpperCycle = true;
						break;
					}
					if (rightIndex == size(right) - 2) currentPossibleExtraTerm = "";
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
	string result;
	string* constituents;
	int arrSize = 0, argumentsQuantity = 0;
	bool readingSymbols = false;
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '(') arrSize++;
		if (input[i] != ' ' && input[i] != '!' && input[i] !=  '*' && input[i] != '+' && input[i] != 'x' && (int)(input[i] - '0') > argumentsQuantity) argumentsQuantity = (int)(input[i] - '0');
	}
	constituents = new string [arrSize];
	int currConstituent = -1;
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == ')')
		{
			readingSymbols = false;
		}
		if (readingSymbols) constituents[currConstituent] += input[i];
		if (input[i] == '(')
		{
			readingSymbols = true;
			currConstituent++;
		}
	}
	string left, right;
	string connector = (isSDNF(input, argumentsQuantity)) ? " + " : " * ";
	bool firstIteration = true;
	for (int currLeftConstituent = 0; currLeftConstituent < arrSize; currLeftConstituent++)
	{
		left = constituents[currLeftConstituent];
		for (int currRightConstituent = currLeftConstituent + 1; currRightConstituent < arrSize; currRightConstituent++)
		{
			right = constituents[currRightConstituent];
			if (areNeighboring(left, right))
			{
				if (!firstIteration) result += connector;
				else firstIteration = false;
				result += '(';
				result += concatenateNeighboring(left, right);
				result += ')';
			}
		}
	}
	return result;
}

string concatenateStage2(string input)
{
	return input;
}
#include "lab3header.h"
#include <string>

using namespace std;

bool ifSKNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int [argumentsQuantity];
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '+') return false;
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

bool ifSDNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int[argumentsQuantity];
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '*') return false;
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
#include "lab3header.h"
#include <string>

StringArray::~StringArray()
{
	if(size > 0) delete[] arr;
}

void StringArray::push(string pushing)
{
	string* newArr = new string[++size];
	for (int i = 0; i < size - 1; i++) newArr[i] = arr[i];
	newArr[size - 1] = pushing;
	string* dummy = arr;
	arr = newArr;
	delete[] dummy;
}

bool StringArray::has(string searching)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == searching) return true;
	}
	return false;
}

int StringArray::getSize() { return size; }

string StringArray::operator[](int index)
{
	return arr[index];
}

bool isSKNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int [argumentsQuantity];
	bool insideParentheses = false;
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '(')
		{
			for (int j = 0; j < argumentsQuantity; j++) variablesInCurrentParenthesesSet[j] = 0;
			insideParentheses = true;
		}
		if (input[i] != ' ' && input[i] != '!' && input[i] != 'x' && input[i] != '*') variablesInCurrentParenthesesSet[(int)(input[i] - '0') - 1]++;
		if (insideParentheses && input[i] == '*') return false;
		if (input[i] == ')')
		{
			if (i < size(input) - 2 && input[i + 2] == '+') return false;
			for (int j = 0; j < argumentsQuantity; j++) if (variablesInCurrentParenthesesSet[j] != 1) return false;
			insideParentheses = false;
		}
	}
	return true;
}

bool isSDNF(string input, int argumentsQuantity)
{
	int* variablesInCurrentParenthesesSet = new int[argumentsQuantity];
	bool insideParentheses = false;
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == '(')
		{
			for (int j = 0; j < argumentsQuantity; j++) variablesInCurrentParenthesesSet[j] = 0;
			insideParentheses = true;
		}
		if (input[i] != ' ' && input[i] != '!' && input[i] != 'x' && input[i] != '+') variablesInCurrentParenthesesSet[(int)(input[i] - '0') - 1]++;
		if (insideParentheses && input[i] == '+') return false;
		if (input[i] == ')')
		{
			if (i < size(input) - 2 && input[i + 2] == '*') return false;
			for (int j = 0; j < argumentsQuantity; j++) if (variablesInCurrentParenthesesSet[j] != 1) return false;
			insideParentheses = false;
		}
	}
	return true;
}

bool bothSumOrProduct(string left, string right)
{
	string twoOrMoreArgumentFunction;
	if (size(left) == 2)
	{
		if (size(right) == 2) return true;
		else twoOrMoreArgumentFunction = right;
	}
	else twoOrMoreArgumentFunction = left;
	char connector;
	for (int i = 0; i < size(twoOrMoreArgumentFunction); i++)
	{
		if (twoOrMoreArgumentFunction[i] == '+')
		{
			connector = '+';
			break;
		}
		if (twoOrMoreArgumentFunction[i] == '*')
		{
			connector = '*';
			break;
		}
		if (i == size(twoOrMoreArgumentFunction) - 1) return false;
	}
	for (int i = 2; i < size(left); i++)
	{
		if (left[i] == 'x')
		{
			if (left[i - 1] == '!')
			{
				if (left[i - 3] != connector) return false;
			}
			else if (left[i - 2] != connector) return false;
		}
	}
	for (int i = 2; i < size(right); i++)
	{
		if (right[i] == 'x')
		{
			if (right[i - 1] == '!')
			{
				if (right[i - 3] != connector) return false;
			}
			else if (right[i - 2] != connector) return false;
		}
	}
	return true;
}

bool areNeighboring(string left, string right)
{
	if (!bothSumOrProduct(left, right)) return false;
	int differentArguments = 0;
	int leftArguments = 0, rightArguments = 0;
	for (int leftIndex = 0; leftIndex < size(left) - 1; leftIndex++)
	{
		if (left[leftIndex] == 'x')
		{
			leftArguments++;
			bool leftNegated = (leftIndex > 0 && left[leftIndex - 1] == '!');
			for (int rightIndex = 0; rightIndex < size(right) - 1; rightIndex++)
			{
				if (right[rightIndex] == 'x' && right[rightIndex + 1] == left[leftIndex + 1])
				{
					bool rightNegated = (rightIndex > 0 && right[rightIndex - 1] == '!');
					if(leftNegated ^ rightNegated) differentArguments++;
					break;
				}
				if (rightIndex == size(right) - 2) return false;
			}
		}
	}
	for (int rightIndex = 0; rightIndex < size(right); rightIndex++)
	{
		if (right[rightIndex] == 'x') rightArguments++;
	}
	if (leftArguments != rightArguments) return false;
	if (differentArguments == 1) return true;
	else return false;
}

bool areEquivalent(string left, string right)
{
	if (!bothSumOrProduct(left, right)) return false;
	int leftArguments = 0, rightArguments = 0;
	for (int leftIndex = 0; leftIndex < size(left) - 1; leftIndex++)
	{
		if (left[leftIndex] == 'x')
		{
			leftArguments++;
			bool leftNegated = (leftIndex > 0 && left[leftIndex - 1] == '!');
			for (int rightIndex = 0; rightIndex < size(right) - 1; rightIndex++)
			{
				if (right[rightIndex + 1] == left[leftIndex + 1])
				{
					rightArguments++;
					bool rightNegated = (rightIndex > 0 && right[rightIndex - 1] == '!');
					if (leftNegated ^ rightNegated) return false;
					break;
				}
				if (rightIndex == size(right) - 2) return false;
			}
		}
	}
	if (leftArguments != rightArguments) return false;
	return true;
}

bool aSubfunctionOf(string function, string subfunction)
{
	if (!bothSumOrProduct(function, subfunction)) return false;
	for (int sfIndex = 0; sfIndex < size(subfunction) - 1; sfIndex++)
	{
		if (subfunction[sfIndex] == 'x')
		{
			bool sfargNegated = (sfIndex > 0 && subfunction[sfIndex - 1] == '!');
			for (int fIndex = 0; fIndex < size(function) - 1; fIndex++)
			{
				if (function[fIndex + 1] == subfunction[sfIndex + 1])
				{
					bool fargNegated = (fIndex > 0 && function[fIndex - 1] == '!');
					if (sfargNegated ^ fargNegated) return false;
					break;
				}
				if (fIndex == size(function) - 2) return false;
			}
		}
	}
	return true;
}

string reduceViaCalculatingMethod(string input)
{
	string result = input;
	result = stage1(result);
	return result;
}

string reduceViaTableCalculatingMethod(string input)
{
	string result = input;
	result = stage1(result);
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
					if (right[rightIndex] == 'x' && right[rightIndex + 1] == currentPossibleExtraTerm[1] && rightIndex != 0 && right[rightIndex - 1] == '!')
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

string stage1(string input)
{
	if (size(input) == 2 || size(input) == 3) return input;
	int constituentQuantity = 0;
	for (int i = 0; i < size(input); i++) if (input[i] == '(') constituentQuantity++;
	StringArray constituents;
	string currConstituent;
	bool readingSymbols = false;
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == ')')
		{
			readingSymbols = false;
			if(!constituents.has(currConstituent)) constituents.push(currConstituent);
			currConstituent = "";
		}
		if (readingSymbols) currConstituent += input[i];
		if (input[i] == '(') readingSymbols = true;
	}
	for (int i = 0; i < constituents.getSize(); i++) cout << constituents[i] << endl;
	cout << endl;
	StringArray orderMinusOneImplicants;
	string currImplicant, currLeftConstituent, currRightConstituent;
	int constituentsArraySize = constituents.getSize();
	for (int leftIndex = 0; leftIndex < constituentsArraySize; leftIndex++)
	{
		currLeftConstituent = constituents[leftIndex];
		for (int rightIndex = leftIndex + 1; rightIndex < constituentsArraySize; rightIndex++)
		{
			currRightConstituent = constituents[rightIndex];
			if (areNeighboring(currLeftConstituent, currRightConstituent))
			{
				currImplicant = concatenateNeighboring(currLeftConstituent, currRightConstituent);
				if (!orderMinusOneImplicants.has(currImplicant)) orderMinusOneImplicants.push(currImplicant);
			}
		}
	}
	for (int i = 0; i < orderMinusOneImplicants.getSize(); i++) cout << orderMinusOneImplicants[i] << endl;
	cout << endl;
	StringArray orderMinusTwoImplicants;
	string currLeftImplicant, currRightImplicant;
	int orderMinusOneImplicantsArraySize = orderMinusOneImplicants.getSize();
	for (int leftIndex = 0; leftIndex < orderMinusOneImplicantsArraySize; leftIndex++)
	{
		currLeftImplicant = orderMinusOneImplicants[leftIndex];
		for (int rightIndex = leftIndex + 1; rightIndex < orderMinusOneImplicantsArraySize; rightIndex++)
		{
			currRightImplicant = orderMinusOneImplicants[rightIndex];
			if (areNeighboring(currLeftImplicant, currRightImplicant))
			{
				currImplicant = concatenateNeighboring(currLeftImplicant, currRightImplicant);
				if (!orderMinusTwoImplicants.has(currImplicant)) orderMinusTwoImplicants.push(currImplicant);
			}
		}
	}
	for (int i = 0; i < orderMinusTwoImplicants.getSize(); i++) cout << orderMinusTwoImplicants[i] << endl;
	cout << endl;
	string result;
	string connector;
	for (int i = 0; i < size(input) - 2; i++)
	{
		if (input[i] == ')')
		{
			connector += ' ';
			connector += input[i + 2];
			connector += ' ';
			break;
		}
	}
	int orderMinusTwoImplicantsArraySize = orderMinusTwoImplicants.getSize();
	for (int currIndex = 0; currIndex < orderMinusTwoImplicantsArraySize; currIndex++)
	{
		if (currIndex > 0) result += connector;
		result += '(';
		currImplicant = orderMinusTwoImplicants[currIndex];
		for (int i = 0; i < size(currImplicant); i++) result += currImplicant[i];
		result += ')';
	}
	return result;
}
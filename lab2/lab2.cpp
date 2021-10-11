#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "math.h"
#include "Header.h"
#include <string>

using namespace std;

int main()
{
	int** truthTable;
	int argumentsQuantity;
	int truthTableWidth;
	int choice;
	while (true)
	{
		printf("Choose action:\n\n1. V(n1, n2, ...) to FDNF/FCNF\n2. fi(x1, x2, ...) to FDNF/FCNF\n3. Arbitrary three-argument function to FDNF/FCNF\n4. Exit\n");
		scanf("%d", &choice);
		truthTable = new int*;
		switch (choice)
		{
			case 1:
			{
				int currentInput = -1;
				int inputQuantity = 0;
				int* inputs = new int[0];
				printf("\nInput n1, n2, ...; input -1 when finished\n\n");
				while(true)
				{
					scanf("%d", &currentInput);
					if (currentInput < 0) break;
					push(&inputs, currentInput, inputQuantity++);
				} 				
				if (inputQuantity == 0)
				{
					printf("Please provide the inputs.\n\n");
					break;
				}
				printf("Convert V(");
				for (int i = 0; i < inputQuantity; i++)
				{
					printf("%d", inputs[i]);
					if (i != inputQuantity - 1) printf(", ");
				}
				printf(") to FDNF and FCNF\n");
				truthTable = numericFormToTruthTable(inputs, inputQuantity);
				argumentsQuantity = 1;
				for (int i = 0; i < inputQuantity; i++)
				{
					while (inputs[i] > pow(2, argumentsQuantity) - 1)
					{
						argumentsQuantity++;
					}
				}
				truthTableWidth = pow(2, argumentsQuantity);
				fullNormalForms result = truthTableToFullNormalForms(truthTable, argumentsQuantity, truthTableWidth);
				cout << "FDNF: " << result.disjunctive << endl;
				cout << "FCNF: " << result.conjunctive << endl;
				printf("\n");
				break;
			}
			case 2:
			{
				int index = -1;
				printf("\nInput index: ");
				scanf("%d", &index);
				while (index < 0)
				{
					printf("Input a non-negative index: ");
					scanf("%d", &index);
				}
				truthTable = indexFormToTruthTable(index);
				argumentsQuantity = 0;
				while (index > pow(2, pow(2, argumentsQuantity)) - 1) argumentsQuantity++;
				truthTableWidth = pow(2, argumentsQuantity);
				printf("\nConvert f%d(", index);
				for (int i = 0; i < argumentsQuantity; i++)
				{
					printf("x%d", i + 1);
					if (i != argumentsQuantity - 1) printf(", ");
				}
				printf(") to FDNF and FCNF\n");
				fullNormalForms result = truthTableToFullNormalForms(truthTable, argumentsQuantity, truthTableWidth);
				cout << "FDNF: " << result.disjunctive << endl;
				cout << "FCNF: " << result.conjunctive << endl;
				printf("\n");
				break;
			}
			case 3:
			{
				argumentsQuantity = 3;
				truthTableWidth = 8;
				allocMemoryAndFillTruthTableArguments(&truthTable, argumentsQuantity, truthTableWidth);
				string input;
				printf("\nAvailable operators: '&&', '||' , '!'; parentheses are allowed and welcome\n");
				printf("Please use exactly three arguments; denote them by x1, x2, x3 (you can use the arguments multiple times)\n");
				printf("Chaining operators (e.g. x1||x2||x3) is supported, although such inputs will be evaluated in order, not in priority\n");
				printf("And please refrain from using spaces!\n");
				printf("Input the function: ");
				cin >> input;
				bool x1, x2, x3;
				input = setNegatingArgumentParentheses(input);
				for (int j = 0; j < 8; j++)
				{
					if (truthTable[0][j] == 1) x1 = true;
					else x1 = false;
					if (truthTable[1][j] == 1) x2 = true;
					else x2 = false;
					if (truthTable[2][j] == 1) x3 = true;
					else x3 = false;
					if (threeArgumentLogicalFunctionParser(input, x1, x2, x3)) truthTable[3][j] = 1;
					else truthTable[3][j] = 0;
				}
				printf("\n");
				printmatr(truthTable, argumentsQuantity + 1, truthTableWidth);
				printf("\n");
				fullNormalForms result = truthTableToFullNormalForms(truthTable, argumentsQuantity, truthTableWidth);
				cout << "FDNF: " << result.disjunctive << endl;
				cout << "FCNF: " << result.conjunctive << endl;
				printf("\n");
				break;
			}
			default:
			{
				return 0;
			}
		}
		for (int i = 0; i < argumentsQuantity + 1; i++) delete truthTable[i];
		argumentsQuantity = 0;
		truthTableWidth = 0;
	}
}
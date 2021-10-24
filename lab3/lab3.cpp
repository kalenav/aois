#include <iostream>
#include "../lab2/lab2header.h"
#include "lab3header.h"

using namespace std;

int main()
{
	string input = "(!x1 * !x2 * !x3 * x4) + (!x1 * !x2 * x3 * x4) + (!x1 * x2 * !x3 * x4) + (x1 * !x2 * !x3 * x4) + (x1 * !x2 * x3 * !x4) + (x1 * !x2 * x3 * x4) + (x1 * x2 * !x3 * x4) + (!x1 * !x2 * x3 * !x4)";
	string stage1output = stage1(input);
	reduceViaTableCalculatingMethod(input, stage1output);
}
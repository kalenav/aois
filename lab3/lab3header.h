#include <string>
#include <iostream>

using namespace std;

class StringArray
{
private: 
	string* arr;
	int size = 0;
public:
	void push(string pushing);
	bool has(string searching);
	int getSize();
	string operator[](int index);
};

bool isSKNF(string input, int argumentsQuantity);

bool isSDNF(string input, int argumentsQuantity);

bool areNeighboring(string left, string right);

bool areEquivalent(string left, string right);

string reduceViaCalculatingMethod(string input);

string concatenateNeighboring(string left, string right);

string stage1(string input);

string concatenateStage2(string input);
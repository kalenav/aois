#include <string>
#include <iostream>

using namespace std;

class StringArray
{
private: 
	string* arr;
	int size = 0;
public:
	~StringArray();
	void push(string pushing);
	bool has(string searching);
	int getSize();
	string operator[](int index);
};

bool isSKNF(string input, int argumentsQuantity);

bool isSDNF(string input, int argumentsQuantity);

bool bothSumOrProduct(string left, string right);

bool areNeighboring(string left, string right);

bool areEquivalent(string left, string right);

bool aSubfunctionOf(string function, string subfunction);

string reduceViaCalculatingMethod(string input);

string reduceViaTableCalculatingMethod(string input);

string concatenateNeighboring(string left, string right);

string stage1(string input);
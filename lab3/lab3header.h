#include <string>

using namespace std;

bool isSKNF(string input, int argumentsQuantity);

bool isSDNF(string input, int argumentsQuantity);

bool areNeighboring(string left, string right);

string reduceViaCalculatingMethod(string input);

string concatenateNeighboring(string left, string right);

string concatenateStage1(string input);

string concatenateStage2(string input);
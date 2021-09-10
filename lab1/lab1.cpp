#include <iostream>
#include "lab1.h"

int main()
{
    BinaryNumber num1, num2;
    num1.setNumber(4);
    num2.setNumber(3);
    multiply(num1, num2).getNumber().print();
}

#include <iostream>
#include "lab1.h"

int main()
{
    BinaryNumber num1, num2;
    num1.setNumber(-6);
    num2.setNumber(-5);
    add(num1, num2, 2).getNumber().print();
}

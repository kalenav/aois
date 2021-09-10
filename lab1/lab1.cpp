#include <iostream>
#include "lab1.h"

int main()
{
    BinaryNumber num1, num2;
    num1.setNumber(-327);
    num2.setNumber(62453);
    num1.getNumber().print();
    printf("\n\n");
    num2.getNumber().print();
    printf("\n\n\n\n");
    multiply(num1, num2).getNumber().print();
}

#include <iostream>
#include "lab1.h"

Array& Array::push(int arg)
{
    int* newArray = new int[++length];
    for (int i = 0; i < length - 1; i++) newArray[i] = array[i];
    newArray[length - 1] = arg;
    int* dummy = array;
    array = newArray;
    delete dummy;
    return *this;
}

Array& Array::unshift(int arg)
{
    int* newArray = new int[++length];
    newArray[0] = arg;
    for (int i = 1; i < length; i++) newArray[i] = array[i - 1];
    int* dummy = array;
    array = newArray;
    delete dummy;
    return *this;
}

int Array::pop()
{
    if (length == 0) return -1;
    int* newArray = new int[--length];
    for (int i = 0; i < length; i++) newArray[i] = array[i];
    int toReturn = array[length];
    int* dummy = array;
    array = newArray;
    delete dummy;
    return toReturn;
}

int Array::operator[](int index)
{
    if (index > length - 1) return -1;
    return array[index];
}

void Array::reverse()
{
    int* newArray = new int[length];
    for (int i = 0; i < length; i++) newArray[i] = array[length - 1 - i];
    int* dummy = array;
    array = newArray;
    delete dummy;
}

void Array::print()
{
    for (int i = 0; i < length; i++) printf("%d ", array[i]);
}

Array add(BinaryNumber num1, BinaryNumber num2)
{
    Array result;
    int carrying = 0;
    int temp;
    Array num1arr = num1.getNumber();
    Array num2arr = num2.getNumber();
    for (int i = 15; i >= 0; i--)
    {
        temp = num1arr[i] + num2arr[i] + carrying;
        result.unshift(temp % 2);
        if (temp >= 2) carrying = 1;
        else carrying = 0;
    }
    return result;
}

Array decimalToDirect16bitBin(int input)
{
    Array binary;
    int currentNumerator = input;
    if (input < 0) currentNumerator *= -1;
    do
    {
        binary.push(currentNumerator % 2);
        currentNumerator /= 2;
    }     while (currentNumerator != 0);
    while (binary.length < 15) binary.push(0);
    if (input < 0) binary.push(1);
    else binary.push(0);
    binary.reverse();
    return binary;
}

void BinaryNumber::setNumber(int input)
{
    number = decimalToDirect16bitBin(input);
    if (input < 0) sign = 1;
    else sign = 0;
    code = 0;
}

Array BinaryNumber::getNumber() { return number; }

BinaryNumber& BinaryNumber::convertToDirect()
{
    if (sign == 0 || code == 0) return (*this);
    if (code == 1)
    {
        BinaryNumber one;
        one.setNumber(-1);
        printf("\n\n");
        one.getNumber().print();
        one.convertToComplementary();
        printf("\n\n");
        one.getNumber().print();
        printf("\n\n");
        number = add((*this), one);
        number.print();
        printf("\n\n");
        Array newNumber;
        for (int i = 1; i < 16; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
        number = newNumber.unshift(1);
    }
    if (code == 2)
    {
    }
    code = 0;
    return *this;
}

BinaryNumber& BinaryNumber::convertToComplementary()
{
    if (sign == 0 || code == 1) return (*this);
    if (code == 0)
    {
        Array newNumber;
        for (int i = 1; i < 16; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
        BinaryNumber one;
        one.setNumber(1);
        number = newNumber;
        number = add((*this), one);
        code = 1;
        return *this;
    }
    else return (*this).convertToDirect().convertToComplementary();
}
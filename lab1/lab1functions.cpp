#include <iostream>
#include "lab1.h"

BinaryNumber add(BinaryNumber num1, BinaryNumber num2)
{
    Array result;
    Array num1arrConverted = (num1.getNumber()[0] == 0) ? num1.getNumber() : num1.convertToComplementary().getNumber();
    Array num2arrConverted = (num2.getNumber()[0] == 0) ? num2.getNumber() : num2.convertToComplementary().getNumber();
    int carrying = 0;
    int temp;
    for (int i = 31; i >= 1; i--)
    {
        temp = num1arrConverted[i] + num2arrConverted[i] + carrying;
        result.unshift(temp % 2);
        if (temp >= 2) carrying = 1;
        else carrying = 0;
    }
    if (num1.getNumber()[0] == 1 || num2.getNumber()[0] == 1)
    {
        Array num1arr = num1.getNumber();
        Array num2arr = num2.getNumber();
        for (int i = 1; i < 32; i++)
        {
            if (num1arr[i] > num2arr[i])
            {
                result.unshift(0);
                break;
            }
            if (num1arr[i] < num2arr[i])
            {
                result.unshift(1);
                break;
            }
        }
    }
    else result.unshift(0);
    BinaryNumber res;
    res.setNumber(result, 0);
    return res;
}

BinaryNumber multiply(BinaryNumber num1, BinaryNumber num2)
{
    Array result;
    if ((num1.getNumber()[0] == 1 && num2.getNumber()[0] == 1) || (num1.getNumber()[0] == 0) && num2.getNumber()[0] == 0) result.push(0);
    else result.push(1);
    BinaryNumber* intermediateTerms = new BinaryNumber[31];
    BinaryNumber zero;
    zero.setNumber(0);
    for (int i = 31; i >= 1; i--)
    {
        if (num2.getNumber()[i] == 1)
        {
            intermediateTerms[i].setNumber(num1.getNumber(), num1.getCode());
            intermediateTerms[i].getNumber().shift();
            for (int j = 0; j < i; j++) intermediateTerms[i].getNumber().push(0);
        }
        else intermediateTerms[i] = zero;
    }
    BinaryNumber res;
    for (int i = 0; i < 31; i++) res = add(res, intermediateTerms[i]);
    return res;
}

Array decimalToDirect32bitBin(int input)
{
    Array binary;
    int currentNumerator = input;
    if (input < 0) currentNumerator *= -1;
    do
    {
        binary.push(currentNumerator % 2);
        currentNumerator /= 2;
    }     while (currentNumerator != 0);
    while (binary.length < 31) binary.push(0);
    if (input < 0) binary.push(1);
    else binary.push(0);
    binary.reverse();
    return binary;
}

BinaryNumber::BinaryNumber()
{
    setNumber(0);
}
BinaryNumber::BinaryNumber(BinaryNumber& copying)
{
    Array copied;
    copied = copying.getNumber();
    setNumber(copied, copying.code);
}
void BinaryNumber::setNumber(int input)
{
    number = decimalToDirect32bitBin(input);
    if (input < 0) sign = 1;
    else sign = 0;
    code = 0;
}
void BinaryNumber::setNumber(Array input, int givenCode)
{
    for (int i = 0; i < 32; i++) number.push(input[i]);
    if (input[0] == 0) sign = 0;
    else sign = 1;
    code = givenCode;
}
Array BinaryNumber::getNumber() { return number; }
int BinaryNumber::getCode() { return code; }
BinaryNumber& BinaryNumber::convertToDirect()
{
    if (sign == 0 || code == 0) return (*this);
    if (code == 1)
    {
        BinaryNumber one;
        one.setNumber(-1);
        one.convertToComplementary();
        number = add((*this), one).getNumber();
        Array newNumber;
        for (int i = 1; i < 32; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
        number = newNumber.unshift(1);
    }
    if (code == 2)
    {
        Array newNumber;
        for (int i = 0; i < 16; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
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
        for (int i = 0; i < 32; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
        BinaryNumber one;
        one.setNumber(1);
        number = newNumber;
        number = add((*this), one).getNumber();
        code = 1;
        return *this;
    }
    else return (*this).convertToDirect().convertToComplementary();
}
BinaryNumber& BinaryNumber::convertToReverse()
{
    if (sign == 0 || code == 2) return *this;
    if (code == 0)
    {
        Array newNumber;
        for (int i = 0; i < 32; i++)
        {
            if (number[i] == 0) newNumber.push(1);
            else newNumber.push(0);
        }
        code = 2;
        return *this;
    }
    else return  (*this).convertToDirect().convertToReverse();
}
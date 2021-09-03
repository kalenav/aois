#include <iostream>

class Array
{
private:
    int* array;
public:
    int length = 0;
    Array& push(int arg)
    {
        int* newArray = new int[++length];
        for (int i = 0; i < length - 1; i++) newArray[i] = array[i];
        newArray[length - 1] = arg;
        int* dummy = array;
        array = newArray;
        delete dummy;
        return *this;
    }
    int pop()
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
    Array& unshift(int arg)
    {
        int* newArray = new int[++length];
        newArray[0] = arg;
        for (int i = 1; i < length; i++) newArray[i] = array[i - 1];
        int* dummy = array;
        array = newArray;
        delete dummy;
        return *this;
    }
    int operator[](int index)
    {
        if (index > length - 1) return -1;
        return array[index];
    }
    void reverse()
    {
        int* newArray = new int[length];
        for (int i = 0; i < length; i++) newArray[i] = array[length - 1 - i];
        int* dummy = array;
        array = newArray;
        delete dummy;
    }
    void print()
    {
        for (int i = 0; i < length; i++) printf("%d ", array[i]);
    }
};

Array decimalToDirect8bitBin(int input)
{
    Array binary;
    int currentNumerator = input;
    if (input < 0) currentNumerator *= -1;
    do
    {
        binary.push(currentNumerator % 2);
        currentNumerator /= 2;
    }     
    while (currentNumerator != 0);
    while (binary.length < 15) binary.push(0);
    if (input < 0) binary.push(1);
    else binary.push(0);
    binary.reverse();
    return binary;
}

class BinaryNumber
{
private:
    Array number;
    int code = 0;
    int sign = 0;
public:
    void setNumber(int input) 
    { 
        number = decimalToDirect8bitBin(input); 
        if (input < 0) sign = 1;
        else sign = 0;
    }
    void setCode(int input) 
    { 
        if (input < 0 || input > 2) return; 
        code = input;
    }
    Array getNumber() { return number; }
    void convertToDirect()
    {
        if (sign == 0 || code == 0) return;
        switch (code)
        {
        case 1:
        {

        }
        }
    }
};

class FloatingPointBinaryNumber
{
private:
    Array mantissaBin;
    Array orderBin;
    int sign;
    int mantissaDec;
public:
    void setMantissa(int input) { mantissaDec = input; }
    void setSign(int input)
    {
        if (input != 0 && input != 1) return;
        else sign = input;
    }
    void setOrder(Array order)
    {
        while (order.length > 0) orderBin.push(order.pop());
        orderBin.reverse();
    }
    void convertMantissaToBin() { mantissaBin = decimalToDirect8bitBin(mantissaDec); }
    int getSign() { return sign; }
    Array getOrder() { return orderBin; }
    Array getMantissa() { return mantissaBin; }
};

Array add(BinaryNumber num1, BinaryNumber num2)
{
    Array result;
    int carrying = 0;
    int temp;
    for (int i = 15; i >= 0; i--)
    {
        temp = num1.getNumber()[i] + num2.getNumber()[i] + carrying;
        result.unshift(temp % 2);
        if (temp >= 2) carrying = 1;
        else carrying = 0;
    }
    return result;
}

int main()
{
    BinaryNumber num1;
    BinaryNumber num2;
    num1.setNumber(5);
    num2.setNumber(12);
    num1.getNumber().print();
    printf("\n");
    num2.getNumber().print();
    printf("\n");
    add(num1, num2).print();
}

class Array
{
private:
    int* array;
public:
    int length = 0;
    Array& push(int arg);
    int pop();
    Array& unshift(int arg);
    int operator[](int index);
    void reverse();
    void print();
};

class BinaryNumber
{
private:
    Array number;
    int code;
    int sign;
public:
    void setNumber(int input);
    void setCode(int input);
    Array getNumber();
    BinaryNumber& convertToDirect();
    BinaryNumber& convertToComplementary();
};

class FloatingPointBinaryNumber
{
private:
    Array mantissaBin;
    Array orderBin;
    int sign;
    int mantissaDec;
public:
    void setMantissa(int input);
    void setSign(int input);
    void setOrder(Array order);
    void convertMantissaToBin();
    int getSign();
    Array getOrder();
    Array getMantissa();
};

Array decimalToDirect16bitBin(int input);

Array add(BinaryNumber num1, BinaryNumber num2);


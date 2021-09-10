#include <iostream>
#include "array.h"

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
Array::Array()
{
    array = new int;
    length = 0;
}
Array::Array(const Array& copying)
{
    (*this).length = copying.length;
    for (int i = 0; i < copying.length; i++) (*this).array[i] = copying.array[i];
}
void Array::operator=(const Array& copying)
{
    for (int i = 0; i < copying.length; i++) (*this).push(copying.getNthElement(i));
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
int Array::shift()
{
    if (length == 0) return -1;
    int* newArray = new int[--length];
    for (int i = 1; i <= length; i++) newArray[i] = array[i];
    int toReturn = array[0];
    int* dummy = array;
    array = newArray;
    delete dummy;
    return toReturn;
}
int Array::operator[](int index)
{
    if (index > length - 1 || index < 0) return -1;
    else return array[index];
}
int Array::getNthElement(int index)
{
    if (index > length - 1 || index < 0) return -1;
    else return array[index];
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
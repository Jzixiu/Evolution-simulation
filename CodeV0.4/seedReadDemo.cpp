#include <iostream>
#include <vector>
#include <array>
#include <Math.h>
#define SeedLen 32
#define ARRLEN 16
using namespace std;

long long readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end)
{
    long long temp = 0;
    for (int n = start - 1; n < end; n++)
    {
        temp += arr[n] * pow(10, (end - n - 1));
    }
    return temp;
}

int main()
{
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator it;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator iter;
    
}

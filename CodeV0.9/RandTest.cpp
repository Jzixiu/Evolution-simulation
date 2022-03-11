#include<iostream>
using namespace std;
#define halfRM RAND_MAX/2

int Rand()
{
    return rand()-halfRM;
}

int RangeRand(int min, int max)//Return a random number within given interval
{
    int k=Rand();
    return (k>max)?((k-min)%(max-min+1)+min):((k-max)%(max-min+1)+max);
}

int main()
{
    int value=0;
    for(int temp=0;temp<10000000;temp++)
    {
        value+=RangeRand(-1,1);
        cout<<value<<endl;
    }
    return 0;
}
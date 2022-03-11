#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <array>
#include <math.h>
#define SeedLen 32
#define ARRLEN 16
using namespace std;

class SYS
{
private:
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator it;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator iter;
    long long readSeed(array<int,ARRLEN>arr,unsigned start,unsigned end);
public:
    void initialize();
    void AutoGenSeed();
    SYS();
    ~SYS();
};

long long SYS::readSeed(array<int,ARRLEN>arr,unsigned start,unsigned end)
{
    long long temp=0;
    for(int n=start-1;n<end;n++)
    {
        temp+=arr[n]*pow(10,(end-n-1));
    }
    return temp;
}

void SYS::initialize()
{
    string tempInput;
    cout << "Enter the (1/32) Line of Seed. Enter'/' for Auto Generate:";
    cin >> tempInput;
    if (tempInput == "/")
    {
        AutoGenSeed();
    }
    else
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
        }
        seed.push_back(arr);
        for (int j = 1; j < SeedLen; j++)
        {
            cin >> tempInput;
            for (int i = 0; i < ARRLEN; i++)
            {
                arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
            }
            seed.push_back(arr);
        }

        for (iter = seed.begin(); iter != seed.end(); ++iter)
        {
            for (it = iter->begin(); it != iter->end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
}

void SYS::AutoGenSeed()
{
    unsigned time_stamp = time(NULL);
    cout << "Using time stamp:" << time_stamp << " to generate seed." << endl;
    srand(time_stamp);
    for (int temp = 0; temp < SeedLen; temp++)
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = rand() % 10; //todo
        }
        seed.push_back(arr);
    }
    cout << "array values: "<<endl;
    for (iter = seed.begin(); iter != seed.end(); ++iter)
    {
        for (it = iter->begin(); it != iter->end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

SYS::SYS()
{
    for (int i = 0; i < ARRLEN; i++)
    {
        arr[i] = 0;
    }
    cout << "Class SYS constructed." << endl;
}

SYS::~SYS()
{
    ;
}

int main()
{
    SYS sysctrl;
    sysctrl.initialize();
    return 0;
}

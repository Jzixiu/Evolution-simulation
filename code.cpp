#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <array>
#include <math.h>
#include <map>
#define SeedLen 32
#define ARRLEN 16
using namespace std;

class SYS
{
private:
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator arr_iter;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator vector_iter;
    map<string, unsigned long long> mp;
    map<string, unsigned long long>::iterator map_iter;
    long long readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end);
    void seedResolution();

public:
    void initialize();
    void AutoGenSeed();
    SYS();
    ~SYS();
};

long long SYS::readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end)
{
    long long temp = 0;
    for (int n = start - 1; n < end; n++)
    {
        temp += arr[n] * pow(10, (end - n - 1));
    }
    return temp;
}

void SYS::seedResolution()
{
    vector_iter=seed.begin();//read First Row
    mp.insert(make_pair("HuDongShunXu",readSeed(*vector_iter,1,1)));
    mp.insert(make_pair("GeTi",readSeed(*vector_iter,2,2)));
    mp.insert(make_pair("InitCrtAmount",readSeed(*vector_iter,3,4)));

    vector_iter++;//read Second Row
    mp.insert(make_pair("Max_x",readSeed(*vector_iter,1,16)));

    vector_iter++;//read Third Row
    mp.insert(make_pair("Max_y",readSeed(*vector_iter,1,16)));


    for (map_iter = mp.begin(); map_iter != mp.end(); map_iter++)
    {
        cout<<map_iter->first<<"->"<<map_iter->second<<endl;
    }
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

        for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
        {
            for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
            {
                cout << *arr_iter << " ";
            }
            cout << endl;
        }
    }
    seedResolution();
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
    cout << "array values: " << endl;
    for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
    {
        for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
        {
            cout << *arr_iter << " ";
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
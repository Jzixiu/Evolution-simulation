#include <iostream>
#include <array>
#include <vector>
using namespace std;
int main(void)
{
    array<int, 16> arr;
    array<int, 16>::iterator it;
    vector<array<int, 16>> seed;
    vector<array<int, 16>>::iterator iter;
    for (int temp=0;temp<16;temp++)
    {
        for (it = arr.begin(); it <= arr.end(); it++)
        {
            *it = rand() % 10; //todo
        }
        seed.push_back(arr);
    }
    cout << "array values: ";
    for (iter = seed.begin(); iter != seed.end(); ++iter)
    {
        for (it = iter->begin(); it != iter->end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    return 0;
}
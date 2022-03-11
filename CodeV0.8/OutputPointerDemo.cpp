#include <iostream>
using namespace std;

int main()
{
    int *p=new int;
    cout<<p;
    delete p;

    return 0;
}
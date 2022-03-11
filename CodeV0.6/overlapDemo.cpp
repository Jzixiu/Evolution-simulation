#include <iostream>
using namespace std;

struct range
{
    int rangeLeft;
    int rangeRight; 
};

range overlap(int a, int b, unsigned short n)
{
    range temp;
    if(a>b)
    {
        temp.rangeLeft=a-n;
        temp.rangeRight=b+n;
    }
    else
    {
        temp.rangeLeft=b-n;
        temp.rangeRight=a+n;
    }
    return temp;
}

int main()
{
    range result=overlap(1,2,1);
    cout<<result.rangeLeft<<","<<result.rangeRight;
    return 0;
}
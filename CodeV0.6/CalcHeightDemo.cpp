#include<iostream>
using namespace std;
struct range
{
    int rangeLeft;
    int rangeRight;
};
struct coordinate
{
    unsigned long long X;
    unsigned long long Y;
};

void CalcH_LB(coordinate cordi)
{
    cout << "LB(" << cordi.X << "," << cordi.Y << ")";
}

void CalcH_L(coordinate cordi)
{
    cout << "L(" << cordi.X << "," << cordi.Y << ")" << endl;
}

void CalcH_B(coordinate cordi)
{
    cout << "B(" << cordi.X << "," << cordi.Y << ")" << endl;
}

range overlap(int a, int b, unsigned short n)
{
    range temp;
    if (a > b)
    {
        temp.rangeLeft = a - n;
        temp.rangeRight = b + n;
    }
    else
    {
        temp.rangeLeft = b - n;
        temp.rangeRight = a + n;
    }
    return temp;
}

void rands()
{
    cout<<rand();
}

int rangeRand(range tRg)
{
    return rand() % (abs(tRg.rangeRight - tRg.rangeLeft) + 1) + (abs(tRg.rangeLeft) < abs(tRg.rangeRight) ? tRg.rangeLeft : tRg.rangeRight);
}

int main()
{
    srand(100);
    return 0;
}
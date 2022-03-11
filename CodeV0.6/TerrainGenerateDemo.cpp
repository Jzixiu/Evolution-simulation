#include <iostream>
using namespace std;
#define Xmax 16
#define Ymax 8

struct coordinate
{
    unsigned long long X;
    unsigned long long Y;
};

void CalcH_LB(coordinate cordi)
{
    cout << "LB(" << cordi.X << "," << cordi.Y << ")" << endl;
}

void CalcH_L(coordinate cordi)
{
    cout << "L(" << cordi.X << "," << cordi.Y << ")" << endl;
}

void CalcH_B(coordinate cordi)
{
    cout << "B(" << cordi.X << "," << cordi.Y << ")" << endl;
}

int main() //m indicate y, n indicate x.
{
    coordinate cordi;
    unsigned long long m, n;
    if (Ymax > Xmax)
    {
        cout << "Ymax>Xmax" << endl;
        for (m = 2; m <= Xmax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 0; n < m - 2; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        cout << "change" << endl;
        for (m = Xmax + 1; m <= Ymax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 1; n < Xmax; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
        cout << "change" << endl;
        for (m = 2; m <= Xmax; m++)
        {
            cordi.X = m;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (n = 0; n < Xmax - m; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
    }
    else
    {
        cout << "else" << endl;
        for (m = 2; m <= Ymax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 0; n < m - 2; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        cout << "change" << endl;
        for (n = 2; n <= Xmax - Ymax + 1; n++)
        {
            cordi.X = n;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (m = 0; m < Ymax - 2; m++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        cout << "change" << endl;
        for (n = Xmax - Ymax + 2; n <= Xmax; n++)
        {
            cordi.X = n;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (m = 0; m < Xmax - n; m++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
    }

    return 0;
}
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
    int m, n, x;
    srand(time(NULL));
    while (1)
    {
        cin >> m;
        cin >> n;
        for (x = 0; x < 100; x++)
        {
            cout << rand() % (abs(n - m) + 1) + (abs(m) < abs(n) ? m : n) << endl;
        }
    }
    return 0;
}
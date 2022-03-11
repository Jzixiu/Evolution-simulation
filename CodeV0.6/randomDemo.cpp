#include <iostream>
#include <time.h>
using namespace std;
int main()
{
    int m, n, x;
    srand(time(NULL));
    cin >> m;
    cin >> n;
    cout << rand() % (abs(n - m) + 1) + (abs(m) < abs(n) ? m : n) << endl;
    return 0;
}
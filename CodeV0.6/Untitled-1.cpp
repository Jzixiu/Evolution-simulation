#include <iostream>
#include <array>
using namespace std;


int main()
{
    int **px,Xmax=10,Ymax=15;
    px=new int*[Xmax];
    for(int temp=0;temp<Xmax;temp++)
    {
        px[temp]=new int[Ymax];
        for(int tmp=0;tmp<10;tmp++)
        {
            px[temp][tmp]=0;
        }
    }
    px[8][2]=82;//test
    cout<<px[8][2];//test
    return 0;
}
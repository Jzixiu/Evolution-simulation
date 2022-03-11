#include <vector>
#include <iostream>
using namespace std;

int rangeRand(int min, int max)
{
    return rand() % (abs(max - min) + 1) + (abs(min) < abs(max) ? min : max);
}

int main()
{
    vector<int>::iterator iter;
	vector<int> original;
    for(int temp=0;temp<10;temp++)
    {
        original.push_back(temp);
    }
    vector<int> temp1;
    vector<int> temp2;

    temp1=original;
    for(iter=temp1.begin();iter!=temp1.end();iter++)
    {
        cout<<*iter<<endl;
    }

    int temp;
    while(temp1.size()!=0)
    {
        iter=temp1.begin()+rangeRand(0,temp1.size());
        temp2.push_back(*iter);
        temp1.erase(iter);
    }
    cout<<endl;
    for(iter=temp2.begin();iter!=temp2.end();iter++)
    {
        cout<<*iter<<endl;
    }
    system("pause");
}
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{

    vector<int> iVec;

    vector<int>::iterator it;
    int i;

    for( i=0;i<10;i++)

        iVec.push_back(i);

    for( i=0;i<iVec.size();i++)
        cout<<iVec[i]<<ends;
    cout<<endl;

    for(it=iVec.begin();it!=iVec.end();++it)

    {

        if(*it ==4 || *it == 5)

        {

            it=iVec.erase(it);
            it--;

        }

    }

   for( i=0;i<iVec.size();i++)
        cout<<iVec[i]<<ends;
    cout<<endl;
    return 0;
}
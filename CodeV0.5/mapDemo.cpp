#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<string, unsigned long long> mp;
    map<string, unsigned long long>::iterator it;
    mp.insert(make_pair("initCrtAmo",123));
    mp.insert(make_pair("hudong",4));
    mp.insert(make_pair("geti",4));
    mp.insert(make_pair("max_x",9999999999999999));
    mp.insert(make_pair("max_y",67899));
    it=mp.find("max_x");
    cout<<it->first<<"->"<<it->second;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        cout<<it->first<<"->"<<it->second;
    }
    return 0;
}
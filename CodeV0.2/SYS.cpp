#include "SYS.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

SYS::SYS()
{
    cout << "test map begin..." << endl;
}

void SYS::AutoGenSeed()
{
    srand(time(NULL));
    string strTemp = dec2hex(rand()), seedTemp;
    for (int i = 0; i < 32; i++)
    {
        do
        {
            seedTemp = seedTemp + dec2hex(rand());
        } while (seedTemp.size() < 16);
        seed.push_back(seedTemp);
        seedTemp = "";
    }
}

bool SYS::initialize()
{
    string temp;
    cout << "Enter(1/32) (enter '/' to Auto Generate):";
    cin >> temp;
    if (temp == "/")
    {
        cout << "Auto generating" << endl;
        AutoGenSeed();
        cout << "Seed generated:" << endl;
        for (seedIter = seed.begin(); seedIter != seed.end(); seedIter++)
        {
            cout << *seedIter << endl;
        }
        return true; //Seed by machine must be valid
    }
    else if (temp.size() == 16)
    {
        string seedTemp;
        for (int i = 1; i < 32; i++)
        {
            cin>>seedTemp;
            if(seedTemp.size()==16)
            {
                seedTemp=(dec2hex(seedTemp));
                cout<<seedTemp;
                seed.push_back(seedTemp);
                seedTemp = "";
            }
        }
    }
    cout << "Seed invalid" << endl;
    return false;
}

string SYS::getSeed(unsigned temp)
{
    return seed[temp];
}

string SYS::dec2hex(int i) //trans
{
    stringstream ioss;                                 //定义字符串流
    string s_temp;                                     //存放转化后字�?
    ioss << resetiosflags(ios::uppercase) << hex << i; //以十六制(小写)形式输出
    ioss >> s_temp;
    return s_temp;
}

string SYS::dec2hex(string t_string) //trans
{
    stringstream ioss;                                 //定义字符串流
    string result;                             //存放转化后字�?
    char s_temp;
    for(int i=0;i<t_string.length();i++)
    {
        ioss << resetiosflags(ios::uppercase) << hex << t_string[i]; //以十六制(小写)形式输出
        ioss >> s_temp;
        result+=s_temp;
        s_temp="";
    }
    
    
    return result;
}
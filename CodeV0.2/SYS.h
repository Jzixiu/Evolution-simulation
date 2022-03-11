#ifndef CLASSSYS_H
#define CLASSSYS_H
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
using namespace std;
class SYS
{
    private:
    vector<array<int,16>> seed;
    vector<array<int,16>>::iterator seedIter;
    public:
    void AutoGenSeed();
    bool initialize();
    string getSeed(unsigned temp);
    string dec2hex(int i);
    string dec2hex(string i);
    SYS();
};


#endif
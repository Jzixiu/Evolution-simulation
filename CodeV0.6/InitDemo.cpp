#include <iostream>
#include <fstream>
using namespace std;

class SYS
{
public:
    SYS();
    ~SYS();
    fstream Tfile;

private:
};

SYS::SYS() : Tfile("C:\\Users\\hp\\Desktop\\Code\\LOG\\test.txt", ios::app) {}

SYS::~SYS()
{
    ;
}

int main()
{
    SYS mysys;
    for (int temp = 0; temp < 10; temp++)
    {
        mysys.Tfile << "testLOG" << __TIMESTAMP__ << endl;
    }

    return 0;
}
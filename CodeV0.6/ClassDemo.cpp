#include <iostream>
#include <fstream>
using namespace std;

class SYS
{
    public:
    void asd();
    SYS();
    SYS(string fPath);
    ~SYS();
    bool is_file_open()
    {
        return fout.is_open();
    }
    private:
    fstream fout;
};

void SYS::asd()
{
    cout<<"asd"<<endl;
};

SYS::SYS()
{
    cout<<"constructed."<<endl;
};

SYS::~SYS()
{
    cout<<"destructed."<<endl;
}

int main()
{
    SYS sys("c:\\tmp\\test.txt");
    if (sys.is_file_open())
    {
        std::cout << "file open ok\n";
    }
    else
    {
        std::cout << "file open error\n";
        return -1;
    }
    /*CWriter file("c:\\tmp\\test.txt");
    std::cout << file.GetPath() << "\n";

    if (file.is_file_open())
    {
        std::cout << "file open ok\n";
    }
    else
    {
        std::cout << "file open error\n";
        return -1;
    }

    file.AddLog("1234");
    file.AddLog("1234");*/
    return 0;
}
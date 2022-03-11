#include <iostream>
using namespace std;

class SYS
{
    public:
    static void display();
    private:
};

void SYS::display()
{
    cout<<"hello world";
}

int main()
{
    SYS::display();
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

class skill
{
    public:
    bool flag;
    virtual void active();
};

class fly: skill
{
    void active()
    {
        cout<<"fly active";
    }
};

class heal: skill
{
    void active()
    {
        cout<<"heal active";
    }
};



class baseC
{
    public:
    vector<skill> Skill;
};


int main()
{
    baseC base;
    fly Fly;
    base.Skill.push_back();

    return 0;
}
#include <iostream>
using namespace std;

class Base_Creature
{
    public:
    Base_Creature();
    ~Base_Creature();    
    struct heal
    {
        float *address;
        void active();
        bool flag;
    } HEAL;
    
    float damage;
    float hp;
    float speed;
};

Base_Creature::Base_Creature()
{
    HEAL.address=&hp;
};

Base_Creature::~Base_Creature() {};

void Base_Creature::heal::active()
{
    *address+=3;
}

int main()
{
    Base_Creature base;
    cout<<base.hp;

    if(base.HEAL.flag) {base.HEAL.active();};

    return 0;
}
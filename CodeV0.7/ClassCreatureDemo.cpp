#include <iostream>
#include <vector>
using namespace std;

class SYS
{
    vector<Base_Creature> creature_list;
};

class Base_Creature
{
    public:
    Base_Creature();
    ~Base_Creature();

    protected:
    float damage;
    float hp;
    float speed;
};

class horse: Base_Creature
{
    
};

int main()
{

    return 0;
}
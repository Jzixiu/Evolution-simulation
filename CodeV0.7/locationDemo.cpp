#include <iostream>
#include <array>
#include <vector>
using namespace std;
typedef unsigned long long ULL;


enum Gene_name
{
    STRENTH,
    ARMOR,
    RUN
};

struct gene
{
    Gene_name Name;
    bool flag;
};

class base_creature
{
public:
    base_creature(int temp1, int temp2);
    ~base_creature(){};
    void insertGene(gene temp);
    void insertGene(int temp1, int temp2);
    //private:
    vector<gene> GENE;
    vector<gene>::iterator iter;
    float damage;
    float hp;
    float speed;
};

base_creature::base_creature(int temp1, int temp2)
{
    gene *p = new gene;
    p->Name = Gene_name(temp1);
    p->flag = temp2;
    GENE.push_back(*p);
    damage = 1;
    hp = 1;
    speed = 1;
}

void base_creature::insertGene(gene temp)
{
    for (iter = GENE.begin(); iter != GENE.end(); iter++)
    {
        if (iter->Name == temp.Name)
        {
            iter->flag = temp.flag;
            return;
        } //if new gene name conflicts
    }
    GENE.push_back(temp);
}

void base_creature::insertGene(int temp1, int temp2)
{
    gene *p = new gene;
    p->Name = Gene_name(temp1);
    p->flag = temp2;
    insertGene(*p);
    delete p;
}

class SYS
{
public:
    SYS(){};
    ~SYS(){};
    static int rangeRand(int left, int right);
    void insertCreature(base_creature temp);

private:
    vector<base_creature> creature;
    base_creature ***location;
};




int SYS::rangeRand(int left, int right)
{
    return rand() % (abs(right - left) + 1) + (abs(left) < abs(right) ? left : right);
}

void SYS::insertCreature(base_creature temp)
{
    creature.push_back(temp);
}


int main()
{
    srand(time(0));
    SYS sysctrl;
    ULL Max_x, Max_y;

    
    base_creature *p;
    for (int temp = 0; temp < 10; temp++)
    {
        p = new base_creature(SYS::rangeRand(0, 1), SYS::rangeRand(0, 2));
        p->insertGene(SYS::rangeRand(0, 1), SYS::rangeRand(0, 2));
        
        sysctrl.insertCreature(*p);
    }

    return 0;
}
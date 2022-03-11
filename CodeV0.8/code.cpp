#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <array>
#include <math.h>
#include <map>
#include <set>
#include <ctime>
#include <fstream>
#define SeedLen 32
#define ARRLEN 16
#define LOG_PATH "C:\\Users\\hp\\Desktop\\Code\\LOG"
#define LOG_FILENAME "Log"
#define mode AUTO
using namespace std;
typedef unsigned int UI;
//define

UI idx=1;

struct coordinate
{
    UI X;
    UI Y;
};

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
    base_creature(int temp1, int temp2, UI tX, UI ty, int temp3, int temp4, int temp5, int temp6);

    ~base_creature(){};
    void insertGene(gene temp);
    void insertGene(int temp1, int temp2);
    UI num;
    private:
    vector<gene> GENE;
    vector<gene>::iterator iter;
    coordinate position;
    float damage;
    float hp;
    float speed;
    float rep;//reproductive index
};

base_creature::base_creature(int temp1, int temp2, UI tX, UI tY, int temp3, int temp4, int temp5, int temp6)
{
    gene *p = new gene;
    p->Name = Gene_name(temp1);
    p->flag = temp2;
    GENE.push_back(*p);

    position.X=tX;
    position.Y=tY;

    num=idx++;

    damage = temp3;
    hp = temp4;
    speed = temp5;
    rep= temp6;
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
    map<string, UI> key_values_mp;
    map<string, UI>::iterator map_iter;
    base_creature ***location;

    static string GetFilePath();
    void OutPut(string text);            //Only to file
    void OutPut(string text, bool flag); //Both file and screen
    void initialize();
    int rangeRand(int min, int max);
    void newCrt(UI tX, UI tY, UI num);
    void insertCreature(base_creature* temp);
    long long readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end);
    void GenInterOrder(UI SortNum);
    void evolve();
    SYS(string filePath);
    ~SYS();

private:
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator arr_iter;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator seed_iter;
    vector<base_creature*>::iterator crt_iter;
    vector<base_creature*> creature;
    vector<base_creature*> InterOrder;

    fstream fout;

    void GenSeed();
    void GenSeed(unsigned int temp);
    void seedResolution();
    void InitCrt();
};
//implement----------------------------------------------------------------------------------------

//Class SYS Private
string SYS::GetFilePath()
{
    string temp = LOG_PATH;
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));
    string sys_time = tmp;
    temp += "\\";
    temp += LOG_FILENAME;
    temp += sys_time.substr(0, 14);
    temp += ".log";
    cout << "Log file saved as " << temp << endl;
    return temp;
};

void SYS::OutPut(string text)
{
    fout << __TIMESTAMP__ << ": " << text << endl;
}

void SYS::OutPut(string text, bool flag)
{
    fout << __TIMESTAMP__ << ": " << text << endl;
    cout << text << endl;
}

long long SYS::readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end)
{
    long long temp = 0;
    for (int n = start - 1; n < end; n++)
    {
        temp += arr[n] * pow(10, (end - n - 1));
    }
    return temp;
}

void SYS::GenSeed()
{
    OutPut("Function SYS::GenSeed started.", true);

    unsigned time_stamp = time(NULL);
    string tempOutPut = "";
    OutPut("Using time stamp:" + to_string(time_stamp) + " to generate seed.", true);
    srand(time_stamp);
    for (int temp = 0; temp < SeedLen; temp++)
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = rand() % 10;
        }
        seed.push_back(arr);
    }
    OutPut("array values: ", true);
    for (seed_iter = seed.begin(); seed_iter != seed.end(); ++seed_iter)
    {
        for (arr_iter = seed_iter->begin(); arr_iter != seed_iter->end(); ++arr_iter)
        {
            tempOutPut += to_string(*arr_iter);
            tempOutPut += " ";
        }
        OutPut(tempOutPut, true);
        tempOutPut = "";
    }

    OutPut("Function SYS::GenSeed terminated.", true);
}

void SYS::GenSeed(unsigned int temp)
{
    OutPut("Function SYS::GenSeed started.", true);

    string tempOutPut = "";
    OutPut("Using number:" + to_string(temp) + " to generate seed.", true);
    srand(temp);
    for (int temp = 0; temp < SeedLen; temp++)
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = rand() % 10;
        }
        seed.push_back(arr);
    }
    OutPut("array values: ", true);
    for (seed_iter = seed.begin(); seed_iter != seed.end(); ++seed_iter)
    {
        for (arr_iter = seed_iter->begin(); arr_iter != seed_iter->end(); ++arr_iter)
        {
            tempOutPut += to_string(*arr_iter);
            tempOutPut += " ";
        }
        OutPut(tempOutPut, true);
        tempOutPut = "";
    }

    OutPut("Function SYS::GenSeed terminated.", true);
}

void SYS::seedResolution()
{
    OutPut("Function SYS::seedResolution started.", true);

    seed_iter = seed.begin(); //read First Row
    key_values_mp.insert(make_pair("InterOrder", readSeed(*seed_iter, 1, 1)));
    key_values_mp.insert(make_pair("IndivisualOrder", readSeed(*seed_iter, 2, 2)));
    key_values_mp.insert(make_pair("InitCrtAmount", readSeed(*seed_iter, 3, 4)));//test,3,4

    seed_iter++;                                               //read Second Row
    key_values_mp.insert(make_pair("Max_x", readSeed(*seed_iter, 1, 4))); //test

    key_values_mp.insert(make_pair("Max_y", readSeed(*seed_iter, 9, 12))); //test

    for (map_iter = key_values_mp.begin(); map_iter != key_values_mp.end(); map_iter++)
    {
        OutPut(map_iter->first + "->" + to_string(map_iter->second), true);
    }

    if(key_values_mp.find("Max_x")->second*key_values_mp.find("Max_y")->second<key_values_mp.find("InitCrtAmount")->second)
    {
        OutPut("Environment space not sufficient. Can't allocate Crt. Exiting",true);
        exit(-1);
    }

    OutPut("Function SYS::seedResolution terminated.", true);
}

void SYS::newCrt(UI tX, UI tY, UI num)
{
    int start=(num%4)*4+1;
    seed_iter=seed.begin();
    seed_iter++;//row2
    seed_iter++;//row3
    for(int temp=0;temp<num/4;temp++)//down to the row
    {
        seed_iter++;
    }
    
    base_creature *p;
    p = new base_creature(rangeRand(0, 2), rangeRand(0, 1),tX,tY, 
    readSeed(*seed_iter,start,start),
    readSeed(*seed_iter,start+1,start+1),
    readSeed(*seed_iter,start+2,start+2),
    readSeed(*seed_iter,start+3,start+3)
    );
    location[tX][tY]=p;
    insertCreature(p);
    OutPut("SYS::newCrt:created new creature, index="+ to_string(p->num));
}

void SYS::InitCrt()
{
    
    UI Max_x=key_values_mp.find("Max_x")->second,Max_y=key_values_mp.find("Max_y")->second;
    UI tX,tY;
    for (UI temp = 0; temp < key_values_mp.find("InitCrtAmount")->second; temp++)
    {
        do
        {
            tX=(UI)rangeRand(0,Max_x);
            tY=(UI)rangeRand(0,Max_y);
        }while(location[tX][tY]!=nullptr);
        newCrt(tX,tY,temp);
    }
}

void SYS::GenInterOrder(UI SortNum)
{
    clock_t timeStart = clock();
    OutPut("InterOrder:");
    if(SortNum%2)
    {
        int tempINT;
        base_creature *tempBC;
        InterOrder=creature;
        for(int loop=0;loop<InterOrder.size();loop++)
        {
            tempBC=InterOrder[loop];
            tempINT=rangeRand(0,InterOrder.size()-1);
            InterOrder[loop]=InterOrder[tempINT];
            InterOrder[tempINT]=tempBC;
            OutPut("swaping "+to_string(loop)+" with "+to_string(tempINT));
        }

        for(int loop=0;loop<InterOrder.size();loop++)
        {
            fout<<InterOrder[loop]->num<<" ";
        }
        fout<<endl;
    }
    else 
    {
        InterOrder=creature;
        for(int loop=0;loop<InterOrder.size();loop++)
        {
            fout<<InterOrder[loop]->num<<" ";
        }
        fout<<endl;
    }
    OutPut("Function SYS::GenInterOrder terminated. Used milli-seconds :" + to_string(clock() - timeStart), true);
}

//Class SYS Public
void SYS::initialize()
{

    string tempInput;
    OutPut("Function SYS::initialize started.", true);
    cout << "Enter 10-digit seed. Enter'/' for Auto Generate:";
    OutPut("Enter 10-digit seed. Enter'/' for Auto Generate:");
    cin >> tempInput;
    OutPut(tempInput);
    clock_t timeStart = clock();
    if (tempInput == "/")
    {
        GenSeed();
    }
    else
    {
        GenSeed(atoi(tempInput.c_str()));
    }
    // else //Input by keyboard
    // {
    //     for (int i = 0; i < ARRLEN; i++)
    //     {
    //         arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
    //     }
    //     seed.push_back(arr);
    //     for (int j = 1; j < SeedLen; j++)
    //     {
    //         cin >> tempInput;
    //         for (int i = 0; i < ARRLEN; i++)
    //         {
    //             arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
    //         }
    //         seed.push_back(arr);
    //     }
    //     for (seed_iter = seed.begin(); seed_iter != seed.end(); ++seed_iter)
    //     {
    //         for (arr_iter = seed_iter->begin(); arr_iter != seed_iter->end(); ++arr_iter)
    //         {
    //             OutPut(to_string(*arr_iter) + " ", true);
    //         }
    //         cout << endl;
    //     }
    // }
    seedResolution();

    UI tempMax_x=key_values_mp.find("Max_x")->second,tempMax_y=key_values_mp.find("Max_y")->second;
    location=new base_creature**[tempMax_x];
    for(UI temp_x=0;temp_x<tempMax_x;temp_x++)
    {
        location[temp_x]=new base_creature*[tempMax_y];
        for(UI temp_y=0;temp_y<tempMax_y;temp_y++)
        {
            location[temp_x][temp_y]=nullptr;
        }
    }

    InitCrt();

    GenInterOrder(key_values_mp.find("InterOrder")->second);

    OutPut("Function SYS::initialize terminated. Used milli-seconds :" + to_string(clock() - timeStart), true);
    
}

int SYS::rangeRand(int min, int max)
{
    return rand() % (abs(max - min) + 1) + (abs(min) < abs(max) ? min : max);
}

void SYS::insertCreature(base_creature* temp)
{
    creature.push_back(temp);
}

SYS::SYS(string filePath) : fout(filePath, ios::app)
{
    for (int i = 0; i < ARRLEN; i++)
    {
        arr[i] = 0;
    }
    OutPut("Class SYS constructed.", true);
}

SYS::~SYS()
{
    if (fout.is_open())
    {
        OutPut("fout closed.", true);
        fout.close();
    }
    cout << "class SYS destructed.";
}

int main()
{
    SYS sysctrl(SYS::GetFilePath());
    sysctrl.initialize();

    
    

    return 0;
}

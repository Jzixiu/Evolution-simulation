#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <array>
#include <math.h>
#include <map>
#include <ctime>
#include <fstream>
#define SeedLen 32
#define ARRLEN 16
#define LOG_PATH "C:\\Users\\hp\\Desktop\\Code\\LOG"
#define LOG_FILENAME "Log"
using namespace std;
typedef unsigned long long ULL;
//define


struct coordinate
{
    ULL X;
    ULL Y;
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
    base_creature(int temp1, int temp2, ULL tX, ULL ty);
    ~base_creature(){};
    void insertGene(gene temp);
    void insertGene(int temp1, int temp2);
    //private:
    vector<gene> GENE;
    vector<gene>::iterator iter;
    coordinate position;
    float damage;
    float hp;
    float speed;
};

base_creature::base_creature(int temp1, int temp2, ULL tX, ULL tY)
{
    gene *p = new gene;
    p->Name = Gene_name(temp1);
    p->flag = temp2;
    GENE.push_back(*p);

    position.X=tX;
    position.Y=tY;

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
    map<string, ULL> key_values_mp;
    map<string, ULL>::iterator map_iter;
    base_creature ***location;

    static string GetFilePath();
    void OutPut(string text);            //Only to file
    void OutPut(string text, bool flag); //Both file and screen
    void initialize();
    int rangeRand(int min, int max);
    void insertCreature(base_creature* temp);
    SYS(string filePath);
    ~SYS();

private:
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator arr_iter;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator vector_iter;
    vector<base_creature*> creature;

    fstream fout;
    

    long long readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end);
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
    for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
    {
        for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
        {
            tempOutPut += to_string(*arr_iter);
            tempOutPut += " ";
        }
        OutPut(tempOutPut, true);
        tempOutPut = "";
    }

    OutPut("Function SYS::GenSeed finished.", true);
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
    for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
    {
        for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
        {
            tempOutPut += to_string(*arr_iter);
            tempOutPut += " ";
        }
        OutPut(tempOutPut, true);
        tempOutPut = "";
    }

    OutPut("Function SYS::GenSeed finished.", true);
}

void SYS::seedResolution()
{
    OutPut("Function SYS::seedResolution started.", true);

    vector_iter = seed.begin(); //read First Row
    key_values_mp.insert(make_pair("HuDongShunXu", readSeed(*vector_iter, 1, 1)));
    key_values_mp.insert(make_pair("GeTi", readSeed(*vector_iter, 2, 2)));
    key_values_mp.insert(make_pair("InitCrtAmount", readSeed(*vector_iter, 3, 3)));//test,3,4

    vector_iter++;                                               //read Second Row
    key_values_mp.insert(make_pair("Max_x", readSeed(*vector_iter, 1, 2))); //test

    vector_iter++;                                               //read Third Row
    key_values_mp.insert(make_pair("Max_y", readSeed(*vector_iter, 1, 2))); //test

    for (map_iter = key_values_mp.begin(); map_iter != key_values_mp.end(); map_iter++)
    {
        OutPut(map_iter->first + "->" + to_string(map_iter->second), true);
    }

    OutPut("Function SYS::seedResolution finished.", true);
}

void SYS::InitCrt()
{
    base_creature *p;
    ULL Max_x=key_values_mp.find("Max_x")->second,Max_y=key_values_mp.find("Max_y")->second;
    ULL tX,tY;
    for (int temp = 0; temp < key_values_mp.find("InitCrtAmount")->second; temp++)
    {
        tX=rangeRand(0,Max_x);
        tY=rangeRand(0,Max_y);
        p = new base_creature(rangeRand(0, 2), rangeRand(0, 1),tX,tY);
        location[tX][tY]=p;
        insertCreature(p);
    }
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
    //     for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
    //     {
    //         for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
    //         {
    //             OutPut(to_string(*arr_iter) + " ", true);
    //         }
    //         cout << endl;
    //     }
    // }
    seedResolution();

    ULL tempMax_x=key_values_mp.find("Max_x")->second,tempMax_y=key_values_mp.find("Max_y")->second;
    location=new base_creature**[tempMax_x];
    for(ULL temp_x=0;temp_x<tempMax_x;temp_x++)
    {
        location[temp_x]=new base_creature*[tempMax_y];
        for(ULL temp_y=0;temp_y<tempMax_y;temp_y++)
        {
            location[temp_x][temp_y]=nullptr;
        }
    }

    InitCrt();

    OutPut("Function SYS::initialize finished. Used milli-seconds :" + to_string(clock() - timeStart), true);
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
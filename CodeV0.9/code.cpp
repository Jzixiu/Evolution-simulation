#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <map>
#include <math.h>
#define LOG_PATH "C:\\Users\\hp\\Desktop\\Code\\CodeV0.9\\Log" //Customization
#define GeneMaxAmount 99
using namespace std;
typedef unsigned short base_pair;
typedef unsigned int UI;

UI GIndex=1;//Global:creature index

clock_t Runtime;

struct BaseEffect
{
    short Damage;
    short Health;
    short Restore;
    short Speed;
    short Reproductive;
    short Perception;
};

BaseEffect Effect[4][4][4];

class Creature
{
    public:
    Creature(UI X, UI Y);
    ~Creature(){};
    UI Index;
    vector<base_pair> DNA;
    vector<base_pair>::iterator DNAiter;
    UI Damage;
    UI Health;
    UI Restore;
    UI Speed;
    UI Reproductive;
    UI Perception;
    UI X;
    UI Y;
    UI GeneNum;
    private:
    void SolveGene();
};

class SYS
{
    public:
    SYS(UI TimeStamp, string FilePath);
    ~SYS(){Output("System terminated. Time elapsed:"+to_string(clock() - Runtime));fout.close();};
    static string GetFilePath();//Get log file path
    void Log(string text);//Output to Logfile
    void Output(string text);//Output to both screen and Logfile
    void Initialize();
    static int Rand();
    static int RangeRand(int min, int max);
    void Run();
    UI Cycle;
    bool CheckTerminate();

    private:
    UI TimeStamp;
    fstream fout;
    void SeedResolution();
    map<string, UI> KeyValues;
    map<string, UI>::iterator MapIter;
    Creature ***Locate;
    void InitCrt();
    void NewCrt(UI X, UI Y);
    vector<Creature*> Crt;
    void InsertCrt(Creature* temp);
    void InitEffect();
};

string SYS::GetFilePath()
{
    string temp = LOG_PATH;
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));
    string sys_time = tmp;
    temp += "\\";
    temp += "Log";
    temp += sys_time.substr(0, 14);
    temp += ".log";
    cout << "Log file saved as " << temp << endl;
    return temp;
};

SYS::SYS(UI TimeStamp, string filePath) : fout(filePath, ios::app),TimeStamp(TimeStamp)
{
    Output("Class SYS constructed.Timestamp:"+to_string(TimeStamp));
}

void SYS::Log(string text)
{
    fout << __TIMESTAMP__ << ": " << text << endl;
}

void SYS::Output(string text)
{
    Log(text);
    cout << text << endl;
}

void SYS::Initialize()
{
    Output("Function SYS::initialize started.");
    Output("Enter 10-digit seed. Enter'/' for Auto Generate:");
    string tempInput;//Keyboard input
    cin >> tempInput;
    Runtime=clock();
    clock_t timeStart = clock();//Start clock
    Log(tempInput);
    if (tempInput == "/")//Without given value
    {
        srand(TimeStamp);
    }
    else
    {
        srand(atoi(tempInput.c_str()));//Use user input to initialize.
    }
    SeedResolution();

    UI tempMax_x=KeyValues.find("Max_x")->second+1,tempMax_y=KeyValues.find("Max_y")->second+1;
    Locate=new Creature**[tempMax_x];
    for(UI temp_x=0;temp_x<tempMax_x;temp_x++)
    {
        Locate[temp_x]=new Creature *[tempMax_y];
        for(UI temp_y=0;temp_y<tempMax_y;temp_y++)
        {
            Locate[temp_x][temp_y]=nullptr;
        }
    }

    InitEffect();

    InitCrt();

    // GenInterOrder(KeyValues.find("InterOrder")->second);

    Output("Function SYS::initialize terminated. Used milli-seconds :" + to_string(clock() - timeStart));
    
}

void SYS::SeedResolution()
{
    Output("Function SYS::seedResolution started.");

    KeyValues.insert(make_pair("InterOrder", RangeRand(0,pow(10,1)-1)));
    KeyValues.insert(make_pair("IndivisualOrder", RangeRand(0,pow(10,1)-1)));
    KeyValues.insert(make_pair("InitCrtAmount", RangeRand(0,pow(10,2)-1)));//Test
    KeyValues.insert(make_pair("Max_x", RangeRand(0,pow(10,4)-1)));//Test
    KeyValues.insert(make_pair("Max_y", RangeRand(0,pow(10,4)-1)));//Test

    for (MapIter = KeyValues.begin(); MapIter != KeyValues.end(); MapIter++)
    {
        Output(MapIter->first + "->" + to_string(MapIter->second));
    }

    if((KeyValues.find("Max_x")->second-1)*(KeyValues.find("Max_y")->second-1)<KeyValues.find("InitCrtAmount")->second)
    {
        Output("Environment space not sufficient. Can't allocate Crt. Exiting");
        exit(-1);
    }

    Output("Function SYS::seedResolution terminated.");
}

int SYS::Rand()
{
    return rand()*((rand()%2==0)?1:(-1));
}

int SYS::RangeRand(int min, int max)//Return a random number within given interval
{
    int k=Rand();
    return (k>max)?((k-min)%(max-min+1)+min):((k-max)%(max-min+1)+max);
}

void SYS::InitCrt()
{
    UI Max_x=KeyValues.find("Max_x")->second,Max_y=KeyValues.find("Max_y")->second;
    UI tX,tY;
    for (UI temp = 0; temp < KeyValues.find("InitCrtAmount")->second; temp++)
    {
        do
        {
            tX=(UI)RangeRand(1,Max_x);
            tY=(UI)RangeRand(1,Max_y);
        }while(Locate[tX][tY]!=nullptr);
        NewCrt(tX,tY);
    }
};

void SYS::NewCrt(UI tX, UI tY)
{   
    Creature *p;
    p = new Creature(tX,tY);
    Locate[tX][tY]=p;
    InsertCrt(p);
    Log("Successfully created "+ to_string(p->Index)+"th creature with "+to_string(p->GeneNum)+" DNA at "+to_string(p->X)+","+to_string(p->Y)+"\n");
}

void SYS::InsertCrt(Creature* temp)
{
    Crt.push_back(temp);
}

void SYS::InitEffect()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                Effect[i][j][k].Damage=RangeRand(-1,2);
                Effect[i][j][k].Health=RangeRand(-1,2);
                Effect[i][j][k].Reproductive=RangeRand(-1,2);
                Effect[i][j][k].Restore=RangeRand(-1,1);
                Effect[i][j][k].Speed=RangeRand(-1,2);
                Effect[i][j][k].Perception=RangeRand(-1,3);
            }
        }
    }
};

Creature::Creature(UI X, UI Y):X(X),Y(Y),GeneNum(SYS::RangeRand(1,GeneMaxAmount)),Index(GIndex++),Damage(0),Health(0),Restore(0),Speed(0),Reproductive(0),Perception(0)
{
    for(int temp=0;temp<GeneNum;temp++)
    {
        DNA.push_back(SYS::RangeRand(0,3));//A,T,G,C
    }
    SolveGene();
};

void Creature::SolveGene()
{
    if(GeneNum>=3)
    {
        base_pair i=0,j=0,k=0;
        int tDamage=0,tHealth=0,tReproductive=0,tRestore=0,tSpeed=0,tPerception=0;
        for(DNAiter=DNA.begin();DNAiter+3<=DNA.end();DNAiter+=3)
            {
                i=*DNAiter;
                j=*(DNAiter+1);
                k=*(DNAiter+2);
                tDamage+=Effect[i][j][k].Damage;
                tHealth+=Effect[i][j][k].Health;
                tReproductive+=Effect[i][j][k].Reproductive;
                tRestore+=Effect[i][j][k].Restore;
                tSpeed+=Effect[i][j][k].Speed;
                tPerception+=Effect[i][j][k].Perception;
                
            }
        Damage=((tDamage>0)?tDamage:0);
        Health=((tHealth>0)?tHealth:1);
        Reproductive=((tReproductive>0)?tReproductive:0);
        Restore=((tRestore>0)?tRestore:0);
        Speed=((tSpeed>0)?tSpeed:0);
        Perception=((tPerception>0)?tPerception:1);
    }
};

void SYS::Run()
{
    // while()
};

bool SYS::CheckTerminate()
{
    return Crt.size();
};

int main()
{
    SYS sysctrl(time(NULL),SYS::GetFilePath());
    sysctrl.Initialize();
    return 0;
}
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
#define LOG_FILENAME "log"
using namespace std;

//define

struct range
{
    int rangeLeft;
    int rangeRight;
};

struct coordinate
{
    unsigned long long X;
    unsigned long long Y;
};

class SYS
{
private:
    array<int, ARRLEN> arr;
    array<int, ARRLEN>::iterator arr_iter;
    vector<array<int, ARRLEN>> seed;
    vector<array<int, ARRLEN>>::iterator vector_iter;
    map<string, unsigned long long> key_values_mp;
    map<string, unsigned long long>::iterator map_iter;
    unsigned long long **pTerr;
    fstream fout;

    long long readSeed(array<int, ARRLEN> arr, unsigned start, unsigned end);
    void AutoGenSeed();
    void seedResolution();
    void TerrGen(unsigned long long Xmax, unsigned long long Ymax);
    void CalcH_LB(coordinate cordi);
    void CalcH_L(coordinate cordi);
    void CalcH_B(coordinate cordi);

public:
    static string GetFilePath();
    void OutPut(string text);//Only to file
    void OutPut(string text, bool flag);//Both file and screen
    void initialize();
    range overlap(int a, int b, unsigned short n);
    int rangeRand(range tRg);

    SYS(string filePath);
    ~SYS();
};
//implement----------------------------------------------------------------------------------------

//Class SYS Private
string SYS::GetFilePath()
{
    string temp=LOG_PATH;
    time_t t = time(0); 
    char tmp[64]; 
    strftime( tmp, sizeof(tmp), "%Y%m%d%H%M%S",localtime(&t) );
    string sys_time = tmp;
    temp += "\\";
    temp += LOG_FILENAME;
    temp += sys_time.substr(0,14);
    temp += ".log";
    cout<<"Log file saved as "<<temp<<endl;
    return temp;
};

void SYS::OutPut(string text)
{
    fout<<__TIMESTAMP__<<": "<<text<<endl;
}

void SYS::OutPut(string text,bool flag)
{
    fout<<__TIMESTAMP__<<": "<<text<<endl;
    cout<<text<<endl;
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

void SYS::AutoGenSeed()
{
    OutPut("Function SYS::AutoGenSeed started.",true);

    unsigned time_stamp = time(NULL);
    string tempOutPut="";
    OutPut("Using time stamp:"+to_string(time_stamp)+" to generate seed.",true);
    srand(time_stamp);
    for (int temp = 0; temp < SeedLen; temp++)
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = rand() % 10; //todo
        }
        seed.push_back(arr);
    }
    OutPut("array values: ",true);
    for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
    {
        for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
        {
            tempOutPut+=to_string(*arr_iter);
            tempOutPut+=" ";
        }
        OutPut(tempOutPut,true);
        tempOutPut="";
    }

    OutPut("Function SYS::AutoGenSeed finished.",true);
}

void SYS::seedResolution()
{
    OutPut("Function SYS::seedResolution started.",true);

    vector_iter = seed.begin(); //read First Row
    key_values_mp.insert(make_pair("HuDongShunXu", readSeed(*vector_iter, 1, 1)));
    key_values_mp.insert(make_pair("GeTi", readSeed(*vector_iter, 2, 2)));
    key_values_mp.insert(make_pair("InitCrtAmount", readSeed(*vector_iter, 3, 4)));

    vector_iter++;                                               //read Second Row
    key_values_mp.insert(make_pair("Max_x", readSeed(*vector_iter, 1, 3))); //test

    vector_iter++;                                               //read Third Row
    key_values_mp.insert(make_pair("Max_y", readSeed(*vector_iter, 1, 3))); //test

    for (map_iter = key_values_mp.begin(); map_iter != key_values_mp.end(); map_iter++)
    {
        OutPut(map_iter->first + "->" + to_string(map_iter->second),true);
    }

    OutPut("Function SYS::seedResolution finished.",true);
}

void SYS::TerrGen(unsigned long long Xmax, unsigned long long Ymax)
{
    OutPut("Function SYS::TerrGen started.",true);
    coordinate cordi;
    unsigned long long m, n;
    if (Ymax > Xmax)
    {
        OutPut("Ymax>Xmax",true);
        for (m = 2; m <= Xmax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 0; n < m - 2; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        OutPut("Phase 1 completed.",true);
        for (m = Xmax + 1; m <= Ymax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 1; n < Xmax; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
        OutPut("Phase 2 completed.",true);
        for (m = 2; m <= Xmax; m++)
        {
            cordi.X = m;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (n = 0; n < Xmax - m; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
        OutPut("Phase 3 completed.",true);
    }
    else
    {
        OutPut("Ymax<=Xmax",true);
        for (m = 2; m <= Ymax; m++)
        {
            cordi.X = 1;
            cordi.Y = m;
            CalcH_B(cordi);
            for (n = 0; n < m - 2; n++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        OutPut("Phase 1 completed.",true);
        for (n = 2; n <= Xmax - Ymax + 1; n++)
        {
            cordi.X = n;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (m = 0; m < Ymax - 2; m++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
            cordi.X++;
            cordi.Y--;
            CalcH_L(cordi);
        }
        OutPut("Phase 2 completed.",true);
        for (n = Xmax - Ymax + 2; n <= Xmax; n++)
        {
            cordi.X = n;
            cordi.Y = Ymax;
            CalcH_LB(cordi);
            for (m = 0; m < Xmax - n; m++)
            {
                cordi.X++;
                cordi.Y--;
                CalcH_LB(cordi);
            }
        }
        OutPut("Phase 3 completed.",true);
    }
    OutPut("Function SYS::TerrGen finished.",true);
}

void SYS::CalcH_LB(coordinate cordi)
{
    OutPut("LB("+to_string(cordi.X)+","+to_string(cordi.Y)+")");
}

void SYS::CalcH_L(coordinate cordi)
{
    OutPut("L("+to_string(cordi.X)+","+to_string(cordi.Y)+")");
}

void SYS::CalcH_B(coordinate cordi)
{
    OutPut("B("+to_string(cordi.X)+","+to_string(cordi.Y)+")");
}

//Class SYS Public
void SYS::initialize()
{
    OutPut("Function SYS::initialize started.",true);
    string tempInput;
    cout << "Enter the (1/32) Line of Seed. Enter'/' for Auto Generate:";
    OutPut("Enter the (1/32) Line of Seed. Enter'/' for Auto Generate:");
    cin >> tempInput;
    OutPut(tempInput);
    clock_t timeStart = clock();
    if (tempInput == "/")
    {
        AutoGenSeed();
    }
    else //Input by keyboard
    {
        for (int i = 0; i < ARRLEN; i++)
        {
            arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
        }
        seed.push_back(arr);
        for (int j = 1; j < SeedLen; j++)
        {
            cin >> tempInput;
            for (int i = 0; i < ARRLEN; i++)
            {
                arr[i] = atoi(tempInput.substr(i, 1).c_str()); //string to array.
            }
            seed.push_back(arr);
        }

        for (vector_iter = seed.begin(); vector_iter != seed.end(); ++vector_iter)
        {
            for (arr_iter = vector_iter->begin(); arr_iter != vector_iter->end(); ++arr_iter)
            {
                OutPut(to_string(*arr_iter)+" ",true);
            }
            cout << endl;
        }
    }
    seedResolution();
//
    clock_t timeStart2 = clock();
    OutPut("Initializing Dynamic Distribution of SYS::pTerr started.",true);
    unsigned long long tX=key_values_mp.find("Max_x")->second,tY=key_values_mp.find("Max_y")->second;
    pTerr=new unsigned long long *[tX];
    for(int temp=0;temp<(tX);temp++)
    {
        pTerr[temp]=new unsigned long long [tY];
    }
    OutPut("SYS::pTerr initialization completed. Used milli-seconds:"+ to_string(clock() - timeStart2),true);

    TerrGen(tX,tY);
    OutPut( "Function SYS::initialize finished. Used milli-seconds :" + to_string(clock() - timeStart),true);
}

range SYS::overlap(int a, int b, unsigned short n)
{
    range temp;
    if (a > b)
    {
        temp.rangeLeft = a - n;
        temp.rangeRight = b + n;
    }
    else
    {
        temp.rangeLeft = b - n;
        temp.rangeRight = a + n;
    }
    return temp;
}

int SYS::rangeRand(range tRg)
{
    return rand() % (abs(tRg.rangeRight - tRg.rangeLeft) + 1) + (abs(tRg.rangeLeft) < abs(tRg.rangeRight) ? tRg.rangeLeft : tRg.rangeRight);
}

SYS::SYS(string filePath):fout(filePath,ios::app)
{
    for (int i = 0; i < ARRLEN; i++)
    {
        arr[i] = 0;
    }
    OutPut("Class SYS constructed.",true);
}

SYS::~SYS()
{
    if (fout.is_open())
    {
     OutPut("fout closed.",true);
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

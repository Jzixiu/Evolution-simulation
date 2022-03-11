#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

class SYS
{
    private:
    string seed;
    public:
    string GenSeed();
    bool initialize();
    string getSeed();
    string dec2hex(int i);
};

string SYS::GenSeed()
{
    srand(time(NULL));
    string strTemp = dec2hex(rand());
    string seedTemp, Seed;
    do
    {
        strTemp = dec2hex(rand());
        seedTemp = seedTemp + strTemp;
    } while (seedTemp.length()<32);
    for(int temp=0; temp<32; temp++)
    {
        Seed=Seed+seedTemp[temp];
    }
    return Seed;
}

bool SYS::initialize()
{
    string temp;
    cout<<"������32λ����(����/���Զ�����):";
    cin>>temp;
    if(temp=="/")
    {
        cout<<"��ʼ�Զ���������"<<endl;
        temp=GenSeed();
        seed=temp;
        cout<<"�Զ����ɵ�����:"<<getSeed()<<endl;
        return true;//��������һ����ȷ
    }
    else
    {
        cout<<"���������:"<<temp<<endl;
        if(temp.length()==32)//���temp�Ƿ�Ϸ�
        {
            cout<<"���ӺϷ�"<<endl;
            seed=temp;
            return true;
        }
        else
        {
            cout<<"���Ӳ��Ϸ�"<<endl;
            return false;
        }
                
    }
    return false;
}

string SYS::getSeed()
{
    return seed;    
}

string SYS::dec2hex(int i) //��intת��16�����ַ���
{
    stringstream ioss;                                 //�����ַ�����
    string s_temp;                                     //���ת�����ַ�
    ioss << resetiosflags(ios::uppercase) << hex << i; //��ʮ����(Сд)��ʽ���
    ioss >> s_temp;
    return s_temp;
}

int main()
{
    SYS system;
    system.initialize();
    return 0;
}

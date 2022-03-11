#include <iostream>
using namespace std;
 
// 1 define BaseSkill
class BaseSkill {
    public:
    bool flag;
    virtual void active();
};

class heal:public BaseSkill {
    public:
        void active() {
            cout<<"heal active"<<endl;
        }
};

class jump:public BaseSkill {
    public:
        void active() {
            cout<<"jump active"<<endl;
        }
};

class BaseCreature {
    public:
        void active(BaseSkill bs);
};

class horse:public BaseCreature {
    public:
        void active(BaseSkill bs) {
            bs.active();
        }
};

int main() {
    horse hr;
    jump jp;  // horse can jump
    hr.active(jp);
    
    return 0;
} 
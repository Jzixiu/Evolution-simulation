#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// 1 open log, 0 close log
#define OPENDEBUG 1
// zyc_20210523
#define LOG_FILENAME "zyc";

/*
writelog: each day,generate a logfile
depend on macro OPENDEBUG
*/
void writelogByOS(string logtext) {
 // Only log when OPENDEBUG 1; no log when OPENDEBUG 0
 if (!OPENDEBUG) return;
  
    //获取系统时间YYMMDD
    time_t t = time(0); 
    char tmp[64]; 
    strftime( tmp, sizeof(tmp), "%Y%m%d%H%M%S",localtime(&t) ); 

    string sys_time = tmp;

    string log_filename = "C:\\tmp\\";//日志保存的位置 C:\tmp // /opt/jupiterLog/
    log_filename += LOG_FILENAME;
    log_filename += "_";
    log_filename += sys_time.substr(0,8);//YYYYmmdd
    log_filename += ".log";
    
    fstream fout(log_filename, ios::app);
 if(fout.bad())
 {
  cout << "error when openning file" << endl;
  return;
 }
 fout<<sys_time<<" "<<logtext<<endl;
 
 fout.close();
}


int main() {
 for (int i=0;i<10;i++) {
         writelogByOS("记录日志用fos "+ to_string(i));
 }
 return 0;
}
#include "/data4/YuSiang/personalLib/RPU/DBMTThread/DBMTThread.h"
using namespace std;

const int CPUNum = 5;
const int ProcessNum = 10;
const bool processShow   = false;

void function(int iProc){
  
  string FN = Form("/home/yusiang/test/testMutiThread/file%d.txt",iProc);
  ofstream out(FN.data());
  ULong_t integral = 0;
  for(Long64_t i=0; i<1.E+8*(1+iProc);i++)
    integral += i ;
  out<<integral<<endl;
  out.close();
  
}

void *process(void *arg){
  /*Don't change*/
  int iCore, iProc; SetProcStart(arg, iCore, iProc);
  
  /*Adjust this funtion*/
  function(iProc);
  
  /*Don't change*/
  SetProcFinish(arg, iCore, iProc);
}


void speedtest(){
  ContralThread();
}
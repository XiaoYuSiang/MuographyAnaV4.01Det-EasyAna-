#include <TThread.h>
#include <TSystem.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include "/data4/YuSiang/personalLib/RPU/DBMTThread/DBMTThread.h"

using namespace std;
/*external variable*/
extern const int CPUNum;
extern const int ProcessNum;
int  Process0, Process1;
extern const bool processShow;
/*inside variable*/
vector<bool> proOn;
vector<bool> proOf;
vector<int>  proIC;
vector<int>  IProC;
vector<ULong_t> absSec[2], absNanoSec[2];
vector<ULong_t> dSec, dNanoSec;
vector<TThread*> ths;
TThread *thtmp = new TThread();

/*external function*/
extern void *process(void *arg);

/*Delay setting : (milisec)*/
const int tfirstBashDelay  = 100;
const int tListBoolDelay   = 5;
const int tWaitDelThrDelay = 10;
const int tWaitAddThrDelay = 100;
const int tScanThrNumDelay = 20;
const int tListThrBolDelay = 10;

int NumThreadOffset = 0;

int Integral(vector<bool> vBool){
  int x = 0;
  for(int i=0;i<int(vBool.size());i++)
    x+=(vBool[i]==true?1:0);
  return x;
}

void ListThreads(){
  string strProcesses = "";
  gSystem->Sleep(tListThrBolDelay);
  strProcesses += Form("Info: list of process bool(On): ");
  for(int iCore=0;iCore<CPUNum;iCore++)
    strProcesses+=Form("%o",(bool)proOn[iCore]);
  strProcesses += Form(" bool(Of): ");
  for(int iCore=0;iCore<CPUNum;iCore++)
    strProcesses+=Form("%o",(bool)proOf[iCore]);
  strProcesses += Form(" On: %d",Integral(proOn));
  strProcesses += Form(" Of: %d",CPUNum-Integral(proOf));
  cerr<<"\r"<<strProcesses.data()<<flush;
  // cerr<<"\t"<<strProcesses.data()<<"\t"<<endl;
}

void ProcStatSetIniti(){
  if(proOn.size()!=0) proOn.clear();;
  if(proOf.size()!=0) proOf.clear();;
  for(int iCore=0;iCore<CPUNum;iCore++){
    proOn.push_back(false);
    proOf.push_back(true );
    proIC.push_back(-1);
    absSec[0]     .push_back(0);
    absSec[1]     .push_back(0);
    absNanoSec[0].push_back(0);
    absNanoSec[1].push_back(0);
    dSec           .push_back(0);
    dNanoSec      .push_back(0);
  }
  for(int iProc=0;iProc<ProcessNum;iProc++)
    IProC.push_back(-1);
  // cout<<endl<<"44-------------"<<endl;ListThreads(); cout<<endl<<"-------------"<<endl;
}


void SetProcStart(void *arg, int &iCore, int &iProc){
  iCore = atof((char*)arg);
  // cout<<77<<"\t"<<int (*((char *) arg) - '0')<<endl;
  iProc = proIC[iCore];
  // cout<<"Convert arg->iCore:iProc = "<<iCore<<"\t"<<iProc<<endl;
  thtmp->GetTime(&(absSec[0][iCore]), &absNanoSec[0][iCore]);
}
void SetProcFinish(void *arg, int &iCore, int &iProc){
  // cout<<endl<<"Err 0 - 109\tic="<<iProc<<"->"<<iCore<<"\n";
  proOn[iCore] = false;
  thtmp->GetTime(&absSec[1][iCore], &absNanoSec[1][iCore]);
  dNanoSec[iCore] = absNanoSec[1][iCore]-absNanoSec[0][iCore];
  dSec[iCore] = absSec[1][iCore]-absSec[0][iCore];
  if(dNanoSec[iCore]>1.E+9){ 
    dNanoSec[iCore] = absNanoSec[0][iCore]-absNanoSec[1][iCore]+1.E+9;
    dSec[iCore] = absSec[1][iCore]-absSec[0][iCore]-1;
  }
  stringstream iss;
  iss<<"\nFinish thread iProc->iCore = "<<iProc<<"->"<<iCore<<endl;
  if(processShow){
    iss<<"\n----------------------------------------"<<endl;
    iss<<"cost time: "<<dSec[iCore]<<"s+"<<dNanoSec[iCore]<<"ns"<<endl;
    iss<<"----------------------------------------"<<endl;
  }
  cout<<iss.str()<<endl;
  // cout<<endl<<"116: Finish op\tip="<<iProc<<"\tProOn"<<proOn[iCore]<<"\n";
  ListThreads();
}

void AddThread(const int iCore,const int iProc){
  IProC[iProc] = iCore;
  // ListThreads();
  // cout<<endl<<"Input Thread iCore arg: "<<Form("%d",iCore)<<endl;
  TThread *thtmpAdd 
    = new TThread(Form("pi%d",iCore),process,(void*) Form("%d",iCore));
  ListThreads();
  proOn[iCore] = true;
  proOf[iCore] = false;
  proIC[iCore] = iProc;
  cout<<"\nAdd thread iProc->iCore = "<<iProc<<"->"<<iCore<<endl;
  if(int(ths.size())<CPUNum) ths.push_back(thtmpAdd);
  else ths[iCore] = (thtmpAdd);
  ths[iCore]->Run();
}


void ContralThread(const int ProC0=0,const int ProC1=CPUNum,const char OPT = 'N'){
  bool Show=(OPT!='q'&&OPT!='Q');

  ProcStatSetIniti();
  cout <<"---------line before Mutithread----------"<<endl;
  NumThreadOffset = thtmp->Exists();
  if(Show){ ListThreads(); cout<<endl;}
  // cout<<endl<<142<<endl;
  Process0 = ProC0;
  Process1 = ProC1;
  int iProc = Process0;
  for(int iCore = 0;iCore<CPUNum;iProc++){
    if(iProc>=Process1) break;
    AddThread(iCore,iProc);
    iCore++;
  }
  if(Show){ ListThreads(); cout<<endl;}
  gSystem->Sleep(tfirstBashDelay);
  // throw;
  while(Integral(proOn)>0||iProc<ProcessNum){
    
    if(Integral(proOn)<CPUNum){
      // cout<<138<<endl;
      vector<int> emptyCore;
      for(int iCore=0;iCore<CPUNum;iCore++){
        if(proOn[iCore]==false&&proOf[iCore]==false){
          // cout<<"delete the thread : "<<iCore<<endl;
          proOf[iCore] = true; //set thread Ofline
          ths[iCore]->Delete();
          emptyCore.push_back(iCore);
        }
      }
      if(iProc<ProcessNum){
        for(int iECore=0;iECore<int(emptyCore.size())&&iProc<ProcessNum;iECore++){
          if(iProc<Process0) continue;
          if(iProc>=Process1) break;
          gSystem->Sleep(tWaitDelThrDelay);
          AddThread(emptyCore[iECore],iProc);
          iProc++;
        }
      }
    }
    if(Integral(proOn)==0) break;
    gSystem->Sleep(tScanThrNumDelay);//scan frequency
  }
  if(Show){ ListThreads(); cout<<endl;}

  for(int iCore=0;iCore<CPUNum;iCore++){
    if(proOn[iCore]==false&&proOf[iCore]==false){
      // cout<<"delete the thread : "<<iCore<<endl;
      proOf[iCore] = true; //set thread Ofline
      ths[iCore]->Delete();
    }
  }
  if(Show){ ListThreads(); cout<<endl;}
  // cout<<133<<endl;cout<<133<<endl;cout<<133<<endl;cout<<133<<endl;cout<<133<<endl;
  // throw;

  cout<<endl;
  cout<<"exist:\t"<<thtmp->Exists()-NumThreadOffset<<endl;
}
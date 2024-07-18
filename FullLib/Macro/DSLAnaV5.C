//include
#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <TStyle.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TChain.h>
// #include "./personalLib/RootFile/untuplizerv8_YuSiang01.h"
#include "path_dir.h"
#include "AnaVariable.h"

using namespace std;
using namespace MuoAna_path_dir;
using namespace MuographAnaVariable;

struct timeSt{
  Long64_t    unixtime;//abs time of event [s]
  Int_t    tY, tM, tD, th, tm, ts;
  timeSt(Long64_t ut ){
    unixTimeToHumanReadable(ut, tY, tM, tD, th, tm, ts, timeZone);
    unixtime = ut;
  };
};
vector<string> RawRootList(const char * DirOperate){
  vector<string> rootFilePathList;
  char TmpFileRoute[200];
  char rootFileList[200];
  sprintf(rootFileList, "%sDataRootNameAna.dat",DirOperate);
  // cout<<rootFileList<<endl;
  ifstream in(rootFileList);
  for(int i= 0; in>>TmpFileRoute ; i++){
    rootFilePathList.push_back(TmpFileRoute);
    // cout<<rootFilePathList[i]<<endl;
  }
  return rootFilePathList;
}
//channel vs rate combine
void DSLAnaV5(const bool MCMode = false, const bool GamaCutMode = false) {

  vector<string> vssssss = RawRootList(DirOperate.data());
  // for(int i=0;i<100;i++) cout<<vssssss[i]<<endl;
  // TreeReader data(vssssss);
  TChain *tData = new TChain("t");
  ofstream outh(Form("%sDSLData.h",DirMacros.data() ));
  //ofstream out(Form("%sDSLAna.txt",DirOperate));
  for(int i=0;i<int(vssssss.size());i++){
    cout<<"Add TChain: "<<vssssss[i]<<endl;
    tData->Add(vssssss[i].data());
  }
  Long64_t uttmp = 0; 
  tData->SetBranchAddress("unixtime",&uttmp);
  //take time and set anlyze Constant for boundry condition
  Long64_t evs = tData->GetEntries();//total event
  cout <<"total event:\t"<<evs<<endl;
  
  tData->GetEntry(0);
  timeSt timeiT(uttmp);
  Int_t unixtimei    = uttmp;
  Int_t Yeari        = timeiT.tY;
  Int_t Moni         = timeiT.tM;
  Int_t Dayi         = timeiT.tD;
  Int_t Houri        = timeiT.th;
  Int_t Mini         = timeiT.tm;
  Int_t Seci         = timeiT.ts;
  cout <<"unixtimei:\t"<<unixtimei<<endl;
  
  tData->GetEntry(evs-1);
  timeSt timefT(uttmp);
  Int_t unixtimef    = uttmp;
  Int_t Yearf        = timefT.tY;
  Int_t Monf         = timefT.tM;
  Int_t Dayf         = timefT.tD;
  Int_t Hourf        = timefT.th;
  Int_t Minf         = timefT.tm;
  Int_t Secf         = timefT.ts;
  cout <<"unixtimef:\t"<<unixtimef<<endl;
  
  char  TimeStr[50];
  char  TimeStrTitle[100];
  if(MCMode) 
    sprintf(TimeStr,"MCS%04d%02d%02dE%04d%02d%02d",
      Yeari,Moni,Dayi,Yearf,Monf,Dayf);
  else 
    sprintf(TimeStr,"S%04d%02d%02dE%04d%02d%02d",
      Yeari,Moni,Dayi,Yearf,Monf,Dayf);
      
  sprintf(TimeStrTitle,
    "Date From % 04d/%02d/%02d to %04d/%02d/%02d",
    Yeari,Moni,Dayi,Yearf,Monf,Dayf
  );
  /*     Example      sprintf(StatrStr,"SYYYYMMSSEYYYYMMSS")*/
  cout <<"dt:\t"<<unixtimef-unixtimei<<"\t"<<"dday:\t"<<Form("%.2f",(unixtimef-unixtimei)/86400.)<<endl;
  cout<<"TimeStr:    "<<TimeStr<<endl;
  // out<<"TimeStr:    "<<TimeStr<<endl;
  cout<<"TimeStrTitle:    "<<TimeStrTitle<<endl;
  // out<<"TimeStrTitle:    "<<TimeStrTitle<<endl;
  
  Int_t NumDFiles    = int(vssssss.size());
  Int_t FirDaySec    = unixtimei-Seci-Mini*60-Houri*3600;
  Int_t FinDaySec    = unixtimef-Secf-Minf*60-Hourf*3600+86400;
  Int_t yetSec       = 86400-Seci-Mini*60-Houri*3600;
  Int_t TotalTime    = (unixtimef-unixtimei);
  Int_t TotalDTime   = (FinDaySec-FirDaySec);
  Int_t BinOnTime    = int(TotalTime/th2fbinwidth);
  Int_t BinOnTimeD   = int(TotalDTime/th2fbinwidth);
  Int_t yetTimeBin   = int(yetSec/th2fbinwidth);

  Int_t dday = TotalTime/86400 + 1;
  Int_t ndivise = int(TotalDTime/86400);
  Int_t OOL=0;//OrderOfLabel
  
  for (;OOL<12;OOL++){
    if(ndivise<1+(32)*pow(2,OOL)){
      OOL=pow(2,OOL);
      cout<<"Trigger:\t"<<(32)*pow(2,OOL)<<"\tod:\t"<<OOL<<endl;
      break;
    }
  }
  cout<<"Trigger:\t"<<(32)*pow(2,OOL)<<"\tOrder Of Date Label:\t"<<OOL<<endl;
  
  const int totalRunNum = 1;
  int RunID[totalRunNum] = {0};
  //tPos->SetBranchAddress("GeneralID"   ,&GeneralID   );

  int      RID = 0;
  Long64_t StartUT = 1700000000, EndUT = 2147483647;
  Long64_t RUTs[totalRunNum] = {1700000000}, RUTf[totalRunNum] = {2147483647};

  
  int binUTBreak = ceil(TotalDTime/(1.*breaktime));
  int firstUTBin = ceil((unixtimei-FirDaySec)/(1.*breaktime));
  int finalUTBin = ceil((unixtimef-FirDaySec)/(1.*breaktime));
  TH1F *hUT = new TH1F("hUT",TimeStrTitle,binUTBreak,FirDaySec,FinDaySec);
  hUT->GetXaxis()->SetTitle("unixtime of frame");
  hUT->GetYaxis()->SetTitle("number of frame in break time range");



  TCanvas *c = new TCanvas("c","unixtime of data break or not",1920,1080);
  c->cd();
  tData->Draw("unixtime>>hUT","","hist");
  Int_t DutyTime = 0;
  for(int ibin=1;ibin<=binUTBreak;ibin++){
    int StaInBin = hUT->GetBinContent(ibin);
    if(StaInBin==0){
      if(firstUTBin<=ibin&&ibin<=finalUTBin)
        DutyTime += breaktime;
    }
  }
  // cout<<firstUTBin<<"  "<<finalUTBin<<endl;
  Int_t   WorkTime = TotalTime  - DutyTime;
  Float_t RateWei  = (WorkTime == 0 ? 0 : 1./WorkTime );
  
  cout<<"Worktime:\t"<<WorkTime<<"\tDutyT:\t"<<DutyTime<<"\tfrequency:\t"<<RateWei<<endl;
  //out<<"Worktime:\t"<<WorkTime<<"\tfrequency:\t"<<RateWei<<endl;
  Float_t EFFDRat = (WorkTime*1.)/(1.*TotalTime);

  
  cout<<"Saving the data Information at "<<DirMacros<<"DSLData.h"<<endl;
  
  c->Print(Form("%sDutyTime.png",DirOperate.data()));
  c->Print(Form("%sDutyTime.pdf",DirOperate.data()));
  c->Close();
  
  outh<<"#include <iostream>"<<endl;
  outh<<"#include <vector>"<<endl;
  outh<<"#include <fstream>"<<endl;
  outh<<"#include <typeinfo>"<<endl;
  outh<<"#include <algorithm>"<<endl;
  outh<<""<<endl;
  outh<<"namespace DataConst"<<endl;
  outh<<"{"<<endl;
  outh<<""<<endl;
  outh<<"  const bool    MCMode      = "<< MCMode     <<";\n";
  outh<<"  const bool    GammaCutMode= "<< GamaCutMode<<";\n";
  outh<<"  const int     timeZone = "   << timeZone<<";\n";
  outh<<""<<endl;
  outh<<"  /*Time string which can use on file name*/"<<endl;
  outh<<"  const char     TimeStr[25]     = \""<< TimeStr     <<"\";\n";
  outh<<"  const char     TimeStrTitle[50]= \""<< TimeStrTitle<<"\";\n";
  outh<<"  const Int_t    NumDFiles  = "<< NumDFiles <<";\n";
  outh<<endl<<"  /*Total Event Numbers Of Input Files*/"<<endl;
  outh<<"  const Long64_t evs        = "<< evs       <<";\n";
  outh<<endl<<"  /*time Information of the first event*/"<<endl;
  outh<<"  const Int_t    unixtimei  = "<< unixtimei <<";\n";
  outh<<"  const Int_t    Yeari      = "<< Yeari     <<";\n";
  outh<<"  const Int_t    Moni       = "<< Moni      <<";\n";
  outh<<"  const Int_t    Dayi       = "<< Dayi      <<";\n";
  outh<<"  const Int_t    Houri      = "<< Houri     <<";\n";
  outh<<"  const Int_t    Mini       = "<< Mini      <<";\n";
  outh<<"  const Int_t    Seci       = "<< Seci      <<";\n";
  outh<<"  const Int_t    FirDaySec  = "<< FirDaySec <<";\n";
  outh<<endl<<"  /*time Information of the last event*/"<<endl;
  outh<<"  const Int_t    unixtimef  = "<< unixtimef <<";\n";
  outh<<"  const Int_t    Yearf      = "<< Yearf     <<";\n";
  outh<<"  const Int_t    Monf       = "<< Monf      <<";\n";
  outh<<"  const Int_t    Dayf       = "<< Dayf      <<";\n";
  outh<<"  const Int_t    Hourf      = "<< Hourf     <<";\n";
  outh<<"  const Int_t    Minf       = "<< Minf      <<";\n";
  outh<<"  const Int_t    Secf       = "<< Secf      <<";\n";
  outh<<"  const Int_t    FinDaySec  = "<< FinDaySec <<";\n";
  outh<<endl<<"  /*Information of the time bin or chip operate*/"<<endl;
  outh<<"  const Int_t    ndivise    = "<< ndivise   <<";\n";
  outh<<"  const Int_t    OOL        = "<< OOL       <<";\n";
  outh<<"  const Int_t    TotalTime  = "<< TotalTime <<";\n";
  outh<<"  const Int_t    TotalDTime = "<< TotalDTime<<";\n";
  outh<<"  const Int_t    BinOnTime  = "<< BinOnTime <<";\n";
  outh<<"  const Int_t    BinOnTimeD = "<< BinOnTimeD<<";\n";
  outh<<"  const Int_t    yetSec     = "<< yetSec    <<";\n";
  outh<<"  const Int_t    WorkTime   = "<< WorkTime  <<";\n";
  outh<<"  const Float_t  RateWei    = "<< RateWei   <<";\n";
  outh<<"  const Float_t  EFFDRat    = "<< (WorkTime*1.)/(1.*TotalTime)<<";\n";
  outh<<"  const Float_t  EFFDays    = "<< ndivise*EFFDRat<<";\n";
  outh<<"  const Int_t    RunNums    = "<< totalRunNum<<";\n";
  outh<<"  "<<endl<<endl;
  outh<<"  const int RunID[RunNums]={\n";
  outh<<"    "<<RunID[0];
  for(int irun=1;irun<totalRunNum;irun++)
    outh<<",\n"<<"    "<<RunID[irun];
  outh<<"\n  };"<<endl<<endl;
  
  outh<<"  const int RunUts[RunNums]={\n";
  outh<<"    "<<RUTs[0];
  for(int irun=1;irun<totalRunNum;irun++)
    outh<<",\n"<<"    "<<RUTs[irun];
  outh<<"\n  };"<<endl<<endl;
  
  outh<<"  const int RunUtf[RunNums]={\n";
  outh<<"    "<<RUTf[0];
  for(int irun=1;irun<totalRunNum;irun++)
    outh<<",\n"<<"    "<<RUTf[irun];
  outh<<"\n  };"<<endl<<endl;

  
  outh<<"  void Mod_DateLabel(TH1F* TH1FObj,const char* TitleY=\"TitleY\"){"<<endl;
  outh<<"    Int_t    unixtime, tYear, tMonth, tDate ,tHour ,tMinute ,tSecond ;"<<endl;
  outh<<"    "<<endl;
  outh<<"    TH1FObj->SetStats(0);"<<endl;
  outh<<"    TH1FObj->GetXaxis()->SetTitle(\"Date\");"<<endl;
  outh<<"    TH1FObj->GetYaxis()->SetTitle(TitleY);"<<endl;
  outh<<"    TH1FObj->GetXaxis()->SetTitleOffset(1.5);"<<endl;
  outh<<"    TH1FObj->GetYaxis()->SetTitleOffset(1.2);"<<endl;
  outh<<"    TH1FObj->GetXaxis()->SetLabelSize(0.03);"<<endl;
  outh<<"    TH1FObj->GetYaxis()->SetLabelSize(0.03);"<<endl;
  outh<<"    TH1FObj->SetMarkerStyle(0);"<<endl;
  outh<<"    TH1FObj->SetLineColor(0);"<<endl;
  outh<<"    TH1FObj->SetMarkerColor(0);"<<endl;
  outh<<"    TH1FObj->GetXaxis()->SetRangeUser(FirDaySec,FinDaySec);"<<endl;
  outh<<"    TH1FObj->GetXaxis()->SetTickLength(0);"<<endl;
  outh<<"    "<<endl;
  outh<<"    for (int i1=0;i1<(ndivise);i1++){"<<endl;
  outh<<"      unixtime = TH1FObj->GetXaxis()->GetBinCenter(1+i1)-TH1FObj->GetXaxis()->GetBinWidth(1+i1)/2.;"<<endl;
  outh<<"      unixTimeToHumanReadable(unixtime, tYear, tMonth, tDate, tHour, tMinute, tSecond,timeZone);"<<endl;
  outh<<"      char str_MD[30] ={};"<<endl;
  outh<<"      sprintf(str_MD , \"%s-%02.f\",MonthName[tMonth],1.*tDate);"<<endl;
  outh<<"      if(tDate==1||tDate==15||i1==0||i1==ndivise||(ndivise+1)<32){"<<endl;
  outh<<"        TH1FObj->GetXaxis()->SetBinLabel(1+i1 ,str_MD);"<<endl;
  outh<<"      }"<<endl;
  outh<<"    }"<<endl;
  outh<<"  }"<<endl<<endl;
  
  
  outh<<"  TH1F *Mod_DateLabel(const char* TH1FName=\"Mod_TH1F_UTVYZ\",const char* TH1FTitle=\"\",const float YMin=0, const float YMax=1,const char* TH1FTitleY=\"TitleY\"){"<<endl;
  outh<<"    TH1F *Mod_TH1F_UTVYZ = new TH1F(TH1FName,TH1FTitle,ndivise,FirDaySec,FinDaySec);"<<endl;
  outh<<"    Mod_DateLabel(Mod_TH1F_UTVYZ,TH1FTitleY);"<<endl;
  outh<<"    Mod_TH1F_UTVYZ->GetYaxis()->SetRangeUser(YMin,YMax);"<<endl;
  outh<<"    return Mod_TH1F_UTVYZ;"<<endl;
  outh<<"  }"<<endl<<endl;
  
  
  outh<<"  void Mod_DateLabel(TH2F* TH2FObj,const char* TitleY=\"TitleY\",const char* TitleZ=\"TitleZ\"){"<<endl;
  outh<<"    Int_t    unixtime, tYear, tMonth, tDate ,tHour ,tMinute ,tSecond ;"<<endl;
  outh<<"    TH2FObj->SetStats(0);"<<endl;
  outh<<"    TH2FObj->GetXaxis()->SetTitle(\"Date\");"<<endl;
  outh<<"    TH2FObj->GetYaxis()->SetTitle(TitleY);"<<endl;
  outh<<"    TH2FObj->GetZaxis()->SetTitle(TitleZ);"<<endl;
  outh<<"    TH2FObj->GetXaxis()->SetTitleOffset(1.5);"<<endl;
  outh<<"    TH2FObj->GetYaxis()->SetTitleOffset(1.2);"<<endl;
  outh<<"    TH2FObj->GetZaxis()->SetTitleOffset(1.3);"<<endl;
  outh<<"    TH2FObj->GetXaxis()->SetLabelSize(0.03);"<<endl;
  outh<<"    TH2FObj->GetYaxis()->SetLabelSize(0.03);"<<endl;
  outh<<"    TH2FObj->GetZaxis()->SetLabelSize(0.025);"<<endl;
  outh<<"    TH2FObj->SetMarkerStyle(0);"<<endl;
  outh<<"    TH2FObj->SetLineColor(0);"<<endl;
  outh<<"    TH2FObj->SetMarkerColor(0);"<<endl;
  outh<<"    TH2FObj->GetXaxis()->SetRangeUser(FirDaySec,FinDaySec);"<<endl;
  outh<<"    TH2FObj->GetXaxis()->SetTickLength(0);"<<endl;
  outh<<"    "<<endl;
  outh<<"    for (int i1=0;i1<(ndivise);i1++){"<<endl;
  outh<<"      unixtime = TH2FObj->GetXaxis()->GetBinCenter(1+i1)-TH2FObj->GetXaxis()->GetBinWidth(1+i1)/2.;"<<endl;
  outh<<"      unixTimeToHumanReadable(unixtime, tYear, tMonth, tDate, tHour, tMinute, tSecond,timeZone);"<<endl;
  outh<<"      char str_MD[30] ={};"<<endl;
  outh<<"      sprintf(str_MD , \"%s-%02.f\",MonthName[tMonth],1.*tDate);"<<endl;
  outh<<"      if(tDate==1||tDate==15||i1==0||i1==ndivise||(ndivise+1)<32){"<<endl;
  outh<<"        TH2FObj->GetXaxis()->SetBinLabel(1+i1 ,str_MD);"<<endl;
  outh<<"      }"<<endl;
  outh<<"    }"<<endl;
  outh<<"  }"<<endl<<endl<<endl;

  
  outh<<"  TH2F *Mod_DateLabel(const char* TH2FName=\"Mod_TH2F_UTVYVZ\",const char* TH2FTitle=\"\",const int NYBin = 10,const float YMin=0, const float YMax=1,const char* TH2FTitleY=\"TitleY\",const char* TH2FTitleZ=\"TitleZ\"){"<<endl;
  outh<<"    TH2F *Mod_TH2F_UTVYVZ = new TH2F(TH2FName,TH2FTitle,ndivise,FirDaySec,FinDaySec,NYBin,YMin,YMax);"<<endl;
  outh<<"    Mod_DateLabel(Mod_TH2F_UTVYVZ,TH2FTitleY,TH2FTitleZ);"<<endl;
  outh<<"    Mod_TH2F_UTVYVZ->GetYaxis()->SetRangeUser(YMin,YMax);"<<endl;
  outh<<"    return Mod_TH2F_UTVYVZ;"<<endl;
  outh<<"  }"<<endl<<endl;
  

  outh<<"  TGraphErrors *Mod_DateGrid(const float YMin, const float YMax){"<<endl;
  outh<<"  "<<endl;
  outh<<"    TH1F *Mod_TH1F_UTVYZ      = new TH1F(\"Mod_TH1F_UTVYZ\",\"\",ndivise,FirDaySec,FinDaySec);"<<endl;
  outh<<"    float DGx[ndivise]={},DGy[ndivise]={},DGex[ndivise]={},DGey[ndivise]={};"<<endl;
  outh<<"    for(int i0=0;i0<ndivise;i0++) {"<<endl;
  outh<<"      DGx[i0] = Mod_TH1F_UTVYZ->GetBinCenter(i0+1)+Mod_TH1F_UTVYZ->GetBinWidth(i0+1)/2.;"<<endl;
  outh<<"      DGy[i0] = YMin;  DGey[i0] = fabs(YMax-YMin)*2;  DGex[i0] = 0;"<<endl;
  outh<<"      // cout<<DGx[i0]<<\"\t\"<<DGy[i0]<<\"\t\"<<DGex[i0]<<\"\t\"<<DGey[i0]<<endl;"<<endl;
  outh<<"    }"<<endl;
  outh<<"    TGraphErrors *TDayGrid = new TGraphErrors(ndivise,DGx,DGy,DGex,DGey);"<<endl;
  outh<<"    TDayGrid->SetLineStyle(3);"<<endl;
  outh<<"    TDayGrid->SetLineColor(1);"<<endl;
  outh<<"    TDayGrid->SetMarkerStyle(1);"<<endl;
  outh<<"    TDayGrid->SetMarkerColor(0);"<<endl;
  outh<<"    delete Mod_TH1F_UTVYZ;"<<endl;
  outh<<"    return TDayGrid;"<<endl;
  outh<<"  }"<<endl;
  outh<<"};"<<endl;
  
  outh.close();
  system(Form("cp %sDSLData.h %sDSLData.h",DirMacros.data(),DirOperate.data()));
  cout<<Form("Save the copy of %sDSLData.h to %sDSLData.h", DirMacros.data(),DirOperate.data())<<endl;;
}



//channel vs rate combine
void DSLAnaV2() {
  cout<<"Error: Please use the last version DSLAna: DSLAnaV4"<<endl;
  throw;
}


//channel vs rate combine
void DSLAnaV3() {
  cout<<"Error: Please use the last version DSLAna: DSLAnaV4"<<endl;
  throw;
}

//channel vs rate combine
void DSLAnaV4() {
  cout<<"Error: Please use the last version DSLAna: DSLAnaV5"<<endl;
  throw;
}



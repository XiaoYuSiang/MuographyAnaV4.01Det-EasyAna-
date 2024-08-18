#include <typeinfo>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TKey.h>
#include <TGaxis.h>
#include <TText.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TObjString.h>
#include <TGraphErrors.h>
#include "./personalLib/Style/DBMTStyle.h"
#include "./personalLib/RootFile/untuplizerv8_YuSiang01.h"
#include "AnaVariable.h"
#include "path_dir.h"
#include "DSLData.h"

using namespace std;
using namespace MuoAna_path_dir;
using namespace MuographAnaVariable;
using namespace DataConst;
vector<string>   vRootFiles;
vector<string>   vRotFileSepRun[MaxRun];
vector<Long64_t> vSizeSepRun;

const string FNOEvNumForGap = DirOperate+"EvNumForGap.dat";
const string FNOEvDisplay   = DirOperate+"EvDisplay.dat";
const string FNOEvProblem   = DirOperate+"EvProblem.dat";
const int  CPUNum = cpuCores;
const int  ProcessNum = NumDFiles;
const float THRIndexConvertRatio[46] = {};// 140 = 0.28
string ADayGapRootFiles[Num_EvGapIndex][MaxRun][NumDFiles];
int  IRunNow;
// const int  ProcessNum = 2;
// const int  ProcessNum = MaxRun;
const bool processShow   = false;
char RecreateOption = 'N';
int gapIndexNow;
int UTsfNow[2] = {0};
void LastVerShow(){
  string lastVer = "EventAnaV5.C";
  cout<<"Please use the last version: "<<lastVer<<endl;
}
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

int BDcheck(const int b){
  int z = -1;
  for(int i=0;i<NumBD;i++){
    if( b == BD[i] ){
      z = i;
      break;
    } 
  }if(z==-1){
    cout<<"Warning: GobelFun.h: Please Enter the true value b into the int BDcheck(int b)!!!   ";
    cout<<"Now the Enter value b is:  "<< b << ", Set val to be -1" <<endl;
    //throw;
  } 
  return z;
}
int BDCheck(const int b){ return BDcheck(b);}
int CHcheck(const int c){
  int z = -1;
  if(c>NumCh-1||c<0){
    cout<<"Warning: GobelFun.h: Please Enter the true value c into the int CHcheck(int c)!!!   ";
    cout<<"Now the Enter value c is:  "<< -1 <<endl;
    //throw;
  }else{
    z = c;
  }
  return z;
}
Long64_t FileSize(const char *CheckFileName, const char OPT ='-'){
  ifstream fin(CheckFileName, ifstream::in | ifstream::binary);
  fin.seekg(0, ios::end);
  Long64_t length = fin.tellg();
  fin.close();
  if(OPT!='Q'&&OPT!='q') cout << length << " Bytes." << endl;
  return length;
}


void EventAnaV6(
  const int index = 28, const char OPT = 'N'
){//140
   
  double eventGap = eventGapTcnt[index]*1.;
  char rtfN[200]; sprintf(rtfN,"%sGapT%d_%s_nHTH%dL%d.root",DirOperate.data(),int(eventGap),TimeStr,TriggerS,TriggerL);
  
  vector<string> vssssss = RawRootList(DirOperate.data());
  Long64_t sizeRaw = 0;
  for(int i=0;i<int(vssssss.size());i++){
    cout<<"Add TChain: "<<vssssss[i]<<endl;
    sizeRaw+=FileSize(vssssss[i].data());
  }
  
  
  Long64_t size = FileSize(rtfN);
  cout<<"Checking the option of file: "<<rtfN<<"\tis "<<size<<" Byte."<<endl;
  if(size > sizeRaw*0.28&&(OPT!='r'&&OPT!='R')){
    TFile *rottmp = new TFile(rtfN,"open");
    TObjString *FlagFinish;
    bool usefulFile = (FlagFinish =(TObjString*) rottmp->Get("FlagFinish"));
    if(usefulFile&&(size > sizeRaw*0.28)){
      cout<<"The "<<rtfN
        <<" is exist\nNot going to recreate the file, and skip this program\n";
      return;
    }
    delete FlagFinish;
    rottmp->Close();
  }

  cout<<Form("Root file not find, and save: %s",rtfN)<<endl;
  
  stringstream iss, iss1, issEvP;
  // cout<<"L116, Lock the threads to create TreeReader of Core: "<<iCore<<endl;
  
  
  TreeReader data(vssssss);
  Long64_t evs = data.GetEntriesFast();
  Long64_t ThisFileLastEvent = evs;
  cout<<"\nevs is :" << evs<<endl;
  //Data Variable
  Int_t Index =0;
  
  
  TFile *rotfile = new TFile(rtfN,"RECREATE");//@@ by DSL
  cout<<Form("Root Save: %s",rtfN)<<endl;
  Int_t      EvIndex=0;
  Int_t      frame_;
  Int_t      frameLast = 0;
  Long64_t   unixtime_;
  Int_t      tYear;
  Int_t      tMonth;
  Int_t      tDate;
  Int_t      tHour;
  Int_t      tMinute;
  Int_t      tSecond;

  //PS:2560000000 Hz
  Int_t      nLayers;
  Int_t      nHits ;//total number for hit in a frame/event
  Int_t      nH  ;//total number for hit in a frame/event
  Int_t      nHk[NumLY];
  Double_t*  dtime_;
  Long64_t*  dtimeInt_;
  Int_t*     channel_;
  Int_t*     board_;
  Int_t*     pwidth_;
  Int_t*     pcnt_;
  Long64_t*  tcnt_;
  vector<Double_t>  dtime;
  vector<Long64_t>  dtimeInt;
  vector<Int_t>     channel;
  vector<Int_t>     board;
  vector<Int_t>     pwidth;
  vector<Int_t>     pwidthScaleFactor;
  vector<Int_t>     pcnt;
  vector<Long64_t>  tcnt;
  vector<Double_t>  dtcnt;
  Double_t   dTimeOfEv ;
  
  // cout<<"L148, Lock the threads to create TTree and TH1Fs of Core: "<<iCore<<endl;
  TTree *tree = new TTree("t","data from analyzing file");
  tree->Branch("frame",&frameLast);
  tree->Branch("EvIndex",&EvIndex);
  tree->Branch("unixtime",&unixtime_);
  tree->Branch("tYear",&tYear);
  tree->Branch("tMonth",&tMonth);
  tree->Branch("tDate",&tDate);
  tree->Branch("tHour",&tHour);
  tree->Branch("tMinute",&tMinute);
  tree->Branch("tSecond",&tSecond);
  tree->Branch("nH",&nH);
  for(int i=0; i<NumLY; i++) tree->Branch(Form("nH%d",i),&(nHk[i]));
  
  tree->Branch("nLayers",&nLayers);
  tree->Branch("channel",&channel);
  tree->Branch("board",&board);
  tree->Branch("pwidth",&pwidth);
  tree->Branch("pwidthScaleFactor",&pwidthScaleFactor);
  tree->Branch("tcnt",&tcnt);
  tree->Branch("pcnt",&pcnt);
  tree->Branch("dtcnt",&dtcnt);
  tree->Branch("dtime",&dtime);
  tree->Branch("dtimeInt",&dtimeInt);
  tree->Branch("dTimeOfEv",&dTimeOfEv);
  

  
  TH1F *hBoard       = new TH1F("hBoard ","",NumBD,0,NumBD);
  TH1F *hChannel     = new TH1F("hChannel ","",NumCh,0,NumCh);
    // cout<<"L182, UnLock the threads to create TTree and TH1Fs of Core: "<<iCore<<endl;
  Index =0;
  double dtime0 = 0;
  dTimeOfEv = 0;
  int nHit = 0;
  cout<<"Start at: "<< 0<<endl;
  data.GetEntry(0);
  frameLast   = data.GetInt("frame");
  cout<< 275<<"  iC/iP/FN: " <<"  "<<rtfN<<endl;

  for (Long64_t ev = 0; ev < ThisFileLastEvent ; ++ev) {
    
    if(ev%1000==0)
      cout<<"\r"<<100*ev/float(ThisFileLastEvent)<<"%"<<flush;
    data.GetEntry(ev);
    frame_   = data.GetInt("frame");
    unixtime_= data.GetLong64("unixtime");//fabs time of event [s]

    // if(ev%1000 == 0) cout<<Form("\r%.5f%%\t%d\t%d\t%d",(ev*100.)/(1.*evs),unixtime_,frame_,nHits)<<flush;
    nHits    = data.GetInt("nHits");
    dtime_   = data.GetPtrDouble("dtime");
    dtimeInt_= data.GetPtrLong64("dtimeInt");
    board_   = data.GetPtrInt("board");
    channel_ = data.GetPtrInt("channel");
    pwidth_  = data.GetPtrInt("pwidth");
    pcnt_    = data.GetPtrInt("pcnt");
    tcnt_    = data.GetPtrLong64("tcnt");
    

    if (dtime0 == 0) dtime0 = dtimeInt_[0];

     

    for( int i=0 ; i<nHits; i++){
      if(GammaCutMode) if(pwidth_[i]==0) continue;
      // if(board_[i]>=17) continue;
      dtcnt.push_back(abs(dtimeInt_[i]-dtime0));
      if(((!MCMode)&&(nHit!=0&&dtcnt[nHit]>eventGap))||(MCMode&&frameLast!=frame_)){
        dtcnt.pop_back();
        tYear   = data.GetInt("tYear"  );
        tMonth  = data.GetInt("tMonth" );
        tDate   = data.GetInt("tDate"  );
        tHour   = data.GetInt("tHour"  );
        tMinute = data.GetInt("tMinute");
        tSecond = data.GetInt("tSecond");
        nH      = nHit;//total number for hit in a frame/event
        int NPartCut = NumBD/NumLY;
        int VnH[NumLY] = {0};
        // for(int iPartCut = 0 ; iPartCut < NPartCut ; iPartCut++){
          // for(int iLay = 0 ; iLay < NumLY ; iLay++){
            // VnH[iLay] +=hBoard->GetBinContent(BDCheck(BD[iLay*NPartCut+iPartCut])+1);//total number for hit in a frame/event
          // }
        // }//@@
        for(int iBD=0;iBD<NumBD; iBD++){
          VnH[BDLay[iBD]] += hBoard->GetBinContent(iBD+1);//total number for hit in a frame/event
        }
        int Tmp_nH = 0;
        for(int iLay = 0 ; iLay < NumLY ; iLay++){
          nHk[iLay] = VnH[iLay];
          Tmp_nH += nHk[iLay];  
        } 
        
        if(nH!=Tmp_nH){
          cout<<"Warning: nH!=Tmp_nH: "<<EvIndex<<"\t"<<nH;
          for(int iLay = 0 ; iLay < NumLY ; iLay++) cout<<"\t"<<nHk[iLay];
          cout<<endl;
        }
        
        
        nLayers=0 ;//total number for hit in a frame/event
        for(int i1=0; i1<NumLY;i1++) if (VnH[i1]!=0) nLayers++;
        
        if( ((!MCMode)&&(TriggerS < nHit&&nHit < TriggerL)) || (MCMode) ){
          if(/*unixtime_>1600000000*/true){
            dTimeOfEv = abs(dtimeInt_[i]-dtime0);
            tree->Fill();
            for(int i7=0;i7<nH;i7++){
              char gid[20];
              sprintf(gid,"%010.f%d%02.f",tcnt[i7]*1.,board[i7],channel[i7]*1.);
              // iss1<<Index<<"\t"<<gid<<"\t"<<tcnt[i7]<<"\t"<<board[i7]<<"\t"<<channel[i7]<<"\t"<<pwidth[i7]<<endl;
            }
            Index++;
            EvIndex = Index;
          // cout<<"\tIndex\t"<<Index<<"\tnH\tbool \t "<<nHit<<"\t"<<( TriggerS < nHit&&nHit < TriggerL)<<endl;
          }
        }
        //cout<<"dTimeOfEv\t"<<dTimeOfEv<<"\tnHit:\t"<<nHit<<endl;
        board.clear();
        channel.clear();
        pwidth.clear();
        pwidthScaleFactor.clear();
        tcnt.clear();
        pcnt.clear();
        dtime.clear();
        dtimeInt.clear();
        dtcnt.clear();
        //cout<<fabs(dtime0-dtime_[i])<<endl;
        // cout<<"dTimeOfEv"<<dTimeOfEv<<endl;
        //dTimeOfEv = dtime_[i];
        nHit = 0;
        hBoard->Reset();
        hChannel->Reset();
        
        dtcnt.push_back(0);
        
        frameLast = frame_;

        //cout<<"EvIndex:\t"<<EvIndex<<endl;
      }
      board.push_back(board_[i]);
      channel.push_back(channel_[i]);
      pwidth.push_back(pwidth_[i]);
      tcnt.push_back(tcnt_[i]);
      pcnt.push_back(pcnt_[i]);
      pwidthScaleFactor.push_back(BDPwWei[BDcheck(board_[i])]);
      if (BDcheck(board_[i])==-1||CHcheck(channel_[i])==-1){
        issEvP<<unixtime_<<"\t"<<board_[i]<<"\t"<<channel_[i]<<"\t"<<pcnt_[i]<<"\t"<<tcnt_[i]<<endl;
        // cout<<unixtime_<<"\t"<<board_[i]<<"\t"<<channel_[i]<<"\t"<<pcnt_[i]<<"\t"<<tcnt_[i]<<endl;
      }
      dtime.push_back(dtime_[i]);
      dtimeInt.push_back(dtimeInt_[i]);
      
      hBoard  ->Fill(BDcheck(board_[i]));
      // cout<<board_[i]<<endl;
      hChannel->Fill(channel_[i]);
      nHit++;
      dtime0 = dtimeInt_[i];
    }
    if(ev==ThisFileLastEvent) break;
  }
  
  

  

  rotfile->WriteObject(tree,"t");
  TObjString *FlagFinish = new TObjString("true");
  rotfile->WriteObject(FlagFinish,"FlagFinish");
  ofstream out   (FNOEvNumForGap.data(), ofstream::out | ofstream::app );
  ofstream outEvP(FNOEvProblem.data()  , ofstream::out | ofstream::app );
  cout<<"\n"<<"Finished Ntuple write"<<endl;
  cout<<"gap:total event:\t"<<eventGap<<"\t"<<Index<<endl;

  
  
  rotfile->Close();
  out<<iss.str();
  // out1<<iss1.str();
  outEvP<<issEvP.str();

  // throw;
}

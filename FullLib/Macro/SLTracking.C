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
#include "LoadChTable.h"

using namespace std;
using namespace MuoAna_path_dir;
using namespace MuographAnaVariable;
using namespace DataConst;


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
class HitSet : public ChSet {
public:
    float PX, PY, PZ, PWidth;
    int tcnt;
    HitSet() : ChSet(), PX(0), PY(0), PZ(0) { PWidth = -1;}

    HitSet(int gch, int ibd, int ich, int ix, int iy, int iz, int dir, float px, float py, float pz)
        : ChSet(gch, ibd, ich, ix, iy, iz, dir), PX(px), PY(py), PZ(pz) {PWidth = -1;}

    virtual void Show() {
        ChSet::Show(); // 呼叫基類的 Show() 函數
        std::cout << PX << "\t" << PY << "\t" << PZ << std::endl;
    }
};
void SLTracking(
  const int index = 28)
{
  double eventGap = eventGapTcnt[index]*1.;
  char rtfNIn[200]; sprintf(rtfNIn,"%sGapT%d_%s_nHTH%dL%d.root",DirOperate.data(),int(eventGap),TimeStr,TriggerS,TriggerL);
  char rtfNOut[200]; sprintf(rtfNOut,"%sSTGapT%d_%s_nHTH%dL%d.root",DirOperate.data(),int(eventGap),TimeStr,TriggerS,TriggerL);
  cout<<rtfNIn<<endl;
  TFile file(rtfNIn, "READ");
  if (file.IsZombie()) {
    cerr << "Error: Cannot open file " << rtfNIn << endl;
    return;
  }
  
  TChain *tRead = new TChain("t");
  tRead->Add(file.GetName());
  TFile *fSave = new TFile(rtfNOut,"recreate");
  TTree *tSave = new TTree("t","Tree for Straight Line Tracking events");
 // 打開 ROOT 文件
  std::map<int, ChSet> ChTable;
  LoadChTable(ChTable,(DirDetector+"ChannelTable"+DetectorGeoSet+".dat").data());
  // for(int idata = 0;idata<int(ChTable.size());idata++) ChTable[idata].Show();
  // throw;
  // 設置樹的變數
  Long64_t unixtime ;
  Int_t EvIndex, SLIndex, nH, nH0, nH1, nH2, nH3, nLayers;
  vector<int>* channel = nullptr;
  vector<int>* board = nullptr;
  vector<int>* pwidth = nullptr;
  vector<int>* tcnt = nullptr;
  vector<int>  vCID,vBID,vGID,vPW,vIX,vIY,vIZ,vPX,vPY,vPZ,vtcnt;

  tRead->SetBranchAddress("unixtime", &unixtime);
  tRead->SetBranchAddress("EvIndex", &EvIndex);
  tRead->SetBranchAddress("nH", &nH);
  tRead->SetBranchAddress("nH0", &nH0);
  tRead->SetBranchAddress("nH1", &nH1);
  tRead->SetBranchAddress("nH2", &nH2);
  tRead->SetBranchAddress("nH3", &nH3);
  tRead->SetBranchAddress("nLayers", &nLayers);
  tRead->SetBranchAddress("channel", &channel);
  tRead->SetBranchAddress("board", &board);
  tRead->SetBranchAddress("pwidth", &pwidth);
  tRead->SetBranchAddress("tcnt", &tcnt);
  tRead->SetBranchStatus("dtimeInt", 0);

  
  int iX0=0, iY0=0, TrackID=0, DiX=0, DiY=0, nNoise;
  tSave->Branch("unixtime", &unixtime);
  tSave->Branch("EvIndex", &EvIndex);
  tSave->Branch("SLIndex", &SLIndex);
  tSave->Branch("TrackID", &TrackID);
  tSave->Branch("nNoise", &nNoise);
  //reliability = 0=best  3=wrost
  // tSave->Branch("nH", &nH);
  // tSave->Branch("nH0", &nH0);
  // tSave->Branch("nH1", &nH1);
  // tSave->Branch("nH2", &nH2);
  // tSave->Branch("nH3", &nH3);
  tSave->Branch("iX0", &iX0);
  tSave->Branch("iY0", &iY0);
  tSave->Branch("DiX", &DiX);
  tSave->Branch("DiY", &DiY);
  tSave->Branch("tcnt", &vtcnt);
  // tSave->Branch("nLayers", &nLayers);
  
  // tSave->Branch("channel", &channel);
  // tSave->Branch("board", &board);
  // tSave->Branch("CID", &vCID);
  // tSave->Branch("BID", &vBID);
  // tSave->Branch("GID", &vGID);
  // tSave->Branch("PW", &vPW);
  // tSave->Branch("IX", &vIX);
  // tSave->Branch("IY", &vIY);
  // tSave->Branch("IZ", &vIZ);
  // tSave->Branch("PX", &vPX);
  // tSave->Branch("PY", &vPY);
  // tSave->Branch("PZ", &vPZ);

  // 迴圈讀取所有條目
  Long64_t nEntries = tRead->GetEntries();
  SLIndex=0;
  // cout<<132<<"\t"<<nEntries<<endl;
  for (Long64_t i = 0; i < nEntries; ++i) {
    tRead->GetEntry(i);
    if(unixtime%1000==0) cout<<"\r"<<i*100./(nEntries*1.)<<"%"<<flush;

    if(nH<3||nH>6) continue;
    if(nH0<1||nH0>2) continue;
    if(nH3<1||nH3>2) continue;
    if(nH1+nH2<1) continue;
    // cout<<140<<"\t"<<i<<"\t"<<nH<<"\t"<<nH0<<"\t"<<nH1<<"\t"<<nH2<<"\t"<<nH3<<endl;
    vector<HitSet> EventTmp[NumLY];
    for (int iHit = 0; iHit < nH; ++iHit) {
      HitSet Hittmp;
      Hittmp.IBD = BDcheck(board->at(iHit));
      Hittmp.ICH = channel->at(iHit);
      Hittmp.GCH = Hittmp.IBD*NumCh + Hittmp.ICH;
      // cout<<Hittmp.IBD<<"*"<<NumCh <<"+"<< Hittmp.ICH<<"\t"<<Hittmp.GCH<<endl;
      Hittmp.IX = ChTable[Hittmp.GCH].IX;
      Hittmp.IY = ChTable[Hittmp.GCH].IY;
      Hittmp.IZ = ChTable[Hittmp.GCH].IZ;
      Hittmp.tcnt = tcnt->at(iHit);
      // cout<<151<<" "<<Hittmp.IX<<","<<Hittmp.IY<<","<<Hittmp.IZ<<endl;
      Hittmp.PWidth = pwidth->at(iHit);
      EventTmp[Hittmp.IZ].push_back(Hittmp);
    }
    // cout<<155<<endl;
    int Combination = 1;
    int nHk[NumLY] = {0};
    bool NoiseCut = true;
    for(int iLay = 0;iLay<NumLY&&NoiseCut;iLay++){
      nHk[iLay] = int(EventTmp[iLay].size());
      Combination *= int(nHk[iLay] == 0 ? 1 : nHk[iLay]);
      if(nHk[iLay]>1){
        // if(nHk[iLay]>2) cout<<"Lay = "<<iLay<<"\t nHk ="<<nHk[iLay]<<endl;
        for (int i = 0; i < nHk[iLay]&&NoiseCut; ++i) {
          for (int j = i + 1; j < nHk[iLay]&&NoiseCut; ++j) {
            double distance = sqrt(
                  pow( EventTmp[iLay][i].IX -  EventTmp[iLay][j].IX, 2) 
                + pow( EventTmp[iLay][i].IY -  EventTmp[iLay][j].IY, 2));
            NoiseCut = distance > sqrt(8);
            // if(nHk[iLay]>2) cout<<"dis "<<i<<"\t"<<j<<"\t = "<<distance<<endl;
            // if(nHk[iLay]>2) cout<<"detail = ("<<EventTmp[iLay][i].IX<<","<<EventTmp[iLay][i].IY<<") -> ("<<EventTmp[iLay][j].IX<<","<<EventTmp[iLay][j].IY<<")\n";
          }
        }
        // cout<<164<<" "<<NoiseCut<<endl;
      }
    }
    // cout<<165<<endl;
    if(!NoiseCut) continue;
    // cout<<179<<endl;
    vector<HitSet> EventCob[20][NumLY];
    // cout<<191<<" "<<Combination<<endl;
    
    for(int iCB = 0; iCB<Combination; iCB++){
      int RATIO = Combination;
      for(int iLay = 0;iLay<NumLY;iLay++){
        if(nHk[iLay] ==0)    continue;
        RATIO/=nHk[iLay];
        int iH = (iCB/RATIO)%nHk[iLay];
        EventCob[iCB][iLay].push_back(EventTmp[iLay][iH]);
      }
    }
/*
    if(Combination>=4){
      cout<<"------New Event------"<<endl;
      cout<<i/double(nEntries)<<"\t"<<EvIndex<<"\t"<<SLIndex<<"\t"<<endl;
      cout<<nH<<" "<<nH0<<" "<<nH1<<" "<<nH2<<" "<<nH3<<endl;

      for(int iCB=0;iCB<Combination;iCB++){
        cout<<"(";
        for(int iL=0;iL<NumLY;iL++){
          if(EventCob[iCB][iL].size()==1)
            cout<<EventCob[iCB][iL][0].IX<<","<<EventCob[iCB][iL][0].IY<<","<<EventCob[iCB][iL][0].IZ<<"\t    ";
          else 
            cout<<"Null\t    ";
        }
        cout<<")"<<endl;
      }
      cout<<"------End Event------"<<endl;
    }
    */
    /*
    for(int iCB=0;iCB<Combination;iCB++)
      for(int il=0;il<4;il++)
        cout<<EventCob[iCB][il].size()<<endl;
    for(int iCB=0;iCB<Combination;iCB++){
      cout<<EventCob[iCB][0][0].IX<<","<<EventCob[iCB][0][0].IY<<","<<EventCob[iCB][0][0].IZ<<"\t";
      cout<<EventCob[iCB][1][0].IX<<","<<EventCob[iCB][1][0].IY<<","<<EventCob[iCB][1][0].IZ<<"\t";
      cout<<EventCob[iCB][2][0].IX<<","<<EventCob[iCB][2][0].IY<<","<<EventCob[iCB][2][0].IZ<<"\t";
      cout<<EventCob[iCB][3][0].IX<<","<<EventCob[iCB][3][0].IY<<","<<EventCob[iCB][3][0].IZ<<endl;
    }
    */
    vector<int> PassIndex, vDiX, vDiY;
    // cout<<211<<"\t"<<Combination<<endl;
    
    for(int iCB=0;iCB<Combination;iCB++){
      // cout<<226<<endl;
      int ix0 = EventCob[iCB][0][0].IX, iy0 = EventCob[iCB][0][0].IY;
      // cout<<ix0<<"\t"<<iy0<<endl;
      int dixMax = ix0-EventCob[iCB][NumLY-1][0].IX;
      // cout<<228<<"  "<<dixMax<<endl;
      // cout<<229<<"  "<<(NumLY-1)<<endl;
      if(dixMax%(NumLY-1)!=0) continue;
      int diyMax = iy0-EventCob[iCB][NumLY-1][0].IY;
      if(diyMax%(NumLY-1)!=0) continue;
      // cout<<232<<"  "<<dixMax%(NumLY-1)<<"\t"<<diyMax%(NumLY-1)<<endl;
      int dix = dixMax/(NumLY-1), diy = diyMax/(NumLY-1);
      bool Pass = true;
      // cout<<182<<endl;
      // cout<<ix0<<" - "<<EventCob[iCB][NumLY-1][0].IX<<"\t"<<dix<<endl;
      // cout<<iy0<<" - "<<EventCob[iCB][NumLY-1][0].IY<<"\t"<<diy<<endl;
      // cout<<iy0<<"\t"<<diy<<endl;
      for(int iL=1;iL<(NumLY-1)&&Pass;iL++){
        if(EventCob[iCB][iL].size()==1){
          // cout<<190<<endl;
          if(dix==0){
            Pass = (ix0 == EventCob[iCB][iL][0].IX);
          }else{
            Pass = (ix0 - EventCob[iCB][iL][0].IX) == dix*iL;
            // cout<<195<<" bool = "<<Pass<<" , "<<ix0<<" - "<<EventCob[iCB][iL][0].IX<<" == "<<dix*iL<<endl;
          }
          if(!Pass) break;
          if(diy==0){
            Pass = (iy0 == EventCob[iCB][iL][0].IY);
            // cout<<198<<" bool = "<<Pass<<" , "<<iy0<<" == "<<EventCob[iCB][iL][0].IY<<endl;
          }else{
            Pass = (iy0 - EventCob[iCB][iL][0].IY) == diy*iL;
          }
        }
      }
      
      if(Pass){
        PassIndex.push_back(iCB);
        vDiX.push_back(dix);
        vDiY.push_back(diy);
      }
    }
    // cout<<262<<endl;
    if(PassIndex.size()==0) continue;
    else{
      if(PassIndex.size()>1) cout<<"------New Event------"<<endl;
      if(PassIndex.size()>1) cout<<i/double(nEntries)<<"\t"<<EvIndex<<"\t"<<SLIndex<<"\t"<<PassIndex.size()<<endl;
      if(PassIndex.size()>1) cout<<nH<<" "<<nH0<<" "<<nH1<<" "<<nH2<<" "<<nH3<<endl;

      for(int iTL=0;iTL<int(PassIndex.size());iTL++){
        int iCB = PassIndex[iTL];
        TrackID = 0; nNoise = 0;
        if(PassIndex.size()>1) cout<<"PassIndex[iTL] = "<<iCB<<": (\t";
        for(int iL=0;iL<NumLY;iL++){
          nNoise =+ nHk[iL] - EventCob[iCB][iL].size();
          if(EventCob[iCB][iL].size()==1){
            if(PassIndex.size()>1) cout<<EventCob[iCB][iL][0].IX<<","<<EventCob[iCB][iL][0].IY<<","<<EventCob[iCB][iL][0].IZ<<"\t";
            TrackID += pow(10,iL);
            vtcnt.push_back(EventCob[iCB][iL][0].tcnt);
          }else{
            if(PassIndex.size()>1) cout<<"Null\t";
            vtcnt.push_back(-9999);
          }
          
        }
        if(PassIndex.size()>1) cout<<")"<<endl;
        iX0 = EventCob[iCB][0][0].IX;
        iY0 = EventCob[iCB][0][0].IY;
        DiX = vDiX[iTL];
        DiY = vDiY[iTL];
        
        tSave->Fill();
        vtcnt.clear();
      }
      SLIndex++;
    }
    // cout<<203<<endl;
    /*
    if(SLIndex>2000){
      cout<<"End"<<endl;
      break;
    }
    */
    // cout<<208<<endl;
    
  }
  // cout<<211<<endl;
  // 清理資源
  file.Close();
  tSave->Write();
  fSave->Close();


}
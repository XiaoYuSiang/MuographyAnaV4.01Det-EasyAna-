#include <typeinfo>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
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

void ChRateAnaV401(){//140
  // setTDRStyle();
  vector<string> vRootFiles = RawRootList(DirOperate.data());
  int totalCh = NumBD*NumCh;

  TChain *t = new TChain("t");
  Long64_t EffTime = 0;
  for(int i=0;i<int(vRootFiles.size());i++){
    TChain tDataTMP("t");
    cout<<"Add TChain: "<<vRootFiles[i]<<endl;
    Long64_t uttmp=0,utitmp=0,utftmp=0; 
    tDataTMP.SetBranchAddress("unixtime",&uttmp);
    tDataTMP.Add(vRootFiles[i].data());
    tDataTMP.GetEntry(0);
    EffTime -= uttmp;
    tDataTMP.GetEntry(tDataTMP.GetEntries()-1);
    EffTime += uttmp;
    t->Add(&tDataTMP);
    // cout<<EffTime<<endl;
  }
  
  
  // throw;
  TH2F *h2Rate = new TH2F("h2Rate","Rate;unixtime(s);General ChID;Rate(Hz)",BinOnTimeD,FirDaySec,FinDaySec,totalCh,16,totalCh+16);
  t->Draw("board*16+channel:unixtime>>h2Rate","","goff");
  cout<<"Finish the filling of board*16+channel:unixtime>>h2Rate"<<endl;
  TCanvas *C1 = new TCanvas("C1","C1",1920+4,1080+28);
  C1->cd();
  h2Rate->SetStats(0);
  h2Rate->Draw("colz");
  h2Rate->Scale(1./th2fbinwidth);
  if(h2Rate->GetMaximum()>2) h2Rate->GetZaxis()->SetRangeUser(0,2);

  C1->Print((DirResultRate+"PWidth2D.gif").data());
  C1->Close();
  
  TCanvas *Zs[NumLY];
  int NorRes = 480*4;
  for(int iLy=0;iLy<NumLY;iLy++){
    string NTMP = Form("Z%d",iLy);
    Zs[iLy] = new TCanvas(NTMP.data(),NTMP.data(),NorRes*NumBX[iLy]+4,NorRes*NumBY[iLy]+28);
    Zs[iLy]->Divide(NumBX[iLy],NumBY[iLy]);
  }
  for(int ibd=0;ibd<NumBD;ibd++){
    cout<<"Projecting ibd = "<<ibd<<endl;
    int IZ = BDLay[ibd];
    int iPos = ibd - LayFirst[IZ];
    TCanvas *ctmp = new TCanvas("ctmp","ctmp",NorRes+4,NorRes+28);
    ctmp->Divide(NumnX,NumnY);
    Zs[IZ]->cd(iPos+1)->Divide(NumnX,NumnY);
    int Dir = DiriB_z[ibd];
    for(int ich=0;ich<NumCh;ich++){
      int iBin = ibd*16+ich+1;
      int GID = cIDBack[Dir][ich]+BD[ibd]*16;
      h2Rate->GetYaxis()->SetRangeUser(GID,GID);
      TH1D *h1tmp = h2Rate->ProjectionX(Form("h%02.0f_%02.0f",ibd*1.,cIDBack[Dir][ich]*1.),iBin,iBin);
      h1tmp->SetTitle(Form("MTB.%02.0f Ch.%02.0f;unixtime(s);Rate(Hz)",BD[ibd]*1.,cIDBack[Dir][ich]*1.));
      Long64_t nAll = h1tmp->Integral(-1,-1);
      double MeanRate = nAll*th2fbinwidth/(EffTime*1.);
      h1tmp->GetXaxis()->SetRangeUser(0,64);
      h1tmp->GetYaxis()->SetTitleOffset(1.4);
      h1tmp->SetStats(0);
      
      
      float max = h1tmp->GetMaximum()+h1tmp->GetBinError(h1tmp->GetMaximumBin());
      if(max>2){ max = 2; h1tmp->SetLineColor(2);};
      if(max<0.3) h1tmp->SetLineColor(6);
      // cout<<fConst->GetParameter(0)<<"+-"<<fConst->GetParError(0)<<", Max = "<<h1tmp->GetMaximum()<<endl;
      h1tmp->GetYaxis()->SetRangeUser(0,max*1.2);
      TPaveText *pt = new TPaveText(0.6, 0.7, 0.9, 0.9, "brNDC");
      pt->SetTextColor(kBlue);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      pt->AddText(Form("n: %1.1e",nAll*1.));
      pt->AddText(Form("Mean: %3.3f",MeanRate));
      
      
      Zs[IZ]->cd(iPos+1)->cd(ich+1);
      h1tmp->Draw("h");
      pt->Draw();
      
      ctmp->cd(cIDBack[Dir][ich]*1.+1);
      h1tmp->Draw("h");
      pt->Draw();
    }
    ctmp->Print(Form("%sRateOfMTB%02.0f.gif",DirResultRate.data(),BD[ibd]*1.));
    ctmp->Close();
  }
  for(int iZ = 0; iZ<NumLY;iZ++){
    Zs[iZ]->Print(Form("%sRateOfZ%d.gif",DirResultRate.data(),iZ));
  }
  
}
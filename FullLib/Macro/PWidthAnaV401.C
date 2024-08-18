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


void PWidthAnaV401(
  const int index = 28
){//140
  // setTDRStyle();
   
  double eventGap = eventGapTcnt[index]*1.;
  char rtfN[200]; sprintf(rtfN,"%sGapT%d_%s_nHTH%dL%d.root",DirOperate.data(),int(eventGap),TimeStr,TriggerS,TriggerL);
  int totalCh = NumBD*NumCh;
  
  TChain *t = new TChain("t");
  t->Add(rtfN);
  TH2F *h2PW = new TH2F("h2PW","h2PW",256,0,256,totalCh,16,totalCh+16);
  TH2F *h2PWSE = new TH2F("h2PWSE","h2PWSE",256,0,256,totalCh,16,totalCh+16);
  t->Draw("board*16+channel:pwidth>>h2PW","","goff");
  t->Draw("board*16+channel:pwidth>>h2PWSE","nH0<=2&&nH1<=2&&nH2==1&&nH3==1&&nLayers==4","goff");
  cout<<"Finish the filling of board*16+channel:pwidth>>h2PW"<<endl;
  TCanvas *C1 = new TCanvas("C1","C1",1920+4,1080+28);
  C1->cd();
  h2PW->Draw("colz");
  C1->Print((DirResultPW+"PWidth2D.gif").data());
  h2PWSE->Draw("colz");
  C1->Print((DirResultPW+"PWidthSE2D.gif").data());
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
      h2PW->GetYaxis()->SetRangeUser(GID,GID);
      h2PWSE->GetYaxis()->SetRangeUser(GID,GID);
      TH1D *h1tmp = h2PW->ProjectionX(Form("h%02.0f_%02.0f",ibd*1.,cIDBack[Dir][ich]*1.),iBin,iBin);
      h1tmp->SetTitle(Form("MTB.%02.0f Ch.%02.0f;PWidth(100ns);Ratio",BD[ibd]*1.,cIDBack[Dir][ich]*1.));
      h1tmp->GetXaxis()->SetRangeUser(0,64);
      h1tmp->GetYaxis()->SetTitleOffset(1.4);
      h1tmp->SetStats(0);
      Long64_t nAll = h1tmp->Integral(-1,-1);
      h1tmp->Scale(1./nAll);
      
      TH1D *hSEtmp = h2PWSE->ProjectionX(Form("hSE%02.0f_%02.0f",ibd*1.,cIDBack[Dir][ich]*1.),iBin,iBin);
      hSEtmp->GetXaxis()->SetRangeUser(0,64);
      hSEtmp->SetLineColor(2);
      hSEtmp->SetFillColorAlpha(2,0.3);
      hSEtmp->SetStats(0);
      Long64_t nSE = hSEtmp->Integral(-1,-1);

      hSEtmp->Scale(1./nSE);
      
      float max = h1tmp->GetMaximum()+h1tmp->GetBinError(h1tmp->GetMaximumBin());
      if(max<hSEtmp->GetMaximum()) max = hSEtmp->GetMaximum()+hSEtmp->GetBinError(hSEtmp->GetMaximumBin());
      cout<<max<<"\t"<<h1tmp->GetMaximum()<<"\t"<<hSEtmp->GetMaximum()<<endl;
      h1tmp->GetYaxis()->SetRangeUser(0,max*1.2);
      TPaveText *pt = new TPaveText(0.6, 0.6, 0.9, 0.9, "brNDC");
      pt->SetTextColor(kBlue);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      pt->AddText(Form("n: %1.1e",nAll*1.));
      pt->AddText(Form("Mean: %3.3f",h1tmp->GetMean()));
      pt->AddText(Form("RMS  : %3.3f",h1tmp->GetRMS()));
      pt->AddText(Form("#color[2]{n: %1.1e}",nSE*1.));
      pt->AddText(Form("#color[2]{SE Mean: %3.3f}",hSEtmp->GetMean()));
      pt->AddText(Form("#color[2]{SE RMS  : %3.3f}",hSEtmp->GetRMS()));
      
      Zs[IZ]->cd(iPos+1)->cd(ich+1);
      h1tmp->Draw("h");
      hSEtmp->Draw("histesame");
      h1tmp->Draw("histesame");
      pt->Draw();
      
      
      ctmp->cd(cIDBack[Dir][ich]*1.+1);
      h1tmp->Draw("h");
      hSEtmp->Draw("histesame");
      h1tmp->Draw("histesame");
      pt->Draw();
    }
    ctmp->Print(Form("%sPwidthOfMTB%02.0f.gif",DirResultPW.data(),BD[ibd]*1.));
    ctmp->Close();
  }
  for(int iZ = 0; iZ<NumLY;iZ++){
    Zs[iZ]->Print(Form("%sPwidthOfZ%d.gif",DirResultPW.data(),iZ));
  }
  
}
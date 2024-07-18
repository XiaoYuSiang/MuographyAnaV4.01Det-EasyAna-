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

int cIDBack[2][NumCh]={
  {
    15,14,13,12,
    11,10, 9, 8,
     7, 6, 5, 4,
     3, 2, 1, 0
  },{
    12,13,14,15,
     8, 9,10,11,
     4, 5, 6, 7,
     0, 1, 2, 3
  },
};
int LayFirst[NumLY]={0,9,13,17};

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
  C1->Print((DirResult+"PWidth2D.gif").data());
  h2PWSE->Draw("colz");
  C1->Print((DirResult+"PWidthSE2D.gif").data());
  C1->Close();
  
  TCanvas *Zs[4];
  int NorRes = 480*4;
  Zs[0] = new TCanvas("Z0","Z0",NorRes*3+4,NorRes*3+28);
  Zs[1] = new TCanvas("Z1","Z1",NorRes*2+4,NorRes*2+28);
  Zs[2] = new TCanvas("Z2","Z2",NorRes*2+4,NorRes*2+28);
  Zs[3] = new TCanvas("Z3","Z3",NorRes*3+4,NorRes*3+28);
  Zs[0]->Divide(3,3); Zs[1]->Divide(2,2); Zs[2]->Divide(2,2); Zs[3]->Divide(3,3);
  for(int ibd=0;ibd<NumBD;ibd++){
    cout<<"Projecting ibd = "<<ibd<<endl;
    int IZ = BDLay[ibd];
    int iPos = ibd - LayFirst[IZ];
    TCanvas *ctmp = new TCanvas("ctmp","ctmp",NorRes+4,NorRes+28);
    ctmp->Divide(NumnX,NumnY);
    Zs[IZ]->cd(iPos+1)->Divide(NumnX,NumnY);
    int Dir = DiriB_z[ibd];
    for(int ich=0;ich<NumCh;ich++){
      
      int GID = cIDBack[Dir][ich]+BD[ibd]*16;
      h2PW->GetYaxis()->SetRangeUser(GID,GID);
      h2PWSE->GetYaxis()->SetRangeUser(GID,GID);
      TH1D *h1tmp = h2PW->ProjectionX(Form("h%02.0f_%02.0f",ibd*1.,cIDBack[Dir][ich]*1.));
      h1tmp->SetTitle(Form("MTB.%02.0f Ch.%02.0f;PWidth(100ns);Ratio",BD[ibd]*1.,cIDBack[Dir][ich]*1.));
      h1tmp->GetXaxis()->SetRangeUser(0,64);
      h1tmp->GetYaxis()->SetTitleOffset(1.4);
      h1tmp->SetStats(0);
      h1tmp->Scale(1./(h1tmp->Integral(-1,-1)));
      
      TH1D *hSEtmp = h2PWSE->ProjectionX(Form("hSE%02.0f_%02.0f",ibd*1.,cIDBack[Dir][ich]*1.));
      hSEtmp->GetXaxis()->SetRangeUser(0,64);
      hSEtmp->SetLineColor(2);
      hSEtmp->SetFillColorAlpha(2,0.3);
      hSEtmp->SetStats(0);
      hSEtmp->Scale(1./(hSEtmp->Integral(-1,-1)));
      
      float max = h1tmp->GetMaximum();
      if(max<hSEtmp->GetMaximum()) max = h1tmp->GetMaximum();
      
      h1tmp->GetYaxis()->SetRangeUser(0,max*1.2);
      TPaveText *pt = new TPaveText(0.6, 0.6, 0.9, 0.9, "brNDC");
      pt->SetTextColor(kBlue);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      pt->AddText(Form("Mean: %3.3f",h1tmp->GetMean()));
      pt->AddText(Form("RMS  : %3.3f",h1tmp->GetRMS()));
      pt->AddText(Form("#color[2]{SE Mean: %3.3f}",hSEtmp->GetMean()));
      pt->AddText(Form("#color[2]{SE RMS  : %3.3f}",hSEtmp->GetRMS()));
      
      Zs[IZ]->cd(iPos+1)->cd(ich+1);
      h1tmp->Draw("h");
      hSEtmp->Draw("histesame");
      h1tmp->Draw("histesame");
      pt->Draw();
      
      
      ctmp->cd(ich+1);
      h1tmp->Draw("h");
      hSEtmp->Draw("histesame");
      h1tmp->Draw("histesame");
      pt->Draw();
    }
    ctmp->Print(Form("%sPwidthOfMTB%02.0f.gif",DirResult.data(),BD[ibd]*1.));
    ctmp->Close();
  }
  for(int iZ = 0; iZ<NumLY;iZ++){
    Zs[iZ]->Print(Form("%sPwidthOfZ%d.gif",DirResult.data(),iZ));
  }
  
}